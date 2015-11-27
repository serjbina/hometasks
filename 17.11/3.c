#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	if (argc != 5){
		fprintf(stderr, "Incorrect input: 4 parametrs required\n");
		return 1;
	}
	int pid1, pid2;
	int fin = open(argv[4], O_CREAT|O_WRONLY|O_TRUNC, 0644);
	int fd[2];
	pipe(fd);
	//if (pipe(fd) <1 ){ fprintf(stderr, "Pipe failed\n"); return 2;}
	if ((pid1 = fork()) < 0){
		fprintf(stderr, "Fork failed\n");
		return 3;
	}
	if(!pid1){
		dup2(fd[1], 1);
		close(fd[0]); close(fd[1]); 
		execlp(argv[1], argv[1], NULL);
		perror("Execlp");
		_exit(0);
	}
	if ((pid2 = fork()) < 0){perror("fork"); exit(0);}
	if(!pid2){
		dup2(fd[0], 0);
		dup2(fin,1);
		close(fin);
		close(fd[0]);
		close(fd[1]);
		execlp(argv[3], argv[3], NULL);
		perror("Execlp");
		_exit(0);
	}
	close(fd[0]); close(fd[1]);
	wait(NULL); wait(NULL);
	pipe(fd);
	if ((pid1 = fork()) < 0){
		fprintf(stderr, "Fork failed\n");
		return 3;
	}
	if (!pid1){
		dup2(fd[1], 1);
		close(fd[0]); close(fd[1]); 
		execlp(argv[2], argv[2], NULL);
		perror("Execlp");
		_exit(0);
	}
	if ((pid2 = fork()) < 0) {perror("fork"); exit(0);}
	if(!pid2){
		dup2(fd[0], 0);
		dup2(fin, 1);
		close(fin);
		close(fd[0]);
		close(fd[1]);
		execlp(argv[3], argv[3], NULL);
		perror("Execlp");
		_exit(0);
	}
	close(fd[0]); close(fd[1]);
	wait(NULL); wait(NULL);
	


	return 0;

}
