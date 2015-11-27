#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFF_SIZE 10

int main(int argc, char const *argv[])
{
	int file1, file2;
	int fout;

	file1 = open(argv[1], O_RDONLY);
	file2 = open(argv[2], O_RDONLY);
	fout = open("output.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
	int g;
	char buff[BUFF_SIZE];
	while((g = read(file1, buff, BUFF_SIZE)) == BUFF_SIZE){
		write(fout, buff, BUFF_SIZE);
	}
	write(fout, buff, g);
	while((g = read(file2, buff, BUFF_SIZE)) == BUFF_SIZE){
		write(fout, buff, BUFF_SIZE);
	}
	write(fout, buff, g);
	close(file2); close(file1); close(fout);
	return 0;
}