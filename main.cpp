#include <iostream>
#include <termios.h>
#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<bits/stdc++.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<termios.h>
#include<pwd.h>
#include<grp.h>
#include<fstream>
#include <sys/ioctl.h>
#include "list_files.h"
#include "get_parent_dir.h"
#include "set_Noncanonical.h"
#include "commandMode.h"




using namespace std;


int cursorX,cursorY;
int rows, col;
//DIR *cur_dir;
struct winsize w;
struct termios old_terminal;



int path_pos;
int upper, low;
bool first=true;
int cursor;
string path ;
vector <string > path_vector; //stores the full current path as string with delimiter "/"(/home/username ->[home,username])
stack <string> backPathStack; //stack used for navigation on backspace and forward space
stack <string> frontPathStack;
vector <vector<string> > directories; //current list of directories in current folder
void printCursor(int x,int y);
void clearScreen();




/*void list_dir(const char *path) {
   struct dirent *entry;
   DIR *dir = opendir(path);
   
   if (dir == NULL) {
      return;
   }
   while ((entry = readdir(dir)) != NULL) {
   cout << entry->d_name << entry->d_type << endl;
   }
   closedir(dir);
}*/

bool isDirectory(string dirPath)
{
 return true;
}


void printCursor(int x,int y)
{
    printf("\033[%d;%dH", x, y);
}

void clearScreen()
{
    cout << "\033[2J\033[1;1H";
}




int main(){
 
    int cursorX=1;
    int cursorY=1;
    setNonCanonical();
    path = "./";
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row - 3;
    col = w.ws_col;
    listF(path);
    //backPathStack.push(realpath(path.c_str(),NULL));
    
    printf("\033[%d;%dH", 1, 1);
    
    while(1)
    {   //take input and move around
        char in;
        cin>>in;
        if(in== 'A')
        {
            if(cursorX>1){}
            cursorX++;
            printCursor(cursorX,cursorY);

        }
        if(in== 'B')
        {
            cursorX--;
            printCursor(cursorX,cursorY);

        }

        if(in=='C') //go to parent directory 
        {
            
            //cout<<"this goes in"<<realpath(path.c_str(),NULL)<<endl;
            cout<<realpath(path.c_str(),NULL);
            
            string actualPath = realpath(path.c_str(),NULL);
            actualPath = actualPath+"/"  ;
            backPathStack.push(actualPath);

          
            clearScreen();
           
           
                         
            path = returnParentDirectory(path);//iterates over path 
            
            listF(path);
            
            
            cout<<"updated path is "<<path<<endl;
        
        
        }

         if(in=='D')  
        {
            
            // cout<<"youre looking for this"<<backPathStack.top()<<endl;
           if(!backPathStack.empty()) 
           {
            cout<<"youre looking for this"<<backPathStack.top()<<endl;
            path = backPathStack.top();
            backPathStack.pop();
            cout<<"current path "<<path<<endl;           
            clearScreen();
            
            listF(path);
            
            
           }

           cout<<"updated path is "<<path<<endl;
        }

        if(in=='P') //enter directory
        {   
            //clearScreen();
            cout<<"cursor position is "<<cursorX<<"+"<<cursorY<<endl;
            /*for(int i=0;i<directories.size();i++)
            {
                cout<<"i= "<<i<<" and file="<<directories[i][0]<<endl;
            }*/
            cout<<"file details "<<directories[cursorX-1][0]<<" +folder "<<directories[cursorX-1][4]<<endl;

            string isFolder = directories[cursorX-1][4];

            if(isFolder[0]=='d')
            {
                cout<<" it is a directory ";
                clearScreen();
                backPathStack.push(path);
                path=path+directories[cursorX-1][0]+"/";
                
                listF(path);
            }
            else
            {
                cout<<"not a directory";
                //open the file in vim 
            }
            
            
            /*string dirPath;
            if(isDirectory(dirPath))
            {
                backPathStack.push(path);
                path = path+dirPath;
                clearScreen();
               // listF(dirPath);


            }*/
        }

        if(in ==':')
        {
            enterCommandMode(old_terminal);
        }


    }
    
    return 0;
}

