#ifndef TEXT_EDITOR_H // Include guard to prevent multiple inclusions
#define TEXT_EDITOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <cstdio>
#include <cstdlib>


void displayMenu();
int getIntegerInput();
void createFile(std::string& filename, std::string& fileContent);
void openFile(std::string& filename, std::string& fileContent);
void saveFile(const std::string& filename, const std::string& fileContent);
void saveFileAs(std::string& filename, const std::string& fileContent);
void closeFile(std::string& filename, std::string& fileContent);
void editFile(const std::string& filename, std::string& fileContent);
void displayFileContents(const std::string& filename, const std::string& fileContent);

#endif // TEXT_EDITOR_H
