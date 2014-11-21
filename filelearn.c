#include <stdio.h>



int main(){
	
	FILE *fp;
	fp = fopen("test.txt","w+");
	fprintf(fp,"%s %s %s %d","we","are","in",2012);
	fclose(fp);

	return 0;
}
