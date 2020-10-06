#ifndef NONCANON
#define NONCANON


#include "config.h"



void setNonCanonical();
extern struct termios old_terminal;

void setNonCanonical(){

	tcgetattr ( 1 , &old_terminal);
	struct termios new_terminal = old_terminal;
	new_terminal.c_lflag &= ~ICANON;
	new_terminal.c_lflag &= ~ECHO;
	new_terminal.c_cc[VMIN] = 1;
	new_terminal.c_cc[VTIME] = 0;
	tcsetattr( 1 , TCSANOW, &new_terminal);
	
}

#endif