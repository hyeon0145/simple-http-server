//
//  http-request.cpp
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#include "http-request.h"

const std::string HTTPRequest::request_item_separator = " ";

HTTPRequest::HTTPRequest() : HTTPMessage() { }
HTTPRequest::~HTTPRequest() { }

void HTTPRequest::parse(const std::vector<char> &message) {
    HTTPMessage::parse(message); // call parent's parse method
    
    // split the start line
    std::vector<std::string> items = Utility::split(
        this->start_line,
        HTTPRequest::request_item_separator
    );
    
    // get method and path from the splitted start line
    this->method = items[0];
    this->path = HTTPUtility::decode_path(items[1]);
}

// build http request message
std::vector<char> HTTPRequest::build() {
    this->start_line = this->method;
    this->start_line += HTTPRequest::request_item_separator + HTTPUtility::encode_path(this->path);
    this->start_line += HTTPRequest::request_item_separator + "HTTP/1.1";
    
    return HTTPMessage::build();
}