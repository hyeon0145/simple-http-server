//
//  http-server.h
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#ifndef __HTTPServer__http_server__
#define __HTTPServer__http_server__

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "socket.h"

#include "http-request.h"
#include "http-response.h"
#include "mime-type-chooser.h"

#include "utility.h"

class HTTPServer {
private:
    std::string working_directory;
    MIMETypeChooser mime_type_chooser;
    
    bool is_started;
    std::shared_ptr<Socket> server_socket;
    
public:
    HTTPServer(const std::string &working_directory="");
    virtual ~HTTPServer();
    
public:
    // start HTTP server
    void start(int port=80);
    // stop HTTP server
    void stop();
    
private:
    // sanitize working directory
    std::string sanitize_working_directory(const std::string &working_directory);
    
    // handle http request message
    void handle_request(std::shared_ptr<Socket> socket, const HTTPRequest &request);
    
    // handle http okay response
    void handle_okay(std::shared_ptr<Socket> socket, const HTTPRequest &request);
    // handle http not found response
    void handle_not_found(std::shared_ptr<Socket> socket, const HTTPRequest &request);
    // handle http internal server error response
    void handle_internal_server_error(std::shared_ptr<Socket> socket, const HTTPRequest &request);
};

#endif /* defined(__HTTPServer__http_server__) */
