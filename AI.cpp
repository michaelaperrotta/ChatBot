//
//  AI.cpp
//  ChatterBot
//
//  Created by michaela perrotta on 8/12/19.
//  Copyright © 2019 michaela perrotta. All rights reserved.
//

//#include "AI.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cstring>

#include "Dictionary.cpp"
#include "AbstractToken.h"
#include "KeyWord.hpp"
#include "SpeakObject.cpp"

using namespace std;

// A simple Artificial Intelligence 'Learner' class
// relies on database of user mapped inputs to reponses
class AI {
private:
    Dictionary* response_map;
    SpeakObject voice;
    
    
public:
    // default constructor
    AI() {
        this->response_map = new Dictionary(); // put params later
    }
    
    // parameterized constructor; take in predefined dictionary
    AI(Dictionary* d) {
        this->response_map = d;
    }
    
    // copy constructor; most likely won't be used but good to have incase
    AI(const AI & other) {
        // remove old dict
        if (response_map) {
            delete response_map;
        }
        // rebuild dict
        for (auto t : other.getDictionary()->get_tokens()) {
            response_map->add_token(t);
        }
    }
    
    // override assignment op
    AI & operator=(const AI & other) {
        // prevent from self-reference
        if (this == &other) {
            return *this;
        }
        // free old memory
        if (response_map) {
            delete response_map;
        }
        // set to other dict
        //response_map = other.getDictionary();
        for (auto t : other.getDictionary()->get_tokens()) {
            response_map->add_token(t);
        }
        return *this;
    }
    
    
    // destructor
    ~AI() {
        if (response_map) {
            delete response_map;
        }
    }

    // getter for Dictionary database
    const Dictionary* getDictionary() const {
        return response_map;
    }
    
    // delegate speaking to SpeakObject
    void speak(string resp) {
        voice.say(resp);
    }
    
    
    // returns an int count of how many times 'word' appears in given list of words
    int get_token_frequency(string word, vector<string> list){
        int word_count = 0;
        for (int i = 0; i < list.size(); ++i) {
            if (word == list[i]) {
                word_count++;
            }
        }
        return word_count;
    }
    
    // wrapper for strtok; tokenize and remove dupes
    // returns a list of distinct words in the given sentence
    // checkValid is a flag: if 1 -> only adds word if it is also present in current dictionary
    // if checkValid is 0 -> add the word, even if not already in dictionary
    vector<string> tokenize(string sentence, int checkValid) {
        vector<string> words;
        
        // convert string to char array
        char sent[sentence.length() + 1];
        strcpy(sent, sentence.c_str());
        
        char delim[] = " ";
        char *token = strtok(sent,delim);
        while (token) { // make sure token is of type string
            
            // check if word already exits in vec
            if (find(words.begin(), words.end(), token) == words.end()) {
                if (checkValid == 1) {
                    // also check if token is valid, ie already present in dict
                    if (response_map->has_token(token)) {
                        words.push_back(token);
                    }
                }
                else {
                    // not currently in dict
                    words.push_back(token);
                }
            }
            token = strtok(NULL,delim);
        }
        return words;
    }
    
    // returns a string representing the word that occurs most in the given
    // list of words
    // note: if more than one word is tied for having highest frequency,
    // the first left-wise word in sentence gets returned
    string max_frequency_word(vector<string> words) {
        // get word token with max freq
        int max_freq = 0;
        string max_word = "";
        for (auto w : words) {
            int freq = get_token_frequency(w, words);
            if (freq > max_freq) {
                // update max
                max_freq = freq;
                max_word = w;
            }
        }
        return max_word;
    }
    
    
    // main function used by this class to textually and audibly respond to given user string input
    // there are two cases: either the AI recognizes the input as it is in dictionary, or not
    // if it does not recognize the input, it will prompt the user for an ideal response and then
    // record it in dictionary for next time (ie, this is how it "learns")
    void respond(string usr_input) {
        vector<string> word_list = tokenize(usr_input, 1);
        
        // handle case where no mapped response
        if (word_list.size() == 0) {
            
            // tokenize again but do not check if valid so as to not eliminate new words
            word_list = tokenize(usr_input, 0);
            string max_word = max_frequency_word(word_list);
            
            // must prompt user for ifhdeal response; repeat phrase
            string ideal_resp;
            string prompt = "Hmm... I'm not sure. Tell me, how would you respond to: " + usr_input + " ?";
            speak(prompt);
            getline(cin, ideal_resp);
            
            AbstractToken* newToken = new KeyWord(max_word, { ideal_resp } );
            response_map->add_token(newToken);
            
            string nprompt = "Ah, gotcha. So, what else is new?";
            speak(nprompt);
        }
        
        else {
            // get mapped responses
            string max_word = max_frequency_word(word_list);
            const AbstractToken* token = response_map->get_token(max_word);
            vector<string> responses = token->get_responses();
            
            //srand(time(NULL));
            int resp_idx = rand() % responses.size(); // +1?
            
            // speak!
            speak(responses[resp_idx]);
        }
        
    }
    
    
};
