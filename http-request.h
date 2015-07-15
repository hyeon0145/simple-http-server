//
//  http-request.h
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#ifndef __HTTPServer__http_request__
#define __HTTPServer__http_request__

#include <iostream>
#include <string>

#include "http-message.h"
#include "http-utility.h"

#include "utility.h"

class HTTPRequest : public HTTPMessage {
public:
    std::string method;
    std::string path;
    
public:
    HTTPRequest();
    virtual ~HTTPRequest();
    
public:
    // parse http request message
    virtual void parse(const std::vector<char> &message);
    // build http request message
    virtual std::vector<char> build();
    
public:
    static const std::string request_item_separator;
};

#endif /* defined(__HTTPServer__http_request__) */
