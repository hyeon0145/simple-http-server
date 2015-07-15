//
//  http-message.h
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#ifndef __HTTPServer__http_message__
#define __HTTPServer__http_message__

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "utility.h"

class HTTPMessage {
public:
    typedef std::map<std::string, std::string> Headers;
    
public:
    std::string start_line;
    HTTPMessage::Headers headers;
    std::vector<char> body;
    
public:
    HTTPMessage();
    virtual ~HTTPMessage();
    
public:
    // parse http message
    virtual void parse(const std::vector<char> &message);
    // build http message
    virtual std::vector<char> build();
    
private:
    // parse http message headers
    void parse_headers(const std::vector<char> &headers);
    // build http message headers
    std::vector<char> build_headers();
    
public:
    static const std::string header_separator;
    static const std::string field_separator;
    static const std::string headers_separator;
    
    static const std::string body_separator;
};

#endif /* defined(__HTTPServer__http_message__) */
