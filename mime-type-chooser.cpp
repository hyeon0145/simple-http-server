//
//  mime-type-chooser.cpp
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#include "mime-type-chooser.h"

MIMETypeChooser::MIMETypeChooser() {
    this->prepare_mime_types();
}

std::string MIMETypeChooser::mime_type_of(const std::string &extension) {
    // find an extension from the this->mime_types
    std::map<std::string, std::string>::iterator iterator = this->mime_types.find(Utility::to_lower(extension));
    if (iterator != this->mime_types.end()) { // mime type is existed
        return iterator->second;
    } else { // mime type is not existed
        return this->mime_types["default"];
    }
}

void MIMETypeChooser::prepare_mime_types() {
    // add mime types to this->mime_types
    this->mime_types[".htm"] = "text/html";
    this->mime_types[".html"] = "text/html";
    this->mime_types[".gif"] = "image/gif";
    this->mime_types[".jpg"] = "image/jpeg";
    this->mime_types[".jpeg"] = "image/jpeg";
    this->mime_types[".mp3"] = "audio/mpeg";
    this->mime_types[".pdf"] = "application/pdf";
    
    this->mime_types["default"] = "application/octet-stream";
}