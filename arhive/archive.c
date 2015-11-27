
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MakeInt(char *str){
	if ( (*str) < '0' || (*str) > '9')
		return -1;
	short res = 0;
	while(*str != '\0'){
		res *= 10;
		res += *str - '0';
		str++;
	}
	return res;
}

int lastblock = 0;

char *ReadBlock(FILE *file, short N){
	char *block = malloc(N);
	int i;
	int flag;
	for(i=0; i<N; i++){
		flag = fscanf(file, "%c", &block[i]);
		if (flag == -1){
			lastblock++;
			block[i] ='\0';
			return block;
		}
	}
	return block;
}

struct element{
	char *block;
	struct element *next;
};

struct element* AddBlock(struct element * list, char *block){
	if (list == NULL){
		list = malloc(sizeof(struct element));
		list->block = block;
		list->next = NULL;
		return list;
	}
	else{
		struct element *head = list;
		while(list->next != NULL){
			if(!strcmp(list->block, block))
				return head;
			list = list->next;
		}
		if (!strcmp(list->block, block))
			return head;
		else{
			list->next = malloc(sizeof(struct element));
			list = list->next;
			list->next = NULL;
			list->block = block;
		list = head;
		return list;
		}
	}
	
}

short ListLength(struct element *list){
	short res=0;
	while(list != NULL){
		list = list->next;
		res++;
	}
	return res;
}

void PrintList(struct element *list, short N){
	while(list != NULL){
		int i;
		for (i=0; i<N; i++)
			printf("%c", list->block[i]);
		printf("\n");
		list = list->next;
	}
}

void FPrintList(FILE * output, struct element *list, short N){
	struct element *head = list;
	while(list != NULL){
		int i;
		for (i=0; i<N; i++)
			fprintf(output, "%c", list->block[i]);
		//printf("\n");
		list = list->next;
	}
	list = head;
}

int BlockCmp(char *block_1, char* block_2, int N){
	int i;
	for(i = 0; i<N; i++)
		if(block_1[i] != block_2[i])
			return 1;
	return 0;

}

void Arc(FILE *input, FILE *output, struct element *list, int N){
	short i;
	lastblock = 0;
//	printf("Arc %d\n", lastblock);
	while(!lastblock){
		i = 0;
		char *block = ReadBlock(input, N);
//		printf("scan %d\n", lastblock);
//		for(i=0; i<N; i++)
//			printf("b %c", block[i]);
//		printf("\n");
//		i=0;
		struct element *head = list;
		while(list != NULL){
//			printf("search\n");
			if(!BlockCmp(list->block, block, N)){
				fprintf(output, "%hd", i);
//				printf("print\n");
				break;
			}
			list = list->next;
			i++;
		}
		list = head;
	}

}

int main(int argc, char *argv[]){
	char *input;
	short N;
	if (argc == 3){
		 input = argv[1];
		 N = MakeInt(argv[2]);
	}
	else if (argc == 2){
		N = MakeInt(argv[1]);
		if (N == -1){
			input = argv[1];
			N = 32;
		}
		else{
			char str[] = "stdin\0";
			input = str;
		}
	}
	FILE * fin = fopen(input, "r");
//	printf("%d %s", N, input);
//	printf("\n");
	struct element * list = NULL;
	short lastlength;
	//while(!lastblock)
	do{
		char * block = ReadBlock(fin, N);
		list = AddBlock(list, block);
		if(lastblock)
			lastlength = strlen(block);
	}while(!lastblock);
	fclose(fin);
	fin = fopen(input, "r");
	FILE *fout = fopen(strcat(input, ".coded"), "w");
//	printf("%d\n", ListLength(list));
//	printf("%s", input);
	fprintf(fout, "%hd", N);
	fprintf(fout, "%hd", ListLength(list));
	fprintf(fout, "%hd", lastlength);
	FPrintList(fout, list, N);
	Arc(fin, fout, list, N);
	
//	PrintList(list, N);
//	printf("%d\n", lastlength);
	return 0;
}
