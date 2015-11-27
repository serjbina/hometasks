#include <stdlib.h>
#include <stdio.h>

int main(){
	FILE * output = fopen("inputfile.txt", "w");
	FILE *output2 = fopen("inputfile2.txt", "w");
	fprintf(output2, "12341234567890qqabc");
	fprintf(output, "12341234567890qqabc");
	fclose(output);
	fclose(output2);
	return 0;
}
