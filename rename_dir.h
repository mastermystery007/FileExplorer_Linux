#ifndef RENAME
#define RENAME


#include "config.h"
#include "commandMode.h"
#include "get_parent_dir.h"
//commnads can be relative to current directory or can be absolute path
//rename_dir /home/mystery/Pictures Pics
//rename_dir ./testover testing
// It accepts arg from command and rename file/dir 
int rename(vector<string> commandSplit);


int rename(vector<string> commandSplit)	
{
	string path = commandSplit[1];
	
	string pathparent = returnParentDirectory(path);

	pathparent =pathparent+commandSplit[2];
	string oldpathName =realpath(path.c_str(),NULL); 

	
	

	char *_old=new char[oldpathName.length()+1];
	char *_new=new char[pathparent.length()+1];
	strcpy(_old,oldpathName.c_str());
	strcpy(_new,pathparent.c_str());
	//cout<<"new path is "<<_new<<endl;
	//cout<<"old path is ="<<_old<<endl;
   	
   	int status=rename(_old,_new);
   	if(status!=0)
   	{
   		cout<<endl<<"No such file exists"<<endl;
   	}
    else
    {
        cout<<"renamed"<<endl;
        
    }
	return 0;
}

#endif