//
//  Keyword.cpp
//  ChatterBot
//
//  Created by michaela perrotta on 8/12/19.
//  Copyright © 2019 michaela perrotta. All rights reserved.
//

#include <stdio.h>
#include "KeyWord.hpp"
 
// these constructors will delegate to abstract base class, AbstractToken
KeyWord::KeyWord() : AbstractToken() {}

KeyWord::KeyWord(string word) : AbstractToken(word){}

KeyWord::KeyWord(string word, vector<string> resps) : AbstractToken(word, resps){}

KeyWord::KeyWord(const KeyWord & other) : AbstractToken(other) {}

// virtual destructor
KeyWord::~KeyWord() {
    cout << "~KeyWord()" <<endl;
}

// override virtual methods for dynamic dispatch
void KeyWord::add_response(string resp) {
    responses.push_back(resp);
}
