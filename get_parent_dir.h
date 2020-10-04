
#ifndef PARENT
#define PARENT

#include "config.h"


extern vector<string> path_vector;
extern string path;

void getFullWorkingDirectory(string relativePath);
string returnParentDirectory(string path);


void getFullWorkingDirectory(string relativePath) //just updates path vector
{

    if(relativePath=="/")
    {
        path_vector.clear();
        return;
    }
    
    else{
    char * fullPath = realpath(relativePath.c_str(),NULL);
    
    string fullPathString(fullPath);

    cout<<"full path is "<<fullPathString<<endl;
    
    string delimiter = "/";

    size_t pos = 0;
    std::string token;
    path_vector.clear();
    while ((pos = fullPathString.find(delimiter)) != std::string::npos) 
    {
    token = fullPathString.substr(0, pos);
    
    path_vector.push_back(token);
    fullPathString.erase(0, pos + delimiter.length());
    
    
    }
    path_vector.push_back(fullPathString);
    cout<<"this is the path vector"<<endl;
    for(int i=0;i<path_vector.size();i++)
    {
    cout<<path_vector[i]<<endl;
    }
    }
    
}

string returnParentDirectory(string path)

    
{
    getFullWorkingDirectory(path);

    string parentDir="/";
    
    if(path_vector.empty()){return parentDir;}
    
    for(int i=0;i<path_vector.size()-1;i++)
    {
        if(path_vector[i].size()!=0)
        {
            parentDir=parentDir+path_vector[i]+"/";
        }
        
    }
    
    //path =parentDir;
    cout<<"Current path is "<< path<<endl;
    return parentDir;
}

#endif