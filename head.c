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
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFF 1048576 // buffer size 

/**
 *
 *
 */
void c_bytes(int fd, int bytes_num) 
{
	int total = 0;
	ssize_t read_bytes = 0;
	char buffer[BUFF];

	while ((read_bytes = read(fd, buffer, BUFF)) > 0) {
		if (total + read_bytes > bytes_num) {
			read_bytes = bytes_num - total;
		} // if
		
		write(STDOUT_FILENO, buffer, read_bytes);
		total += read_bytes;
		if (total >= bytes_num) {
			break;
		} // if
	} // while
	
	write(STDOUT_FILENO, "\n", 1);
} // c_bytes
 
/**
 *
 *
 */
void n_lines(int fd, int lines_num)
{
	char buffer[BUFF];
	int counter = 0;
	ssize_t read_bytes;
	char *ptr;
	char *nxt;
	
	while ((read_bytes = read(fd, buffer, BUFF)) > 0) {
		ptr = buffer;
		while (read_bytes > 0 && counter < lines_num) {
			nxt = memchr(ptr, '\n', read_bytes);
			if (nxt != NULL) {
				nxt++;
				write(STDOUT_FILENO, ptr, nxt - ptr);
				counter++;
				read_bytes -= (nxt - ptr);
				ptr = nxt;
			} else {
				write(STDOUT_FILENO, buffer, read_bytes);
				break;
			} // if
		} // while
		if (counter >= lines_num) {
			break;
		} // if
	} // while

	write(STDOUT_FILENO, "\n", 1);
} // n_lines
 

/**
 *
 *
 */
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
		fprintf(stderr, "Error: cannot combine -c and -n options.\n");
		exit(EXIT_FAILURE);
	} // if

	if (optind == argc) {
		if (cflag) {
			c_bytes(STDIN_FILENO, num);
		} else if (nflag) {
			n_lines(STDIN_FILENO, num);
		} // if
	} else {
		int file_one = 1;
		for(; optind < argc; optind++) {
			if (!file_one) {
				write(STDOUT_FILENO, "\n", 1);
			} // if
			
			file_one = 0;

			if (strcmp(argv[optind], "-") == 0) {
				fd = STDIN_FILENO;
			} else {
				fd = open(argv[optind], O_RDONLY);
				if (fd == -1) {
					fprintf(stderr, "cannot open file %s: %s\n", argv[optind], strerror(errno));
					continue;
				} // if
			} // 	
	
			if (cflag) {
				c_bytes(fd, num);
			} else if (nflag) {
				n_lines(fd, num);
			} // if

			close(fd);
		} // for
	} // if
	
	return 0;

} // main
