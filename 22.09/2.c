#include <stdio.h>

int IsPrime(int a){
	int j;
	for(j=2; j<a; j++)
		if (a%j == 0)
			return 0;
	return 1;
}

int main(){
	int n;
	scanf("%d", &n);
	int i;
	for(i=1; i<=n; i++)
		if (IsPrime(i))
			printf("%d, ", i);	
	printf("\n");
return 0;
}
