//
//  utility.h
//  HTTPServer
//
//  Created by Jonghwan Hyeon on 10/9/13.
//  Copyright (c) 2013 Jonghwan Hyeon. All rights reserved.
//

#ifndef __HTTPServer__utility__
#define __HTTPServer__utility__

#include <iostream>
#include <algorithm>
#include <vector>

#include <stdexcept>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/param.h>

class Utility {
public:
    // make all the charaters in text be lower character
    static std::string to_lower(const std::string &text);
    
    // insert elements from source_first_iterator to source_last_iterator to the end of destination
    template <typename DestinationConatiner, typename SourceIterator>
    static void insert_back(DestinationConatiner &destination, const SourceIterator &source_first_iterator, const SourceIterator &source_last_iterator) {
        destination.insert(destination.end(), source_first_iterator, source_last_iterator);
    }
    
    // insert all elements in source to the end of destination
    template <typename DestinationContainer, typename SourceContainer>
    inline static void insert_back(DestinationContainer &destination, const SourceContainer &source) {
        Utility::insert_back(destination, source.begin(), source.end());
    }
    
    // split elements from source_first_iterator to source_last_iterator by elements from delimiter_first_iterator to delimiter_last_iterator
    template <typename Container, typename SourceIterator, typename DelimiterIterator>
    static std::vector<Container> split(const SourceIterator &source_first_interator, const SourceIterator &source_last_iterator, const DelimiterIterator &delimiter_first_interator, const DelimiterIterator &delimiter_last_iterator, const std::size_t limit = 0) {
        std::vector<Container> tokens;

        std::size_t size_of_delimiter = delimiter_last_iterator - delimiter_first_interator;
        SourceIterator start_iterator = source_first_interator;
        SourceIterator end_iterator = source_first_interator;
        while (end_iterator != source_last_iterator) {
            // search delimiter in the elements from start_iterator to source_last_iterator
            end_iterator = std::search(start_iterator, source_last_iterator, delimiter_first_interator, delimiter_last_iterator);
            
            // push back a token that is found
            tokens.push_back(Container(start_iterator, end_iterator));
            
            // advance the iterator by size_of_delimiter
            start_iterator = end_iterator + size_of_delimiter;
            
            // spliting elements is completed
            if (tokens.size() == limit) {
                // push back all rest elements.
                tokens.push_back(Container(start_iterator, source_last_iterator));
                break;
            }
        }
        
        return tokens;
    }
    
    // split data by delimiter
    template <typename SourceContainer, typename DelimiterContainer>
    inline static std::vector<SourceContainer> split(const SourceContainer &data, const DelimiterContainer &delimiter, const std::size_t limit = 0) {
        return Utility::split<SourceContainer>(data.begin(), data.end(), delimiter.begin(), delimiter.end(), limit);
    }
    
    // trim white spaces off text
    static std::string trim(const std::string &text, const std::string &white_spaces=" \t\r\n");
    
    // return current working directory
    static std::string get_current_working_directory();
    // check whether file exists or not
    static bool file_exists(const std::string &filename, bool includes_directory=true);
    // return file extension of path
    static std::string extract_file_extension(const std::string &path);
    // return file size of filename
    static std::size_t get_file_size(const std::string &filename);
};

#endif /* defined(__HTTPServer__utility__) */
