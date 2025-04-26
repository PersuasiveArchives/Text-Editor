#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


GtkWidget *text_view;
std::string current_file_name;


void new_file();
void open_file();
void save_file();
void save_file_as();  
void close_file();
GtkWidget* create_menu_bar();


void new_file() {
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)), "", -1);
    current_file_name = "";
    gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel(text_view)), "Text Editor");
}


void open_file() {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint result;

    dialog = gtk_file_chooser_dialog_new("Open File",
                                         GTK_WINDOW(gtk_widget_get_toplevel(text_view)),
                                         action,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Open", GTK_RESPONSE_ACCEPT,
                                         NULL);

    result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        if (filename) {
            std::ifstream file(filename);
            if (file.is_open()) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                std::string content = buffer.str();
                gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)), content.c_str(), -1);
                current_file_name = filename;
                gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel(text_view)), g_path_get_basename(filename));
                file.close();
            } else {
                GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(text_view)),
                                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                                                 GTK_MESSAGE_ERROR,
                                                                 GTK_BUTTONS_OK,
                                                                 "Could not open file.");
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
                current_file_name = "";
            }
            g_free(filename);
        }
    }
    gtk_widget_destroy(dialog);
}


void save_file() {
    if (current_file_name.empty()) {
        save_file_as();  
    } else {
        std::ofstream file(current_file_name);
        if (file.is_open()) {
            GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
            GtkTextIter start, end;
            gtk_text_buffer_get_start_iter(buffer, &start);
            gtk_text_buffer_get_end_iter(buffer, &end);
            gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
            file << text;
            file.close();
            g_free(text);
        } else {
            GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(text_view)),
                                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                                             GTK_MESSAGE_ERROR,
                                                             GTK_BUTTONS_OK,
                                                             "Could not save file.");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        }
    }
}


void save_file_as() {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint result;

    dialog = gtk_file_chooser_dialog_new("Save As",
                                         GTK_WINDOW(gtk_widget_get_toplevel(text_view)),
                                         action,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Save", GTK_RESPONSE_ACCEPT,
                                         NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);

    result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        if (filename) {
            std::ofstream file(filename);
            if (file.is_open()) {
                GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
                GtkTextIter start, end;
                gtk_text_buffer_get_start_iter(buffer, &start);
                gtk_text_buffer_get_end_iter(buffer, &end);
                gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
                file << text;
                file.close();
                g_free(text);
                current_file_name = filename;
                gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel(text_view)), g_path_get_basename(filename));
            } else {
                GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(text_view)),
                                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                                                 GTK_MESSAGE_ERROR,
                                                                 GTK_BUTTONS_OK,
                                                                 "Could not save file.");
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
            }
            g_free(filename);
        }
    }
    gtk_widget_destroy(dialog);
}


void close_file() {
    new_file(); 
}


GtkWidget* create_menu_bar() {
    GtkWidget *menu_bar = gtk_menu_bar_new();
    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *file_menu_item = gtk_menu_item_new_with_label("File");

    GtkWidget *new_item     = gtk_menu_item_new_with_label("New");
    GtkWidget *open_item    = gtk_menu_item_new_with_label("Open...");
    GtkWidget *save_item    = gtk_menu_item_new_with_label("Save");
    GtkWidget *save_as_item = gtk_menu_item_new_with_label("Save As...");
    GtkWidget *close_item   = gtk_menu_item_new_with_label("Close");
    GtkWidget *exit_item    = gtk_menu_item_new_with_label("Exit");

    g_signal_connect(new_item,     "activate", G_CALLBACK(new_file), NULL);
    g_signal_connect(open_item,    "activate", G_CALLBACK(open_file), NULL);
    g_signal_connect(save_item,    "activate", G_CALLBACK(save_file), NULL);
    g_signal_connect(save_as_item, "activate", G_CALLBACK(save_file_as), NULL);
    g_signal_connect(close_item,   "activate", G_CALLBACK(close_file), NULL);
    g_signal_connect(exit_item,    "activate", G_CALLBACK(gtk_main_quit), NULL);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_as_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), close_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_menu_item);

    return menu_bar;
}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Text Editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *menu_bar = create_menu_bar();
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 0);

    GtkWidget *scroll_view = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), scroll_view, TRUE, TRUE, 0);

    text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scroll_view), text_view);

    GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(text_buffer, "", -1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
