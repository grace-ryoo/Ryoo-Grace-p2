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






int main(int argc, char *argv[]) 
{
	int opt;
	int nflag = 0;
	int cflag = 0;
	int num = 10;
	FILE *file;

	while((opt = getopt(argc, argv, "c:n:")) != -1) {
		switch (opt) {
			case 'c':
				cflag = 1;
				break;
			case 'n':
				nflag = 1;
				break;
		} // switch
	} // while






} // main
