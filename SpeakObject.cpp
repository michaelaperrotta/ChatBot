//
//  SpeakObject.cpp
//  ChatterBot
//
//  Created by michaela perrotta on 8/13/19.
//  Copyright © 2019 michaela perrotta. All rights reserved.
//

//initial terminal greeting: say Greetings! I am the chat bot. Lets get to know each other better


#include <stdio.h>
#include <iostream>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

using namespace std;

// SpeakObject is a wrapper class for the mac system command, 'say'
// it is used in order for the terminal to audibly communicate with the user
class SpeakObject {
public:
    // calls sys command so terminal will speak the given string phrase
    void say(string phrase) {
        string terminal_cmd = "say \"" + phrase + "\"";
        
        // convert string to char array for sys
        char cmd[terminal_cmd.size() + 1];
        strcpy(cmd, terminal_cmd.c_str());
        
        cout << phrase <<endl;
        
        system(cmd);
    }
    
};
