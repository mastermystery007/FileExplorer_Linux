#ifndef COMMAND
#define COMMAND
#include "config.h"
#include "make_directory.h"
#include "rename_dir.h"
#include "search_file.h"
#include "goto.h"
#include "delete_file.h"
#include "delete_dir.h"
#include "move.h"
#include "copy.h"
//todo 
/*
cursor implementatiom
forward stack
open file when enter pressed
change variable names
empty formulatedCommands for next command
up page down page implementation
open directory when goto
create file ​as --> create_file foo.txt ~/foobar
Copying/Moving directories should also be implemented
*/
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




        if(!isspace(c))
        {
        typedString+=c;
        }

         
        
        //escape pressed
        if(c=='q'){}

        if(c==10)
        {
            cout<<"enter pressed";
            formulatedCommands.push_back(typedString);

            if(formulatedCommands[0]=="create_dir")
            {
                createDir(formulatedCommands);
                cls();
            }

           else  if(formulatedCommands[0]=="rename")//rename(/home/mystery/Pictures,/home/mystery/Pics)
            {
                cls();
                rename(formulatedCommands);
                
            }

            else  if(formulatedCommands[0]=="move")//move(/home/mystery/Pictures,/home/mystery/Downloads/Pics)
            {
                //not working

                cls();
               // moveFD(formulatedCommands);
                
            }

            else  if(formulatedCommands[0]=="copy")//move(/home/mystery/Pictures,/home/mystery/Downloads/Pics)
            {
                //not working

                cls();
                copyDirectory(formulatedCommands[1],formulatedCommands[2]);
                
            }



           else if(formulatedCommands[0]=="goto")//goto(/home/mystery/Pictures/)
            {
              //  deleteDir(formulatedCommands);
              cls();
              gotoF(formulatedCommands);
                
            }

            else if(formulatedCommands[0]=="delete_file") //deleteFile(/home/mystery/Pictures/lastest.png)
            {
             
              cls();
              
              deleteFile(formulatedCommands);
                
            }

            else if(formulatedCommands[0]=="delete_dir") //(delete directory,/home/mystery/Pictures)
            {
              //  deleteDir(formulatedCommands);/home/mystery/Pictures/testdir
                cls();
              
                char *deletedir;
                deletedir= new char[formulatedCommands[1].length()+1];
                strcpy(deletedir,formulatedCommands[1].c_str());

                cout<<deletedir;
                removeDirectory(deletedir);
                
            }



            else if(formulatedCommands[0]=="search_file")
            {

                cls ();
                vector<string> res = search(formulatedCommands);

                for(int i=0;i<res.size();i++)
                {
                    cout<<res[i]<<endl;
                }
                //cls ();
            }
            
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