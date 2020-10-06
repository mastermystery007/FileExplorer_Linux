#ifndef DELETE
#define DELETE
#include "config.h"

int deleteFile(vector<string> &commandSplit)	// It accepts arg from commandFile and delete file/files.
{
    char *remove_argument;
    
    	remove_argument= new char[commandSplit[1].length()+1];
    	strcpy(remove_argument,commandSplit[1].c_str());
    	int status=remove(remove_argument);
	    if(status!=0)
	    {
	        cout<<endl<<"No such file exists"<<endl;
	    }
		else
		{
			cout<<"successfullly deleted file"<<endl;
		}
    
    
	return 0;
}

#endif