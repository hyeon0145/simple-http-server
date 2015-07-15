//
//  http-utility.h
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#ifndef __HTTPServer__http_utility__
#define __HTTPServer__http_utility__

#include <iostream>
#include <string>

class HTTPUtility {
public:
    // encode the path for http url
    static std::string encode_path(const std::string &path);
    // decode the path for helping the server process file
    static std::string decode_path(const std::string &path);
    // check whether the character is safe or not
    static bool is_allowed_character(const char character);
    
private:
    // convert character to hex code
    static std::string to_hex_code(const char character);
    // convert hex code to character
    static char from_hex_code(const std::string &hex_code);
};


#endif /* defined(__HTTPServer__http_utility__) */
