#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct MYFILE
{
	int fd;
	char buffer[1024];
	int bufPos, bufChars;	
};

struct MYFILE *mfopen(const char * fname, const char * mode){
	int file, a;
	if (*mode == 'r'){
		a = 1024;
		file = open(fname, O_RDONLY);
	}
	else if(*mode == 'w'){
		a = 0;
		file = open(fname, O_WRONLY|O_TRUNC);
	}
	else{
		printf("Invalid mode!\n");
		return NULL;
	}
	struct MYFILE * f = (struct MYFILE *) malloc (sizeof(struct MYFILE));
	f->fd = file;
	f->bufPos = a;
	f->bufChars = a;
	return f;
}

void mfclose(struct MYFILE *pFile){
	close(pFile->fd);
	free(pFile);
}

int gch(struct MYFILE* pFile){
	if (pFile->bufPos > pFile->bufChars)
		return EOF;

	if (pFile->bufPos == 1024){
		pFile->bufChars = read(pFile->fd, &pFile->buffer, sizeof(pFile->buffer));
		pFile->bufPos = 0;
	}
	int res = pFile->buffer[pFile->bufPos];
	pFile->bufPos++;
	return res;
}

void pch(int c, struct MYFILE *pFile){
	pFile->buffer[pFile->bufPos] = c;
	pFile->bufPos++;
	pFile->bufChars++;
	if((c == '\n') || (pFile->bufPos == 1024) || (c == EOF)){
		write(pFile->fd, pFile->buffer, pFile->bufChars);
		pFile->bufPos = 0;
		pFile->bufChars = 0;
	}
}

int main(int argc, char const *argv[])
{
	struct MYFILE* file;
	file = mfopen(argv[1], "w");
	int c;
	while ((c = getchar()) != EOF)
		pch(c, file);
	mfclose(file);
	file = mfopen(argv[1], "r");
	while ((c = gch(file)) != EOF)
		putchar(c);
	mfclose(file);
	return 0;
}