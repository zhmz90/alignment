#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	/***************************************************************************/
	/****************step 1: read the reference from file***********************/
	/***************************************************************************/
	//step 1: read the reference from the hg19.2bit file. 
	//declare vars
	FILE *pFile;
	long fSize;
	long half_fSize;
	unsigned char *ref;
	size_t BYTES;
	int i;

	//open "hg19.2bit"
	pFile = fopen("hg19.2bit", "rb");
	if (pFile == NULL){fputs("File error",stderr);exit(1);}
	
	//get the total size of bytes, 
	fseek(pFile,0,SEEK_END);
	fSize = ftell(pFile);
	rewind(pFile);
	printf("file size is: %f\n",(float)fSize);	
	
	//try the first half to test.
	half_fSize = fSize / 2;

	//malloc memory for reference.
	ref = (unsigned char *)malloc(sizeof(unsigned char)*half_fSize);
	if (ref == NULL){fputs("Memory error",stderr);exit(2);}

	//read reference file "hg19.2bit"
	BYTES = fread(ref,1,half_fSize,pFile);
	if (BYTES != half_fSize){fputs("Reading error",stderr);exit(3);}
	
	//print the reference we have just gotten
//	for (i=0; i<half_fSize; i++){
//		printf("%d\n", *(ref+i));
//	}
	fclose(pFile);	
	
	/*************************************************************************/
	/*******************step 2: malloc freq and initiate it*******************/
	/*************************************************************************/
	//step 2: malloc an  array:4G to contain first half freqs and initianse it.
	//declar vars
	//MER_16 *freq;
	const unsigned int MAX = (unsigned long)(pow(2,31)-1);	
	size_t SIZE_FREQ = MAX * sizeof(MER_16);
		
	//step 3: hash every 16mers to the array. 
	
	//save the freqs array to the file.
	free(ref);

	return 0;
}
