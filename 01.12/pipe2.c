#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>


int ball = 0;
time_t *SigIntTime;
int FirstPress = 1;

int pid;
void w_sigusr1(int sig){
	signal(SIGUSR1, w_sigusr1);
}


void w_sigint(int sig){
	time_t *CurrentTime = (time_t *) malloc(sizeof(time_t)); 
	time(CurrentTime);
		if(FirstPress){
			SigIntTime = CurrentTime;
			FirstPress--;
			if (getpid() == pid)
				printf("%d\n", ball);
			signal(SIGINT, w_sigint);
			return;
		}
	if(getpid() == pid)
		printf("%d\n", ball);
	if (difftime(*CurrentTime, *SigIntTime) < 1)
		kill(pid, SIGKILL);
	SigIntTime = CurrentTime;
	signal(SIGINT, w_sigint);	
}


int main(int argc, char const *argv[])
{

	//SigIntTime = (time_t*) malloc(sizeof(time_t));	
	signal(SIGUSR1, w_sigusr1);
	signal(SIGINT, w_sigint);

	pid = getpid();
	int fd[2];
	pipe(fd);
	write(fd[1], &ball, sizeof(ball));
	int p = fork();
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