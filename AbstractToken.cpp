//
//  AbstractToken.cpp
//  ChatterBot
//
//  Created by michaela perrotta on 8/12/19.
//  Copyright © 2019 michaela perrotta. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include "AbstractToken.h"


using namespace std;

// default constructor
AbstractToken::AbstractToken() {
    content = "";
}

// parameterized: content without any mapped responses
AbstractToken::AbstractToken(string word) {
    content = word;
}


// parameterized: string with responses
AbstractToken::AbstractToken(string word, vector<string> resps) {
    content = word;
    responses = resps;
}


//copy constructor
AbstractToken::AbstractToken(const AbstractToken & other) {
    content = other.get_content();
    // clear old
    responses.clear();
    // copy over responses
    for (auto elem : other.get_responses()) {
        add_response(elem);
    }
}
    
// override assignment op
AbstractToken & AbstractToken::operator=(const AbstractToken & other){
    if (this == &other) {
        return *this;
    }
        
    content = other.get_content();
    responses.clear();
    int i = 0;
    for (auto elem : other.get_responses()) {
        responses[i] = elem;
        i++;
    }
    return *this;
}

// marked as virtual in header, dynamic dispatch purposes
AbstractToken::~AbstractToken() {
    cout << "~AbstractToken()" <<endl;
}

// add given string response to the list of responses
void AbstractToken::add_response(string resp) {
    responses.push_back(resp);
}

// delete the given response if it exists in token response list
void AbstractToken::del_response(string resp) {
    if (has_response(resp)) {
        int i = 0;
        for (auto r : responses){
            if (r == resp){
                responses.erase(responses.begin() + i);
                break;
            }
            i++;
        }
    }
}

// get the string content of this token
string AbstractToken::get_content() const {
    return content;
}
    

// return bool response whether this token contains the given response
bool AbstractToken::has_response(string resp) {
    for (auto r : responses) {
        if (r == resp) {
            return true;
        }
    }
    return false;
}

// return a count of number of responses mapped to this token
int AbstractToken::num_responses() {
    return responses.size();
}

// return a constant vector with all responses mapped to this token
const vector<string> AbstractToken::get_responses() const {
    return responses;
}
