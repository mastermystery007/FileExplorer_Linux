#ifndef DELDIR
#define DELDIR

//void removeFile(char *path);
/*
void removeFile(char *path)
{
	//cout<<"path for deleting file : "<<path<<endl;
	int status= remove(path);
	 if(status != 0)
	 {
	 	cout<<("Error in removing the File with path ::::: "+string(path));
	 }
	
}*/

void removeDirectory(char *path)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if (d) 
	{
	    while ((dir = readdir(d)) != NULL) 
	    {
		      if( (string(dir->d_name) == "..") || (string(dir->d_name) == ".") )	
		      {   } 
		  	  else
		  	  	{	
		  	  		string finalpath=string(path) + "/" +string(dir->d_name);
					char* newpath = new char[finalpath.length() + 1];
					strcpy(newpath, finalpath.c_str());
		  			struct stat sb;
					if (stat(newpath,&sb) == -1) 
					{
				        perror("lstat");
				    }
				    else
					{

				    	if((S_ISDIR(sb.st_mode)))
					    {
					    	removeDirectory(newpath);
					    }
					    else
					    {
							int status= remove(path);
	 						if(status != 0)
	 						{
	 						cout<<("Could not remove the File with path ::::: "+string(path));
	 						}
					    	
					    }
				    }		
		  		}
	    }
	    closedir(d);
	    int status= rmdir(path);
		if(-1 == status)
		{
		cout<<("Could not remove the Directory with path ::::: "+string(path));
		}
	}
	else{
		cout<<("No such Directory Exist !!!");
	}
}

#endif