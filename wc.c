/**
 * wc.c
 *
 *
 * Usage: [-clw] [files...]
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFF 1048576 // buffer size

/**
 *
 *
 */
int main(int argc, char *argv[])
{
	int opt;
	int cflag = 0;
	int lflag = 0;
	int wflag = 0;
	int fd;

	while ((opt = getopt(argc, argv, "clw")) != -1) 
	{
		switch(opt)
		{
			case 'c':
				cflag = 1;
				break;
			case 'l':
				lflag = 1;
				break;
			case 'w':
				wflag = 1;
				break;
			case '?':
				printf("unknown option: %c\n", optopt);
				break;
		} // switch
	} // while

	if (cflag + lflag + wflag == 0) { // standard input assumed
		cflag = lflag = wflag = 1;
	} // if

	if (cflag) {
		
	} // if

	if (lflag) {

	} // if
	
	if (wflag) {

	} // if

	for(; optind < argc; optind++) {

	} // for


	return 0;







} // main
