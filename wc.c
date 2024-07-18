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
#include <errno.h>
#include <fcntl.h>

#define BUFF 1048576 // buffer size

/**
 *
 *
 */
void bytes_size(char *file) 
{
	int fd = open(file, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return;	
	} // if

	off_t bytes_size = lseek(fd, 0, SEEK_END);

	if (bytes_size == -1) {
		perror("lseek");
	} else {
   		printf("The number of bytes in %s is %ld.\n", file, bytes_size);
	} // if
	
	close(fd);	

} // bytes_size

/**
 *
 *
 */
void new_lines_size(char *file) 
{
	int fd = open(file, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return;	
	} // if
	
	int counter = 0;
	int n;
	char buffer[BUFF];

	while((n = read(fd, buffer, BUFF)) > 0) {
		for (int i = 0; i < n; i++) {
			if (buffer[i] == '\n') {
				counter++;
			} // if
		} // for
	} // while
	
	if (n == -1) {
		perror("read");
	} else {
		printf("The number of newlines in %s is %d.\n", file, counter);
	} // if

	close(fd);
} // new_lines_size

/**
 *
 *
 */
void words_size(char *file) 
{
	int fd = open(file, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return;	
	} // if
	
	int counter = 0;
	int n;
	char buffer[BUFF];
	int word = 0;

	while((n = read(fd, buffer, BUFF)) > 0) {
		for (int i = 0; i < n; i++) {
			if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
				word = 0;
			} else if (word == 0) {
				word = 1;
				counter++;
			} // if
		} // for
	} // while
	
	if (n == -1) {
		perror("read");
	} else {
		printf("The number of words in %s is %d.\n", file, counter);
	} // if

	close(fd);

} // words_size

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

	if (optind >= argc) {
		fprintf(stderr, "missing file names\n");
		exit(EXIT_FAILURE);
	} // if
	
	for (int i = optind; i < argc; i++) {
		char *file = argv[i];
		
		if (cflag) { // number of bytes
			bytes_size(file);
		} // if

		if (lflag) { // number of newlines
			new_lines_size(file);
		} // if

		if (wflag) { // number of words
			words_size(file);
		} // if
		  
	} // for



	return 0;



} // main
