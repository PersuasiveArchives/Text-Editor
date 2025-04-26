# Makefile for the Text Editor


CXX = g++


CXXFLAGS = -Wall -g  


GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)


SOURCES = main.cpp


TARGET = text_editor


all: $(TARGET)


$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(GTK_CFLAGS) $(GTK_LIBS)


clean:
	rm -f $(TARGET)
