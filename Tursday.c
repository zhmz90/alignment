#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct node{
        char n:2;
}NC;

unsigned int hashval(NC *m1, NC *m2, NC *m3, NC *m4, NC *m5,NC *m6, NC *m7, NC *m8, NC *m9, NC *m10, NC *m11, NC *m12, NC *m13, NC *m14, NC *m15, NC *m16){
	unsigned int tmp=0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16;
	a1 = (unsigned int)(m1->n);
	a2 = (unsigned int)(m2->n); 
	a3 = (unsigned int)(m3->n); 
	a4 = (unsigned int)(m4->n); 
	a5 = (unsigned int)(m5->n); 
	a6 = (unsigned int)(m6->n); 
	a7 = (unsigned int)(m7->n); 
	a8 = (unsigned int)(m8->n); 
	a9 = (unsigned int)(m9->n); 
	a10 = (unsigned int)(m10->n); 
	a11 = (unsigned int)(m11->n); 
	a12 = (unsigned int)(m12->n); 
	a13 = (unsigned int)(m13->n);
        a14 = (unsigned int)(m14->n); 
	a15 = (unsigned int)(m15->n); 
	a16 = (unsigned int)(m16->n);
	tmp = (unsigned int)(a1*(unsigned int)pow(4,15)+a2*(unsigned int)pow(4,14)+a3*(unsigned int)pow(4,13)+a4*(unsigned int)pow(4,12)+a5*(unsigned int)pow(4,11)+a6*(unsigned int)pow(4,10)+a7*(unsigned int)pow(4,9)+a8*(unsigned int)pow(4,8)+a9*(unsigned int)pow(4,7)+a10*(unsigned int)pow(4,6)+a11*1024+a12*256+a13*64+a14*16+a15*4+a16);
	return tmp;

}
	


int main(){

	FILE *fp;
	char *refer;//to be used to store the hg19 reference.
	long  len_refer;
	long  i,j,k,h;
	
	fp = fopen("hg19.2bit","rb");
//	fp = fopen("test.txt","rb");
	if (fp == NULL){fputs("open file error",stderr);exit(1);}
	
	fseek(fp,0,SEEK_END);
	len_refer = ftell(fp);
	printf("%f\n",(float)len_refer);
	rewind(fp);
	refer = (char *)malloc(len_refer*sizeof(char));
	if (refer == NULL){fputs("malloc error",stderr);exit(2);}
	if (fread(refer,1,len_refer,fp) != len_refer){
		fputs("reading error",stderr);
		exit(3);
	}
	fclose(fp);
	/******test refer success*******/	
	/********************************
	int i;
	for (i=0;i<len_refer;i++){
		printf("%d\n",refer[i]);
	}
	********************************/
	/***refer to nucletide array***/
	/******************************/
	NC *ref_nc;
	char temp;
	
	ref_nc = (NC *)malloc(4*len_refer*sizeof(NC));
	if (ref_nc == NULL){fputs("error in malloc NC",stderr);exit(4);}
	for (i=0;i<len_refer;i++){//one character to become 4 different elements of NC elements.
		temp = *(refer+i);
		(ref_nc+4*i)->n   = (temp & 192)>>6;
		(ref_nc+4*i+1)->n = (temp &  48)>>4;
		(ref_nc+4*i+2)->n = (temp &  12)>>2;
		(ref_nc+4*i+3)->n =  temp &   3;		
	}		
	free(refer);

	unsigned int *fre;//the array of 16-mers freqency 
	unsigned int size_container = (unsigned int)pow(2,29);//size of the 16-mers frequency in memory, here we divide the 16G into 4 part, each part 4G.
	NC *m1,*m2,*m3,*m4,*m5,*m6,*m7,*m8,*m9,*m10,*m11,*m12,*m13,*m14,*m15,*m16;
	FILE *fp_fre;
	
	fp_fre = fopen("result_freq.txt","w");//to be used to store the frequency of 16-mers.
	
	for (i=0;i<8;i++){
		fre = (unsigned int *)calloc(size_container,sizeof(unsigned int));
		m1 = ref_nc;
		m2 = ref_nc+1;
		m3 = ref_nc+2;
		m4 = ref_nc+3;
		m5 = ref_nc+4;
		m6 = ref_nc+5;
		m7 = ref_nc+6;
		m8 = ref_nc+7;
		m9 = ref_nc+8;
		m10= ref_nc+9;
		m11= ref_nc+10;
		m12= ref_nc+11;
		m13= ref_nc+12;
		m14= ref_nc+13;
		m15= ref_nc+14;
		m16= ref_nc+15;
		for (j=0;j<4*len_refer-15;j++){
			h = hashval(m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15,m16);
			if (  h < (i+1)*size_container && h>=(i*size_container) ){
				h = h - i*size_container;
				fre[h]+=1;
			}
			m1 +=1;
			m2 +=1;
			m3 +=1;
			m4 +=1;
			m5 +=1;
			m6 +=1;
			m7 +=1;
			m8 +=1;
			m9 +=1;
			m10 +=1;
			m11 +=1;
			m12 +=1;
			m13 +=1;
			m14 +=1;
			m15 +=1;
			m16 +=1;
		}	
		for (j=0;j<size_container;j++){
			fprintf(fp_fre,"%u\n",*(fre+j));
			
		}
		free(fre);	
	}
	free(ref_nc);
	fclose(fp_fre);
	return 0;
}
