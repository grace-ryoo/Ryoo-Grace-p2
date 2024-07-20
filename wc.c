/**
 * wc.c
 *
 * Implements the wc utility. The utility reads one or more input files and writes the number of bytes, newlines, and/or words in each input file to the standard output according to the options specified. If more than one input file is specified, the utility will write a total count for all named files.
 *
 * Usage: [-clw] [files...]
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
 * Calculates and writes the number of bytes to standard output from the file descriptor 'fd'.
 *
 * @param fd The file descriptor read from.
 * @param file The name of the file.
 *
 * A standard error message is printed if an error occurs while reading.
 */
void bytes_size(int fd, char *file) 
{
	off_t bytes_size = 0;
	int n;
	char buffer[BUFF];
	
	while((n = read(fd, buffer, BUFF)) > 0) {
		bytes_size += n;
	} // while
	
	if (n == -1) {
		perror("read");
	} else {
   		printf("%ld ",  bytes_size);
		bytes_total += bytes_size;
	} // if	

} // bytes_size

/**
 * Calculates and writes the number of newlines to standard output from the file descriptor 'fd'.
 *
 * @param fd The file descriptor read from.
 * @param file The name of the file.
 *
 * A standard error message is printed if an error occurs while reading.
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
		printf("%d ", counter);
		lines_total += counter;
	} // if
	
} // new_lines_size

/**
 * Calculates and writes the number of words to standard output from the file descriptor 'fd'.
 *
 * @param fd The file descriptor read from.
 * @param file The name of the file.
 *
 * A standard error message is printed if an error occurs while reading.
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
		printf("%d ", counter);
		words_total += counter;
	} // if
	
} // words_size

/**
 * Processes the file or standard input to be computed and performs options according to the options specified.
 *
 * @param file The name of the file or '-' for standard input.
 * @param cflag A flag representing whether to calculate the number of bytes.
 * @param lflag A flag representing whether to calculate the number of newlines.
 * @param wflag A flag representing whether to calculate the number of words.
 */
void filing(char *file, int cflag, int lflag, int wflag) 
{
	int fd = (strcmp(file, "-") == 0) ? STDIN_FILENO : open(file, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return;
	} // if
		
	if (lflag) { // number of newlines
		new_lines_size(fd, file);
		lseek(fd, 0, SEEK_SET);
	} // if

	if (wflag) { // number of words
		words_size(fd, file);
		lseek(fd, 0, SEEK_SET);
	} // if
	
	if (cflag) { // number of bytes
		bytes_size(fd, file);
		lseek(fd, 0, SEEK_SET);
	} // if
	
	if (fd != STDIN_FILENO) {
		close(fd);
	} // if
	  
	if (cflag || lflag || wflag) {
		printf("%s\n", file);
	} // if
} // filing

/**
 * Parses and processes command line arguments to calculate bytes, newlines, and/or words from input to standard output.
 *
 * If more than one input file is specified, the function will return a total count for all named files.
 * Any combination of '-c', '-l', and '-w' options should be handled.
 * Standard input is assumed if no files are specified or when one of the files is '-'.
 *
 * @param argc The total number of command line arguments.
 * @param argv The array of command line argument strings.
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
				fprintf(stderr, "unknown option: %c\n", optopt);
				exit(EXIT_FAILURE);
		} // switch
	} // while

	if (cflag + lflag + wflag == 0) { // -clw default assumed if no options specified
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
			printf("The total number of bytes is %ld.\n", bytes_total);
		} // if
		
		if (lflag) {
			printf("The total number of newlines is %d.\n", lines_total);
		} // if
	
		if (wflag) {
			printf("The total number of words is %d.\n", words_total);
		} // if
	} // if

	return 0;



} // main
