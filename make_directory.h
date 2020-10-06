#ifndef MAKEDIR
#define MAKEDIR

// creareDir("latest","/home/mystery/Pictures)
#include "config.h"

int createDir(vector<string> &commandSplit)	;

int createDir(vector<string> &commandSplit)	// It accepts arg from commandFile and create a directory
{
	//struct stat fileStat,fileStat1;
	string destination=commandSplit[commandSplit.size()-1];
	char *create_dir_argument;
  
    	string s=destination+"/"+commandSplit[1];
    	create_dir_argument= new char[s.length()+1];
    	strcpy(create_dir_argument,s.c_str());
    	int status= mkdir(create_dir_argument, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IXOTH);
    	if(status!=0)
	    {
	        cout<<endl<<"Invalid path"<<endl;
	    }
    
    return 0;
}

#endif