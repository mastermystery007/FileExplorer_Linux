#ifndef RENAME
#define RENAME


#include "config.h"
#include "commandMode.h"
//rename(/home/mystery/Pictures,/home/mystery/Pics)
int rename(vector<string> &commandSplit);


int rename(vector<string> &commandSplit)	// It accepts arg from command and rename file/dir 
{
	char *old=new char[commandSplit[1].length()+1];
	char *_new=new char[commandSplit[2].length()+1];
	strcpy(old,commandSplit[1].c_str());
	strcpy(_new,commandSplit[2].c_str());
   	
   	int status=rename(old,_new);
   	if(status!=0)
   	{
   		cout<<endl<<"No such file exists"<<endl;
   	}
    else
    {
        cout<<"renamed"<<endl;
        cout<<"full paht "<<realpath("./",NULL);
    }
	return 0;
}

#endif