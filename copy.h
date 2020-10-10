#ifndef COPY
#define COPY

#include "config.h"
void copyFile(string fromPassed , string toPassed){

    string from = fromPassed;
    string to = toPassed;
    int from_int, to_int;
    char buffer[1024];
    long long size;

    from_int = open(from.c_str(), O_RDONLY) ;
    to_int=open(to.c_str(),O_CREAT|O_WRONLY|O_TRUNC, 0700) ;

    if(from_int == -1)
    {
        cout<<"error opening source file"<<endl;
    }
    if(to_int   ==  1)
    {
        cout<<"error opening destination file"<<endl;
    }
    
    while((size=read(from_int, buffer, 1024)) > 0)
    {
        write(to_int, buffer, size);
    }

    struct stat sb;
    stat(from.c_str(), &sb);
    chown(to.c_str(), sb.st_uid, sb.st_gid);
    chmod(to.c_str(), sb.st_mode);

    close(from_int);
    close(to_int);

     cout<<"from = "<<from <<"and to="<<to<<endl;
}



void copyDirectory(string source,string destination)
{  
    DIR *DIR;
    struct dirent *entry;
    struct stat stat_dir;
    string frompath,topath;

    stat(source.c_str(), &stat_dir);
    if(S_ISDIR(stat_dir.st_mode) == 0){
        return;
    }

    if( DIR = opendir(source.c_str()) )
    {
        while(entry = readdir(DIR))
        {
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
                continue;

            frompath=source;
            frompath.append("/").append(entry->d_name);

            struct stat buf;
            stat(frompath.c_str(), &buf);
            if(S_ISDIR(buf.st_mode)!=0){
                topath=destination;
                topath.append("/").append(entry->d_name);
                cout<<"making directory: "<<topath<<endl;
                mkdir(topath.c_str(),0755);
                copyDirectory(frompath, topath);
            }
            else{
                topath=destination;
                topath.append("/").append(entry->d_name);
                cout<<"copying from "<<frompath<<" to "<<topath<<endl;
                copyFile(frompath, topath);
            }
        }
        closedir(DIR);
    }
}


#endif