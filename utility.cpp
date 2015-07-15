//
//  utility.cpp
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#include "utility.h"

std::string Utility::to_lower(const std::string &text) {
    std::string lowered_text = text;
    // transform all the charaters in lowered_text which was copied to be lower
    std::transform(lowered_text.begin(), lowered_text.end(), lowered_text.begin(), ::tolower);
    
    return lowered_text;
}

std::string Utility::trim(const std::string &text, const std::string &white_spaces) {
    std::string trimed_text = text;
    
    // find first character which is not white space
    std::size_t position = trimed_text.find_first_not_of(white_spaces);
    if (position != std::string::npos) {
        // erase left white spaces
        trimed_text.erase(trimed_text.begin(), trimed_text.begin() + position);
    } else {
        return ""; // all strings are white spaces
    }
    
    // find first character which is not white space from the right
    position = trimed_text.find_last_not_of(white_spaces);
    if (position != std::string::npos) {
        // erase right white spaces
        trimed_text.erase(trimed_text.begin() + position + 1, trimed_text.end());
    }
    
    return trimed_text;
}

std::string Utility::get_current_working_directory() {
    char current_working_directory[MAXPATHLEN + 1] = { 0, };
    // get current working directory
    if (getcwd(current_working_directory, MAXPATHLEN) == NULL) {
        std::runtime_error("failed to get current working directory");
    }
    
    return current_working_directory;
}

bool Utility::file_exists(const std::string &filename, bool includes_directory) {
    struct stat status;
    // get status of filename
    if (::stat(filename.c_str(), &status) != -1)
    {
        // if not includes directory and filename is directory
        if ((!includes_directory) && (status.st_mode & S_IFDIR)) {
            return false;
        } else {
            return true;
        }
    }
    
    return false;
}

std::string Utility::extract_file_extension(const std::string &path) {
    // split all directories from path
    std::vector<std::string> tokens = Utility::split(path, std::string("/"));
    std::string filename = tokens.back(); // get only last one which is filename part
    
    // extract only extension
    std::size_t position = filename.rfind(".");
    if (position != std::string::npos) {
        return filename.substr(position);
    } else {
        return "";
    }
}

std::size_t Utility::get_file_size(const std::string &filename) {
    struct stat status;
    // get status of filename
    if (::stat(filename.c_str(), &status) != -1)
    {
        // return file size of filename
        return status.st_size;
    }
    
    return 0;
}