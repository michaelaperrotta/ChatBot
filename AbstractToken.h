//
//  AbstractToken.h
//  ChatterBot
//
//  Created by michaela perrotta on 8/14/19.
//  Copyright © 2019 michaela perrotta. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#ifndef AbstractToken_h
#define AbstractToken_h

// header file for AbstractToken class
class AbstractToken {
protected:
    string content;
    vector<string> responses;
    
public:
    AbstractToken();
    AbstractToken(string word);
    AbstractToken(string word, vector<string> resps);
    AbstractToken(const AbstractToken & other);
    AbstractToken & operator=(const AbstractToken & other);
    virtual ~AbstractToken();
    virtual void add_response(string resp);
    void del_response(string resp);
    string get_content() const;
    bool has_response(string resp);
    int num_responses();
    const vector<string> get_responses() const;
    
};


#endif /* AbstractToken_h */
