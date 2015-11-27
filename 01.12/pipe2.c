#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int ball = 0;

int flag = 0;
int pid;
void w_sigusr1(int sig){
	signal(SIGUSR1, w_sigusr1);
}

void w_sigint2(int sig){
	kill(pid, SIGKILL);
}

void w_sigint(int sig){
	printf("%d\n", ball);
	signal(SIGINT, w_sigint2);	
}


int main(int argc, char const *argv[])
{
	signal(SIGUSR1, w_sigusr1);
	signal(SIGINT, w_sigint);

	pid = getpid();
	int fd[2];
	pipe(fd);
	int p = fork();
	write(fd[1], &ball, sizeof(ball));
	if (!p){
		while(1){
			read(fd[0], &ball, sizeof(ball));
			ball++;
			write(fd[1], &ball, sizeof(ball));
			kill(getppid(), SIGUSR1);
				pause();
		}
	}
	else{	
		while(1){		
			pause();
			read(fd[0], &ball, sizeof(ball));
			ball++;
			write(fd[1], &ball, sizeof(ball));
			kill(p, SIGUSR1);
		}		
	}

	return 0;
}