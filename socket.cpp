//
//  socket.cpp
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#include "socket.h"

Socket::Socket() : descriptor(-1) { }

Socket::~Socket() {
    this->close();
}

// create a socket
std::shared_ptr<Socket> Socket::create() {
    Socket *socket = new Socket();
    // create a socket, address domain is internet, and socket type is stream
    socket->descriptor = ::socket(AF_INET, SOCK_STREAM, 0);
    if (socket->descriptor < 0) {
        throw std::runtime_error("failed to create a socket");
    }
    
    // when the connection is close, a try that sends some data can occur a certain signal
    // so, I change the socket option to ignore that signal.
    int value = 1;
#ifdef __linux__
    ::setsockopt(*socket, SOL_SOCKET, MSG_NOSIGNAL, &value, sizeof(value));
#else
    ::setsockopt(*socket, SOL_SOCKET, SO_NOSIGPIPE, &value, sizeof(value));
#endif
    
    return std::shared_ptr<Socket>(socket);
}

// close the socket
void Socket::close() {
    // if socket is not created, just ignore it
    if (this->descriptor == -1) return ;
    
    // close the socket
    ::close(*this);
    this->descriptor = -1;
}

// bind the port
void Socket::bind(int port) {
    // prepare the address for the port
    std::memset(&this->address, 0, sizeof(this->address));
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(port);
    
    // bind the address for that socket
    if (::bind(*this, reinterpret_cast<sockaddr *>(&this->address), sizeof(this->address)) < 0) {
        throw std::runtime_error("failed to bind an address to the socket");
    }
}

// listen for connections
void Socket::listen(int backlog) {
    if (::listen(*this, backlog) < 0) {
        throw std::runtime_error("failed to listen for connections on the socket");
    }
}

// accept a connection
std::shared_ptr<Socket> Socket::accept() {
    Socket *socket = new Socket();
    ::socklen_t size_of_address = sizeof(socket->address);
    // accept a connection
    socket->descriptor = ::accept(*this, reinterpret_cast<sockaddr *>(&socket->address), &size_of_address);
    if (socket->descriptor < 0) {
        throw std::runtime_error("failed to accept a connection");
    }
    
    return std::shared_ptr<Socket>(socket);
}

// read data from socket
std::vector<char> Socket::read(std::size_t size) {
    std::vector<char> data = std::vector<char>(size);
    ssize_t read_size = ::read(*this, data.data(), size);
    if (read_size < 0) { // if read_size is negative, that is error
        throw std::runtime_error("failed to read data from the socket");
    }
    
    // resize the data vector by read_size
    data.resize(read_size);
    return data;
}

// write data to socket
size_t Socket::write(const std::vector<char> &data, std::size_t size) {
    ssize_t written_size = ::write(*this, data.data(), size);
    
    return written_size;
}
