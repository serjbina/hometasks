#include <stdio.h>
#define N 10

void remap(int a[N]){
	int i;
	for(i=0; i<N; i++){
		if (a[i]>0){
			printf("findplus\n");
			int n, k = i, j=i+1;
			while(j!=N){
				n = a[j];
				a[j] = a[k];
				a[k] = n;
				k++;
				j++;
			}
		}
		else if(a[i] < 0){
			printf("find\n");
			int n, k=i, j=i-1;
			while (j != 0){
				n = a[j];
				a[j] = a[k];
				a[k] = n;
				k--; j--;
			}
		}
	}
} 	

int main(){
	int a[N];
	int i;
	for (i = 0; i<N; i++){
		if (i%3 == 0)
			a[i] = -i;
		else if (i%3 == 1)
			a[i] = 0;
		else
			a[i] = i;
	}
	remap(a);
	for(i=0; i<N; i++)
		printf("%d ", a[i]);
return 0;	
}
