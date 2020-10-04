#ifndef LIST
#define LIST

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <stack>
#include <cstddef>
#include <pwd.h>
#include <grp.h>


using namespace std;

extern int rows, col;

extern string path;
extern vector <vector<string> > directories;


extern int  low;
extern int cursor;
  
DIR *cur_dir;

string size_of_file(off_t size);
vector<vector<string> > list_store(string path);
void list_display( int lower);
void listF(string path);

string size_of_file(off_t size)
{
	long int KB = 1024;
	long int MB = 1024*1024;
	long int GB = 1024*1024*1024;
	if(size < KB )
		return to_string(size) + " B";
	else if( size < MB )
	{
		size = size/KB;
		return to_string(size) + " KB";
	}
	else if( size < GB )
	{
		size = size/MB;
		return to_string(size) + " MB";
	}
	else 
	{
		size = size/GB;
		return to_string(size) + " GB";
	}
}
string permission(mode_t mod)
{
	string perm;
	if( mod & S_IFDIR)  perm += 'd';
	else 			    perm += '-';
	if( mod & S_IRUSR)     perm += 'r';
	else                perm += '-';
	if( mod & S_IWUSR) 	perm += 'w';
	else				perm += '-';
	if( mod & S_IXUSR)	perm += 'x';
	else				perm += '-';
	if( mod & 0040)		perm += 'r';
	else				perm += '-';
	if( mod & 0020)		perm += 'w';
	else				perm += '-';
	if( mod & 0010)		perm += 'x';
	else				perm += '-';
	if( mod & 0004)		perm += 'r';
	else				perm += '-';
	if( mod & 0002)		perm += 'w';
	else				perm += '-';
	if( mod & 0001)		perm += 'x';
	else				perm += '-';
	return perm;
}

     
    


vector<vector<string> > list_store(string path)
{
	directories.clear();
	struct dirent* folder;

	cur_dir = opendir (path.c_str()); 
	
	if (cur_dir != NULL)
	{
		while ((folder = readdir(cur_dir)))
		{
			struct stat file_info;
			string file_path = path + folder->d_name;
			stat(file_path.c_str(),&file_info);
			vector<string> fields;
			fields.push_back(folder->d_name); 
			
			fields.push_back(size_of_file(file_info.st_size)); 
			
			struct passwd *pwd = getpwuid(file_info.st_uid);
			if( pwd )
				fields.push_back(string(pwd->pw_name)); 
			else 
				fields.push_back("error");
			struct group *group_info = getgrgid(file_info.st_gid);
			if( group_info )
				fields.push_back(string(group_info->gr_name)); 
			else
				fields.push_back("error");
			fields.push_back(permission(file_info.st_mode)); 	
			
			fields.push_back(string(ctime(&file_info.st_mtime))); 
			if(S_IFDIR & file_info.st_mode)
				fields.push_back("dir");
			else 
				fields.push_back("file");
			directories.push_back(fields);
		}
	    closedir(cur_dir);
	}
	else
		cout << "Directory Not Found!";
	return directories;
}


void list_display( int lower)
{
	
	printf("\033[2J\033[H");
	
	
	for ( int i=0;  i <lower && i<directories.size();i++ )//use for loop
	{
		cout  << i+1 << "." << "\t";
		cout  <<left<<setw(20)<<directories[i][0];
		cout  <<left<<setw(9)<<directories[i][1];
		cout  <<left<<setw(12)<< directories[i][2]; 
		cout  <<left<<setw(12) <<directories[i][3];
		cout  <<left<<setw(16)<< directories[i][4];
		cout  <<left<<setw(12)<<directories[i][5];
		
	}
}



void listF(string pathL)
{
	path = pathL;
	directories.clear();
	directories = list_store(path);
	
	low = rows;
	list_display(low);
	cout << endl << endl << path << endl;
	
	//gotoxy(0,0);
	cursor = 0;
}

#endif