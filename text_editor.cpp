#include "text_editor.h" 

void displayMenu() {
    std::cout << "\nText Editor Menu:\n";
    std::cout << "1. Create New File\n";
    std::cout << "2. Open File\n";
    std::cout << "3. Save File\n";
    std::cout << "4. Save File As\n";
    std::cout << "5. Close File\n";
    std::cout << "6. Edit File\n";
    std::cout << "7. Display File Contents\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int getIntegerInput() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

void createFile(std::string& filename, std::string& fileContent) {
    if (!filename.empty()) {
        std::cout << "Close the current file before creating a new one.\n";
        return;
    }
    std::cout << "Enter the name of the new file: ";
    std::getline(std::cin, filename);
    fileContent = "";
    std::cout << "File '" << filename << "' created in memory.  Use 'Edit File' to add content, and 'Save File' to save to disk.\n";
}

void openFile(std::string& filename, std::string& fileContent) {
    if (!filename.empty()) {
        std::cout << "Close the current file before opening another one.\n";
        return;
    }
    std::cout << "Enter the name of the file to open: ";
    std::getline(std::cin, filename);
    std::ifstream file(filename.c_str());
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        fileContent = buffer.str();
        file.close();
        std::cout << "File '" << filename << "' opened.\n";
    } else {
        std::cerr << "Error opening file '" << filename << "'.  It may not exist.\n";
        filename = "";
        fileContent = "";
    }
}

void saveFile(const std::string& filename, const std::string& fileContent) {
    if (filename.empty()) {
        std::cout << "No file is currently open or created.\n";
        return;
    }
    std::ofstream file(filename.c_str());
    if (file.is_open()) {
        file << fileContent;
        file.close();
        std::cout << "File '" << filename << "' saved.\n";
    } else {
        std::cerr << "Error saving file '" << filename << "'\n";
    }
}

void saveFileAs(std::string& filename, const std::string& fileContent) {
    if (fileContent.empty()) {
        std::cout << "No file content to save.\n";
        return;
    }
    std::string newFilename;
    std::cout << "Enter the new name for the file: ";
    std::getline(std::cin, newFilename);
    std::ofstream file(newFilename.c_str());
    if (file.is_open()) {
        file << fileContent;
        file.close();
        filename = newFilename;
        std::cout << "File saved as '" << newFilename << "'\n";
    } else {
        std::cerr << "Error saving file as '" << newFilename << "'\n";
    }
}

void closeFile(std::string& filename, std::string& fileContent) {
    if (filename.empty()) {
        std::cout << "No file is currently open.\n";
        return;
    }
    filename = "";
    fileContent = "";
    std::cout << "File closed.\n";
}

void editFile(const std::string& filename, std::string& fileContent) {
    if (filename.empty()) {
        std::cout << "No file is currently open or created.  Create a new file or open an existing one.\n";
        return;
    }
    std::cout << "Enter the text to add to the file (or type 'DONE' on a new line to finish):\n";
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "DONE") {
            break;
        }
        fileContent += line + "\n";
    }
    std::cout << "Finished editing.\n";
}

void displayFileContents(const std::string& filename, const std::string& fileContent) {
    if (filename.empty()) {
        std::cout << "No file is currently open.\n";
        return;
    }
    if (fileContent.empty())
    {
        std::cout << "The file is empty.\n";
        return;
    }
    std::cout << "--- File Contents of '" << filename << "' ---:\n";
    std::cout << fileContent;
    std::cout << "--- End of File Contents --- \n";
}
