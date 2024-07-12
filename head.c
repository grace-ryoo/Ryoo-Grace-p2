/**
 * head.c
 *
 * Usage: head [-c number | -n number] [files...]
 *
 *
 *
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <errno.h>





int main(int argc, char *argv[]) 
{
	int opt;
	int nflag = 0;
	int cflag = 0;
	int num = 10;
	int counter = 0;
	FILE *file;

	while((opt = getopt(argc, argv, "c:n:")) != -1)
       	{
		switch (opt) 
		{
			case 'c':
				cflag = 1;
				num = atoi(optarg);
				break;
			case 'n':
				nflag = 1;
				num = atoi(optarg);
				break;
		} // switch
	} // while
	
	if (cflag) {
	
	
	} else if (nflag) {

	} else {

	} // if

	/**
	for(; optind < argc; optind++){
		
	} // for
*/
	return 0;









} // main
