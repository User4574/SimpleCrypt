#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	if(argc==0) {
		fprintf(stderr, "Arguments fool!");
		return 1;
	}
	FILE* file = fopen(argv[1], "r");
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char filearr[length];
	fread(filearr, length, 1, file);
	fclose(file);
	printf("Enter Passphrase:\n");
	char passphrase[81];
	fgets(passphrase, 81, stdin);
	int passlen = strlen(passphrase) - 1;
	int i=0,j=0;
	for(i=0;i<length;i++) {
		if(j==passlen) {
			j=0;
			i--;
		} else {
			filearr[i] += passphrase[j];
			j++;
		}
	}
	file = fopen(argv[1], "w");
	fwrite(filearr, 1, length, file);
	fflush(file);
	fclose(file);
	return 0;
}
