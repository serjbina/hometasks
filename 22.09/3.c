#include <stdio.h>

int main(){
	int n;
	scanf("%d", &n);
	int i=0, j=1,k;

	while (i<=n){
		printf("%d ", i);
		k = i;
		i += j;
		j = k;
		//printf("%d ", j);
		//j = k;
	}
printf("\n");
return 0;

	

}
