
//
//  KeyWord.hpp
//  ChatterBot
//
//  Created by michaela perrotta on 8/14/19.
//  Copyright © 2019 michaela perrotta. All rights reserved.
//

#ifndef KeyWord_hpp
#define KeyWord_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#include "AbstractToken.h"

using namespace std;

// header for class KeyWord; publicly inherits from AbstractToken
class KeyWord  : public AbstractToken {
public:
    KeyWord();
    KeyWord(string word);
    KeyWord(string word, vector<string> resps);
    KeyWord(const KeyWord & other);
    virtual ~KeyWord();
    virtual void add_response(string resp);
    
};


#endif /* KeyWord_hpp */
