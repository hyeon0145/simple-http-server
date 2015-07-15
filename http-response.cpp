//
//  http-response.cpp
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#include "http-response.h"

const std::string HTTPResponse::response_item_separator = " ";

HTTPResponse::HTTPResponse(int status_code) : HTTPMessage(), status_code(status_code) { }
HTTPResponse::~HTTPResponse() { }

// parse http response message
void HTTPResponse::parse(const std::vector<char> &message) {
    HTTPMessage::parse(message); // call parent's parse method
    
    // split start line by response item separator
    std::vector<std::string> items = Utility::split(
        this->start_line,
        HTTPResponse::response_item_separator
    );
    
    // get status code from splitted start line
    this->status_code = std::stoi(items[1]);
}

// build http response
std::vector<char> HTTPResponse::build() {
    this->start_line = "HTTP/1.1";
    this->start_line += HTTPResponse::response_item_separator + std::to_string(this->status_code);
    this->start_line += HTTPResponse::response_item_separator + this->phrase_of();
    
    // if status code is kind of erros, and body is empty,
    if ((this->status_code >= 400) && (this->body.size() == 0)) {
        std::string contents = this->generate_error_page(); // generate error page for status code
        this->body = std::vector<char>(contents.begin(), contents.end()); // assign the generated error page to the body
    }
    
    // build http message
    return HTTPMessage::build();
}

// return phrase of status code
std::string HTTPResponse::phrase_of() {
    switch (this->status_code) {
        case 200:
            return "OK";
        case 404:
            return "Not Found";
        case 500:
            return "Internal Server Error";
        default:
            return "Not Implemented";
    }
}

// generate error page for status code
std::string HTTPResponse::generate_error_page() {
    std::string description = std::to_string(this->status_code) + " " + this->phrase_of();
    
    std::string contents = "<!doctype html>";
    contents += "<html><head>";
    contents += "<title>" + description + "</title>";
    contents += "</head><body>";
    contents += "<h1>" + description + "</h1>";
    contents += "</body></html>";
    
    return contents;
}