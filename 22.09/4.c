#include <stdio.h>
#include <math.h>

int main(){
	float eps;
	scanf("%f", &eps);
	float q1 = 1, q2 = 2;
	float f1 = 2, f2 = 1, mem;
	while (abs(q1-q2) > eps){
		mem = f1;
		f1 += f2;
		f2 = mem;
		q1 = q2;
		q2 = f1/f2;
	}
	printf("%f\n", q2);
return 0;
}
