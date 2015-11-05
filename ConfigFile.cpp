//
// Created by up201403057 on 29-10-2015.
//

#include "ConfigFile.h"
#include <fstream>

ConfigFile::ConfigFile(string &filename) {
    if (filename.find('.') == string::npos)
        filename += ".txt";
    this->filename = filename;
}

void ConfigFile::createFile(string &filename) {
    ofstream outputStream;

    outputStream.open(filename);
    outputStream.close();
}

bool ConfigFile::existsFile(string &filename) {
    ifstream inputStream;
    bool result = false;

    inputStream.open(filename);
    result = inputStream.is_open();
    inputStream.close();
    return result;
}
