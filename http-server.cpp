//
//  http-server.cpp
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#include "http-server.h"

HTTPServer::HTTPServer(const std::string &working_directory) : is_started(false) {
    this->working_directory = this->sanitize_working_directory(working_directory);
    if (!Utility::file_exists(this->working_directory)) { // check whether the working directory exists or not.
        throw std::runtime_error("not existed working directory");
    }
}

HTTPServer::~HTTPServer() {
    // if the server is started, stop the server
    if (this->is_started) {
        this->stop();
    }
}

void HTTPServer::start(int port) {
    if (this->is_started) {
        throw std::runtime_error("HTTP server is already started");
    }
    
    this->is_started = true;
    
    // create server socket, bind, and listen for connections
    this->server_socket = Socket::create();
    this->server_socket->bind(port);
    this->server_socket->listen();
    
    while (this->is_started) {
        // accept a connection
        std::shared_ptr<Socket> client_socket = this->server_socket->accept();
        
        // read data from the socket
        std::vector<char> raw_request = client_socket->read(4096);
        if (raw_request.size() == 0) continue; // unknown situation, just pass it
        
        // print out HTTP request
        std::cout << "<request>" << std::endl;
        std::cout << std::string(raw_request.begin(), raw_request.end()) << std::endl;
        
        // parse HTTP request
        HTTPRequest request = HTTPRequest();
        request.parse(raw_request);
        
        // hand the HTTP request
        this->handle_request(client_socket, request);
    }
}

void HTTPServer::stop() {
    // if the server is not started
    if (!this->is_started) {
        throw std::runtime_error("HTTP server is not started");
    }
    
    // stop the server
    this->server_socket->close();
    this->is_started = false;
}

std::string HTTPServer::sanitize_working_directory(const std::string &working_directory) {
    std::string sanitized_working_directory = working_directory;
    
    // if working_directory is empty, get current working directory
    if (sanitized_working_directory == "") {
        sanitized_working_directory = Utility::get_current_working_directory();
    }
    
    // remove trailing slash
    if (sanitized_working_directory.back() == '/') {
        sanitized_working_directory.erase(sanitized_working_directory.size() - 1);
    }
    
    return sanitized_working_directory;
}

void HTTPServer::handle_request(std::shared_ptr<Socket> socket, const HTTPRequest &request) {
    // if file does not exists, show not found
    if (!Utility::file_exists(this->working_directory + request.path, false)) {
        this->handle_not_found(socket, request);
        return ;
    }
    
    // beacuse file exists, handle the request
    this->handle_okay(socket, request);
}

void HTTPServer::handle_okay(std::shared_ptr<Socket> socket, const HTTPRequest &request) {
    std::string filename = this->working_directory + request.path;
    std::ifstream stream(filename, std::ifstream::binary); // open requested file
    if (!stream.is_open()) { // if failed to open the file,
        this->handle_internal_server_error(socket, request); // show internal server error
        return ;
    }
    
    // make http response
    HTTPResponse response = HTTPResponse(200);
    response.headers["Content-Type"] = this->mime_type_chooser.mime_type_of(Utility::extract_file_extension(filename));
    response.headers["Content-Length"] = std::to_string(Utility::get_file_size(filename));
    
    // send http response header
    socket->write(response.build());
    
    // send http body
    std::vector<char> buffer(4096);
    while (stream.good()) {
        stream.read(buffer.data(), 4096);
        socket->write(buffer, stream.gcount());
    }
    stream.close();
}

// for status code 404
void HTTPServer::handle_not_found(std::shared_ptr<Socket> socket, const HTTPRequest &request) {
    HTTPResponse response = HTTPResponse(404);
    
    socket->write(response.build());
}

// for status code 500
void HTTPServer::handle_internal_server_error(std::shared_ptr<Socket> socket, const HTTPRequest &request) {
    HTTPResponse response = HTTPResponse(500);
    
    socket->write(response.build());
}