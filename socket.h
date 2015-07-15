//
//  socket.h
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#ifndef __HTTPServer__socket__
#define __HTTPServer__socket__

#include <iostream>
#include <memory>
#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

#include <stdexcept>

class Socket {
private:
    int descriptor;
    ::sockaddr_in address;
    
private:
    Socket();
public:
    virtual ~Socket();
    
public:
    // create a socket
    static std::shared_ptr<Socket> create();
    // close the socket
    void close();
    
    // bind a port to the socket
    void bind(int port);
    // listen for connections
    void listen(int backlog=10);
    // accept a connection
    std::shared_ptr<Socket> accept();
    
    // read data from the socket
    std::vector<char> read(std::size_t size);
    // write data to the socket
    size_t write(const std::vector<char> &data, std::size_t size);
    inline std::size_t write(const std::vector<char> &data) {
        return this->write(data, data.size());
    }
    
    // return socket's descriptor
    inline operator int() {
        return this->descriptor;
    }
};

#endif /* defined(__HTTPServer__socket__) */
