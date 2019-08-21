//
//  Dictionary.cpp
//  ChatterBot
//
//  Created by michaela perrotta on 8/12/19.
//  Copyright © 2019 michaela perrotta. All rights reserved.
//

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include "AbstractToken.h"
#include "KeyWord.hpp"

using namespace std;

// acts as a Database that stores a list of tokens
class Dictionary {
private:
    vector<AbstractToken*> tokens;
    int* token_count;
    
public:
    // default constructor
    Dictionary() {
        // empty dict
        token_count = new int(0);
    }
    
    // parameterized constructor
    Dictionary(vector<AbstractToken*> vocab) {
        this->tokens = vocab;
        token_count = new int(vocab.size());
    }
    
    // another parameterized constructor to build a custum dictionary
    // note: assume each word is mapped to response at corresponding index
    Dictionary(vector<string> words, vector<vector<string>> matching_responses) {
        for (int i = 0; i < words.size(); ++i) {
            KeyWord kw(words[i], matching_responses[i]);
            tokens.push_back(&kw);
        }
        token_count = new int(words.size());
    }
    
    // copy constructor
    Dictionary(const Dictionary & other) {
        // remove old contents from memory
        for (auto t : tokens) {
            delete t;
        }
        if (token_count){
            delete token_count;
        }
        token_count = new int(0);
        // copy each token of other into dict
        for (auto elem : other.get_tokens()) {
            add_token(elem); //copy by value
        }
    }
    
    // assignment op
    Dictionary & operator=(const Dictionary & other) {
        // prevent from self-reference
        if (this == &other) {
            return *this;
        }
        // remove old contents
        for (auto t : tokens) {
            delete t;
        }
        if (token_count){
            delete token_count;
        }
        // set by reference
        int i = 0;
        for (auto elem : other.get_tokens()) {
            tokens[i] = elem;
            i++;
        }
        return *this;
    }
    
    
    // destructor
    ~Dictionary() {
        for (auto t : tokens) {
            delete t;
        }
        //tokens.clear();
        if (token_count){
            delete token_count;
        }
    }
    
    // add given token to token list
    void add_token(AbstractToken* t) {
        tokens.push_back(t);
        (*token_count)++;
    }
    
    // delete token with given content from the database
    void del_token(string content){
        if (has_token(content)) {
            int i;
            for (i = 0; i < num_tokens(); ++i) {
                if (tokens[i]->get_content() == content){
                    tokens.erase(tokens.begin() + i);
                    (*token_count)--;
                    break;
                }
            }
        }
    }

    // note: not case sensitive
    // get token with given content if it exists in this dictionary
    // note: this function is const and returns a const variable since we are
    // not modifying anything
    const AbstractToken* get_token(string content) const {
        AbstractToken* at = NULL;
        for (auto t : tokens){
            // convert both strings compared to lowercase; case insensitive
            string s = t->get_content();
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            transform(content.begin(), content.end(), content.begin(), ::tolower);
            
            if (s == content){
                at = t;
                break;
            }
        }
        return at;
    }
    
    // returns a constant list of tokens contained in this dict
    const vector<AbstractToken*> get_tokens() const {
        return tokens;
    }
    
    // return count of how many tokens are in this dict
    int num_tokens() {
        int i = 0;
        if (token_count) {
            i = *token_count;
        }
        return i;
    }
    
    // return bool value whether or not this dict contains the token with the given string content
    bool has_token(string content) {
        // use itr find and functor/predicate
        auto itr = (find_if(tokens.begin(), tokens.end(), [&content](const AbstractToken * at) {return at->get_content() == content;} ));
        if (itr != tokens.end()){
            // found
            return true;
        }
        return false;
    }
                             
};
