//
//  main.cpp
//  OpenALAudio
//
//  Created by michaela perrotta on 8/11/19.
//  Copyright © 2019 michaela perrotta. All rights reserved.
//

// to run: enter 'make' in terminal which will compile and link the files.
// note that if you are ssh'd into the Khoury servers, this will not run
// since it relies on the system command 'say'


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include "AI.cpp"
#include "KeyWord.hpp"

using namespace std;

// main point of control for user-chatbot interaction
int main(int argc, const char * argv[]) {
    // string tokens ie content
    string hello = "hello";
    string goodbye = "goodbye";
    string weather = "weather";
    string nba = "nba";
    string song = "sing";
    string joke = "joke";
    // roasts
    // add more...
    
    // responses
    vector<string> helloResponses = {"Whats brackin dude", "Hello, human!", "Hello, how are you", "Hey what's good", "Yo whats up",
                                    "Hi, did you know you are talking to a live chat bot" };
    
    vector<string> byeResponses = {"Sad to see you leave!", "Goodbye, fellow human", "You leave me faster than my ex husband... ", "Hope to see you again!", "farewell!" };
    
    vector<string> weatherResponses = {"Who do you think I am, Alexa?", "Like I know what the weather is...",
                        "Hmm... I'm looking outside now, looks pretty humid to me", "In Boston it is 77 degrees and partly cloudy",
        "Wind: 5 miles per hour. Temperature: 74 degrees. Humidity: 63 percent.", "A storms a brewin!" };
    
    vector<string> nbaResponses = { "Do you know the Kawhi Leonard meme: What it do baby ?",
        "Zion Williamson was the overall number one draft pick, selected by the New Orleans Pelicans.",
        "Oh I could go on about how LeBron is better than Steph Curry... but I won't waste your time.",
        "Let me try to imitate Kawhi Leonard's laugh:    ah ha ha ha ha"
    };
    
    vector<string> songResponses = { "Sweeeeeeet Caroline! (BAH BAH BAH). Good times never seemed so good... (SO GOOD! SO GOOD!)",
        "La la la la la... how was that?", "Thank you.... next! Thank you... next! I'm so greatful for my ex!"
    };
    
    vector<string> jokeResponses = { "If I make an uber driver drive backwards, does that mean he owes me money?",
        "If I work as a security gaurd at Samsung, does that make me Gardian of the Galaxy?",
        "So, this man walks into a bar.... oh you know the rest!",
        "If you clean a vacuum cleaner, doesn't that make you the vacuum cleaner",
        "If you crash a car on purpose, is it still called a car accident?",
        "Every time I start eating healthy, I see a chocolate bar and it snickers!",
        "Which travels faster, hot or cold?  Hot because you can catch a cold! Ha ha ha ha ha..."
    };
    
    // KeyWords
    // AbstractToken t = KeyWord();
    KeyWord greeting(hello, helloResponses);
    KeyWord leave(goodbye, byeResponses);
    KeyWord temperature(weather, weatherResponses);
    KeyWord bball(nba, nbaResponses);
    KeyWord sing(song, songResponses);
    KeyWord jokes(joke, jokeResponses);
    
    // build dictionary
    vector<AbstractToken*> vec = { &greeting, &leave, &temperature, &bball, &sing, &jokes };
    Dictionary dict( vec);
    
    // ai
    AI chatbot(&dict);
    
    //Welcome message
    SpeakObject speaker;
    speaker.say("Greetings! I am your personal Chat bot.");
    
    // loop until user ends session
    while(true) {
        string input;
        cout << ">USER ";
        getline(cin, input);

        cout << ">CHATBOT ";
        chatbot.respond(input);
    }
    
};
