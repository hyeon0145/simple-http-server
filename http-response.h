//
//  http-response.h
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#ifndef __HTTPServer__http_response__
#define __HTTPServer__http_response__

#include <iostream>
#include <string>

#include "http-message.h"
#include "http-utility.h"

#include "utility.h"

class HTTPResponse : public HTTPMessage {
public:
    int status_code;
    
public:
    HTTPResponse(int status_code);
    virtual ~HTTPResponse();
    
public:
    // parse http response message
    virtual void parse(const std::vector<char> &message);
    // build httep response message
    virtual std::vector<char> build();
    
private:
    // return phrase of this->status_code
    std::string phrase_of();
    
    // generate error page for this->status_code
    std::string generate_error_page();
    
public:
    static const std::string response_item_separator;
};

#endif /* defined(__HTTPServer__http_response__) */
