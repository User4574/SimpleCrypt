#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
	/* We need a file to encrypt */
	if(argc==1) {
		fprintf(stderr, "Arguments fool!");
		return 1;
	}
	/* Now lets open that file */
	FILE* file = fopen(argv[1], "r");
	/* And a temporary file to hold the encrypted data */
	char tpath[255] = "/tmp/";
	strcat(tpath, argv[1]);
	FILE* temp = fopen(tpath, "w");
	/* Now we need the passphrase. Get it */
	printf("Enter Passphrase:\n");
	char passphrase[255];
	fgets(passphrase, 255, stdin);
	int passlen = strlen(passphrase) - 1;
	int c,j=0;
	/* Now we encrypt! */
	while((c=fgetc(file)) != EOF) {
		if(j==passlen) {
			fputc(c-passphrase[0], temp);
			j=1;
		} else {
			fputc(c-passphrase[j], temp);
			j++;
		}
	}
	/* Close the files */
	fflush(temp);
	fclose(temp);
	fclose(file);
	/* Move the file back */
	char cmd[255];
	sprintf(cmd, "%s %s %s", "/bin/mv", tpath, argv[1]);
	system(cmd);
	return 0;
}
