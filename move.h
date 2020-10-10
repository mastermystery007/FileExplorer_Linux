#ifndef MOVE
#define MOVE

#include "config.h"

int move(vector<string> commands)
{
  int result=1;
  char *oldname;
  strcpy(oldname,commands[1].c_str());
  char *newname;
  strcpy(newname,commands[2].c_str());
  
  result = rename( oldname , newname );
  if ( result == 0 )
    cout << "File successfully moved" << endl;
  else
    cout << "Error moving file" << endl;
  return 0;
}
#endif