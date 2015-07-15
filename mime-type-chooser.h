//
//  mime-type-chooser.h
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#ifndef __HTTPServer__mime_type_chooser__
#define __HTTPServer__mime_type_chooser__

#include <iostream>
#include <map>
#include <string>

#include "utility.h"

class MIMETypeChooser {
private:
    std::map<std::string, std::string> mime_types;
    
public:
    MIMETypeChooser();
    
    // return mime type of extension
    std::string mime_type_of(const std::string &extension);
    
private:
    // prepare mime types to this->mime_types
    void prepare_mime_types();
    
};

#endif /* defined(__HTTPServer__mime_type_chooser__) */
