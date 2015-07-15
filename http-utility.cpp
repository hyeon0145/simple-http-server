//
//  http-utility.cpp
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#include "http-utility.h"

std::string HTTPUtility::encode_path(const std::string &path) {
    std::string encoded_path = "";
    for (std::string::const_iterator iterator = path.begin(); iterator != path.end(); iterator++) {
        if (HTTPUtility::is_allowed_character(*iterator)) { // if this character is allowed,
            encoded_path += *iterator; // just add it to the encoded_path
        } else { // else, add an encoded character
            encoded_path += "%" + HTTPUtility::to_hex_code(*iterator);
        }
    }
    
    return encoded_path;
}

std::string HTTPUtility::decode_path(const std::string &path) {
    std::string decoded_path = "";
    for (std::string::const_iterator iterator = path.begin(); iterator != path.end(); iterator++) {
        if (*iterator != '%') { // if this chracter is not percent,
            decoded_path += *iterator; // just add it to decoded_path
        } else { // else, add an decoded character
            decoded_path += HTTPUtility::from_hex_code(std::string(iterator + 1, iterator + 3));
            iterator += 2; // advance iterator by 2 for next character. (the remaining offset 1 will be added by for loop)
        }
    }
    
    return decoded_path;
}

// check whether a character is allowed or not
bool HTTPUtility::is_allowed_character(const char character) {
    static std::string allowed_characters = "!*'();:@&=+$,/?#[]ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~";
    
    return (allowed_characters.find_first_of(character) != std::string::npos);
}

// convert character to hex code
std::string HTTPUtility::to_hex_code(const char character) {
    static std::string codes = "0123456789ABCDEF";
    
    return std::string(1, codes[character / 16]) + codes[character % 16];
}

// convert hex code to character
char HTTPUtility::from_hex_code(const std::string &hex_code) {
    return std::stoi(hex_code, 0, 16);
}