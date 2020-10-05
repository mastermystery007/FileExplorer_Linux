#ifndef COMMAND
#define COMMAND
#include "config.h"


vector<string> formulatedCommands;
extern string path;

string typedString;
void cls();

void cls()
{
    cout << "\033[2J\033[1;1H";
}




void enterCommandMode(struct termios term_p)
{   
    tcsetattr( 1 , TCSANOW, &term_p);
    cls();

    typedString="";

    char c;
    while(1)
    {
        
        c=cin.get();
        //cout<<"char entered"<<"\n";

        typedString+=c; 
        
        //if(c=='/0'){}
        if(c=='q'){}

        if(c==10)
        {
            cout<<"enter pressed";
            formulatedCommands.push_back(typedString);
            typedString="";
        }

        else if(isspace(c))
        {
        //cout<<"you have entered a blank space";
        formulatedCommands.push_back(typedString);
        typedString="";
        }

    }
}


#endif