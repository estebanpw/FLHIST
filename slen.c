/*

Computes the histogram of exponential lengths for a fasta file

*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#define maxH   16


void terror(char* m) {
    printf("\nERR**  %s ***\n",m); 
    exit(-1);
}

int main(int ac,char **av){

	if(ac != 2) terror("USE: ./slen <file.fasta>");

	uint64_t HIS[maxH];
	FILE   *fdb;
	char c = '\0'; //Initialize
	uint64_t curr_len, n_sequences = 0;
	uint64_t total_len = 0;
	uint64_t i = 0, aux;
	for(i=0;i<maxH;i++) HIS[i] = 0;

	fdb = fopen64(av[1], "rt");
	if(fdb == NULL) terror("Could not open fasta database");


	while(!feof(fdb)){

		if(c == '>'){
			n_sequences++;
			curr_len = 0;
			while(c != '\n') c=fgetc(fdb);
			while(!feof(fdb) && c != '>'){
				c=fgetc(fdb);
				curr_len++;
			}
			total_len += curr_len;
			aux = (uint64_t)log10l((long double)curr_len);
			HIS[aux+1]++;
		}else{
				c=fgetc(fdb);
		}
	}

	fprintf(stdout, "Length\tCounts\n");
	for(i=0;i<maxH;i++){
		fprintf(stdout, "%"PRIu64"\t%"PRIu64"\n", (uint64_t) exp10l((long double)i), HIS[i]);
	}
	fprintf(stdout, "Average length is %"PRIu64"\n", total_len/n_sequences);

	return 0;
}
