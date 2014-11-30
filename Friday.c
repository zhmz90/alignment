#include<stdio.h>
#include<stdlib.h>
	
int main(){
	
	FILE *fp;
	unsigned int i,j,k,tmp=0,max=0;//to be used in for cycle or tmp vars.	
	
	//to get the biggest frequency.
	fp = fopen("result_freq.txt","r");
	while( (fscanf(fp,"%u\t",&tmp)) == 1){
		if (tmp > max){
			max = tmp;	
		}
	}
	
	printf("the biggest freqs is:%u\n",max);
//	for (){
	
	
//	}

	fclose(fp);
	return 0;
}
