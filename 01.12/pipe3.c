#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char str[2];
	str[0] = '-';
	str[1] = '\0';
	strcat(str, argv[2]);
	execlp("tail", "tail", str, argv[1], NULL);
	return 0;
}