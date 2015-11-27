#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	if (argc != 3){
		fprintf(stderr, "Incorrect input!\n");
		return 1;
	}
	int pid;
	int status;
	if((pid = fork()) < 0){
		fprintf(stderr, "Fork failed\n");
		return 2;
	}
	if(!pid){
		execlp(argv[1], argv[1], NULL);
		fprintf(stderr, "Exec failed\n");
		return 3;
	}
	else{
		wait(&status);
		if(status){
			execlp(argv[2], argv[2], NULL);
			fprintf(stderr, "Exec failed\n");
			return 3;
		}
		return 0;
	}
}
