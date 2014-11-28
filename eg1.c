#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *pFile;
	long lSize;
	unsigned char  *buffer;
	size_t result;
	
	pFile = fopen("hg19.2bit","rb");
	if (pFile == NULL){fputs("File error",stderr);exit(1);}
	
	fseek(pFile,0,SEEK_END);
	lSize = ftell(pFile);
	printf("%f\n",(float)lSize);
	rewind(pFile);
	buffer = (unsigned char *)malloc(sizeof(unsigned char)*lSize);
	if (buffer == NULL){fputs("Memory error",stderr);exit(2);}

	result = fread(buffer,1,lSize,pFile);
	if (result != lSize){fputs("Reading error",stderr);exit(3);}	
	
	int i;
	for (i=0; i<lSize;i++){
		printf("%d\n", *(buffer+i));
	
	}	
	
	fclose(pFile);	
	free(buffer);
	
	return 0;

}
