//
//  main.cpp
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#include <iostream>
#include <memory>
#include <stdexcept>

#include <sys/signal.h>

#include "http-server.h"

int main(int argc, const char *argv[])
{
    // check the count of arguments
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <port number>" << std::endl;
        return 1;
    }
        
    try {
        // instantiate http server
        std::shared_ptr<HTTPServer> server = std::shared_ptr<HTTPServer>(new HTTPServer());
        
        // convert string port number to integer
        int port_number = std::stoi(argv[1]);
        // start http server
        server->start(port_number);
    } catch (const std::runtime_error &exception) { // if error is raised,
        std::cerr << "<error>" << std::endl; // print out the error
        std::cerr << exception.what() << std::endl;
    }
    
    return 0;
}

