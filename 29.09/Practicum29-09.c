#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char boofer = '\0';

char* ReadWord()
{
	if (boofer != '\0'){
		char *point = (char*) malloc (2);
		char *p = point;
		*p = boofer;
		p++;
		*p = '\0';
		boofer = '\0';
		return point;
	}
	char c;
	int buff_size = 10, i=-1, n=2;
	char *word = (char*) malloc(buff_size);
	char *p = word;
	int in_word = 0, in_quotes = 0; 	
	while(1){
		i++; 
		if (i == 10){
			word = realloc(word, n*buff_size);
			i = 0;
			n++;
		}
		c = getchar();
		if (c == EOF){
			if(!in_word)
				return NULL;
			if(in_word)
				in_word--;
			boofer = -1;
			*p = '\0';
			return word;
		}
		if(isspace(c)){
			if (in_word){
				in_word--;
				*p = '\0';
				return word;
			}
			else
				continue;
		}
		else{
			 if(ispunct(c)){
				if(in_word){
					in_word--;
					*p = '\0';
					boofer = c;
					return word;
				}
				else
				{
					*p = c;
					p++;
					*p = '\0';
					return word;
				}
			}
			else{
				if(!in_word)
					in_word++;
				*p = c;
				p++;
			}

		}
	}
}

void PrintWord(char *word){
	char *p = word;
	while(*p != '\0'){
		printf("%c", *p);
		p++;
	}
	printf(" ");
}

struct element{
	char *word;
	int counter;
	struct element *next;
};

int hash (char*word){
	int res = 0;
	char *p = word;
	while(*p != '\0'){
		res += *p;
		p++;
	}
	return res%10;
}

void AddWord(char * word, struct element **table){
	char *p = word;
	int h = hash(p);

	if (table[h] == NULL){
		table[h] = (struct element*) malloc (sizeof(struct element));
		table[h]->next = NULL;
		table[h]->word = word;
		table[h]->counter = 1;
		return;
	}
	else{
		struct element * t;
		t = table[h];
		if(!strcmp(t->word, word)){
			t->counter++;
			return;
		}
		while(t->next != NULL){
			t = t->next;
			if(!strcmp(t->word, word)){
				t->counter++;
				return;
			}
		}
		t->next = (struct element *) malloc (sizeof(struct element));
		t = t->next;
		t->next = NULL;
		t->word = word;
		t->counter = 1;
		return;

	}
}

void PrintTable(struct element **table, int TotalWords){
	int i;
	for(i = 0; i<10; i++){
		if (table[i] == NULL)
			continue;
		else{	
			struct element *t;
			t = table[i];
			PrintWord(t->word);
			double frequency  = t->counter;
			frequency /= TotalWords;
			printf("%d %lf\n", t->counter, frequency);
		
			while(t->next != NULL){
				t = t->next;
				PrintWord(t->word);
				frequency = t->counter;
				frequency /= TotalWords;
				printf("%d %lf\n", t->counter, frequency);				
			}
		}
		
	}
}

struct element *linear(struct element **table){
	struct element *list;
	struct element *handle;
	int i;
	for (i = 0; i<10; i++)
		if (table[i] != NULL)
			break;
	if(i == 10)
		return NULL;

	list = table[i];
	handle = list;
	while (i < 9){
		while (handle->next != NULL)
			handle = handle->next;
		
		int j;
		for(j = i+1; j<10; j++)
			if (table[j] != NULL)
				break;
		if (j == 10)
			return list;

		handle->next = table[j];
		i = j;
	}

	return list;
	
	

}

struct element *FreeElement(struct element *list, int i){
	if (i==0){
		struct element *handle = list->next;
		free(list);
		list = handle;
		return list;
	}
	else{
		int j;
		struct element *handle = list;
		for(j = 0; j<i-1; j++)
			handle = handle->next;
		struct element *deleter = handle->next;
		handle->next = deleter->next;
		free(deleter);
		return list;
	}
}

void PrintElement(struct element * list, int i, int TotalWords){
	int j;
	struct element *handle = list;
	for(j=0; j<i; j++)
		handle = handle->next;

	double frequency;
	PrintWord(handle->word);
	frequency = handle->counter;
	frequency /= TotalWords;
	printf("%d %lf\n", handle->counter, frequency);				
}


void Output(struct element *list, int TotalWords){
	struct element *max;
	int max_i;
	int i;
	struct element *handle;
	struct element *head;
	handle = list;
	while(list != NULL){
		handle = list;
		i = 0;
		max_i = 0;
		max = handle;
		while (handle->next != NULL){
			handle = handle->next;
			i++;
			if (handle->counter > max->counter){
				max = handle;
				max_i = i;
			}
		}
		PrintElement(list, max_i, TotalWords);
		list = FreeElement(list, max_i);
	}
}

void PrintList(struct elemement *list){
	struct element *handle = list;
	while(handle != NULL){
		PrintWord(handle->word);
		handle = handle->next;
	}
}

int main(){

	char *word;
	struct element *table[10];
	int i; int TotalWords = 0;
	for(i=0; i<10; i++)
		table[i] = NULL;
	
	do{
		if(!(word = ReadWord()))
			break;
		TotalWords++; 
		AddWord(word, table);
	}while (boofer !=-1);
	struct element *line;
	line = linear(table);
	Output(line, TotalWords);
	return 0;

}
