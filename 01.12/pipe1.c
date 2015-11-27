#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int fd1[2], fd2[2];
	pipe(fd2); pipe(fd1);
	int p = fork();
	if (p){
		int ball = 1;
		while(1){
			write(fd1[1], &ball, sizeof(ball));
			read(fd2[0], &ball, sizeof(ball));
			ball++;
			printf("My pid = %d Ball = %d\n", getpid(), ball);
			sleep(1);	
		}
	}
	else{
		while(1){
			int ball;
			read(fd1[0], &ball, sizeof(ball));
			ball++;
			write(fd2[1], &ball, sizeof(ball));
			printf("My pid = %d Ball = %d\n", getpid(), ball);
			sleep(1);	
		}	
	}
	return 0;
}