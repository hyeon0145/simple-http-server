//
//  http-message.cpp
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#include "http-message.h"

const std::string HTTPMessage::header_separator = "\r\n";
const std::string HTTPMessage::field_separator = ":";
const std::string HTTPMessage::headers_separator = "\r\n";

const std::string HTTPMessage::body_separator = "\r\n\r\n";

HTTPMessage::HTTPMessage() { }

HTTPMessage::~HTTPMessage() { }

// parse http message
void HTTPMessage::parse(const std::vector<char> &message) {
    // split http message into header and body part
    std::vector<std::vector<char> > parts = Utility::split(message, HTTPMessage::body_separator, 1);
    // split http header part into start line and headers
    std::vector<std::vector<char> > headers = Utility::split(parts[0], HTTPMessage::header_separator, 1);
    
    // get start line from splitted http header part
    this->start_line = std::string(headers[0].begin(), headers[0].end());
    // parse http headers
    this->parse_headers(headers[1]);
    
    this->body = parts[1];
}

// build http message
std::vector<char> HTTPMessage::build() {
    std::vector<char> message;
    
    Utility::insert_back(message, this->start_line);
    Utility::insert_back(message, HTTPMessage::header_separator);
    
    Utility::insert_back(message, this->build_headers());
    Utility::insert_back(message, HTTPMessage::headers_separator);
    
    Utility::insert_back(message, this->body);

    return message;
}

// parse http headers
void HTTPMessage::parse_headers(const std::vector<char> &headers) {
    // split http headers into each line
    std::vector<std::vector<char> > lines = Utility::split(headers, HTTPMessage::header_separator);
    for (std::vector<std::vector<char> >::iterator iterator = lines.begin(); iterator != lines.end(); iterator++) {
        // split each header line into field name and value
        std::vector<std::string> parts = Utility::split(
            std::string(iterator->begin(), iterator->end()),
            HTTPMessage::field_separator
        );
        
        // store the header
        this->headers[Utility::trim(parts[0])] = Utility::trim(parts[1]);
    }
}

// build http headers
std::vector<char> HTTPMessage::build_headers() {
    std::vector<char> headers;
    std::string separator = HTTPMessage::field_separator + " ";
    
    for (HTTPMessage::Headers::iterator iterator = this->headers.begin(); iterator != this->headers.end(); iterator++) {
        Utility::insert_back(headers, iterator->first);
        Utility::insert_back(headers, separator);
        Utility::insert_back(headers, iterator->second);
        Utility::insert_back(headers, HTTPMessage::header_separator);
    }
    
    return headers;
}