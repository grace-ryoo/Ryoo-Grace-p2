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
	
off_t bytes_total = 0;
int lines_total = 0;
int words_total = 0;

/**
 *
 *
 */
void bytes_size(int fd, char *file) 
{
	off_t bytes_size = lseek(fd, 0, SEEK_END);

	if (bytes_size == -1) {
		perror("lseek");
	} else {
   		printf("The number of bytes in %s is %ld.\n", file, bytes_size);
		bytes_total += bytes_size;
	} // if
	
	lseek(fd, 0, SEEK_SET);

} // bytes_size

/**
 *
 *
 */
void new_lines_size(int fd, char *file) 
{
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
		lines_total += counter;
	} // if
	
	lseek(fd, 0, SEEK_SET);
} // new_lines_size

/**
 *
 *
 */
void words_size(int fd, char *file) 
{
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
		words_total += counter;
	} // if
	
	lseek(fd, 0, SEEK_SET);
} // words_size

/**
 *
 *
 */
void filing(char *file, int cflag, int lflag, int wflag) 
{
	int fd = (strcmp(file, "-") == 0) ? STDIN_FILENO : open(file, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return;
	} // if
		
	if (cflag) { // number of bytes
		bytes_size(fd, file);
	} // if

	if (lflag) { // number of newlines
		new_lines_size(fd, file);
	} // if

	if (wflag) { // number of words
		words_size(fd, file);
	} // if
	
	if (fd != STDIN_FILENO) {
		close(fd);
	} // if
} // filing

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

	if (optind >= argc) { // standard input assumed if no files specified
		filing("-", cflag, lflag, wflag);
	} else {
		for (int i = optind; i < argc; i++) {
			filing(argv[i], cflag, lflag, wflag);  
		} // for
	} // if

	if (argc - optind > 1) {
		if (cflag) {
			printf("The total number of bytes is %ld\n", bytes_total);
		} // if
		
		if (lflag) {
			printf("The total number of newlines is %d\n", lines_total);
		} // if
	
		if (wflag) {
			printf("The total number of words is %d\n", words_total);
		} // if
	} // if

	return 0;



} // main
