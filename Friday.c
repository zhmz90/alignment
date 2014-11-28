#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char m1:2;

}NC;

int main(){
 	NC a;
	a.m1=1;
	printf("%c\n",a.m1);	

	return 0;
}
