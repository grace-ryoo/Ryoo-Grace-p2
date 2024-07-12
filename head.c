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

 #define BUFF 1048576 // buffer size 





int main(int argc, char *argv[]) 
{
	int opt;
	int nflag = 0;
	int cflag = 0;
	int num = 10;
	int fd;


	while((opt = getopt(argc, argv, "c:n:")) != -1)
       	{
		switch (opt) 
		{
			case 'c':
				cflag = 1;
				num = atoi(optarg);
				if (num <= 0) {
					fprintf(stderr, "Error: number must be a positive integer.\n");
					exit(EXIT_FAILURE);
				} // if
				break;
			case 'n':
				nflag = 1;
				num = atoi(optarg);
				if (num <= 0) {
					fprintf(stderr, "Error: number must be a positive integer.\n");
					exit(EXIT_FAILURE);
				} // if
				break;
		} // switch
	} // while
	
	if (cflag && nflag) {
		fprintf(stderr, "Error: cannot combine -c and -n options.");
		exit(EXIT_FAILURE);
	} // if

	if (optind == argc) {
		if (cflag) {
			c_bytes(STDIN_FILENO, num);
		} else if (nflag) {
			n_lines(STDIN_FILENO, num);
		} // if
	} else {
		for(; optind < argc; optind++){
			if (strcmp(argv[optind], "-") == 0) {
				fd = STDIN_FILENO;
			} else {
				fd = open(argv[optind], O_RDONLY);
				if (fd == -1) {
					fprintf(stderr, "cannot open file %s: %s\n", argv[optind], strerror(errno));
					continue;
				} // if
			} // if
		} // for
		
		if (cflag) {
			c_bytes(fd, num);
		} else if (nflag) {
			n_lines(fd, num);
		} // if

	return 0;


} // main
