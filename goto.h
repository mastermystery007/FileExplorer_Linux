#ifndef GOTO
#define GOTO

#include "config.h"
#include "list_files.h"

void gotoF(vector<string> commandSplit);


void gotoF(vector<string> commandSplit)
{

        if(commandSplit.size()==2)
		{
		string path=commandSplit[1];
		DIR *d;
		char *temp2=new char[path.length()+1];
		strcpy(temp2,path.c_str());
		d=opendir(temp2);
		if(!d)
		{
		cout<<endl<<"Invalid path"<<endl<<":";
		}
		else
		listF(path);
		}
}

#endif