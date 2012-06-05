#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sanitise(char *x) {
	char *curpos = x;
	while (*x != '\0') {
		*curpos = *x;
		x++;
		if (*curpos != '/') curpos++;
	}
	*curpos = '\0';
}

int main(int argc, char** argv) {
	char * junk;
	/* We need a file to encrypt */
	if(argc==1) {
		fprintf(stderr, "Arguments fool!");
		return 1;
	}
	/* Now lets open that file */
	FILE* file = fopen(argv[1], "r");
	/* And a temporary file to hold the encrypted data */
	char tpath[255] = "/tmp/";
	sanitise(argv[1]);
	strcat(tpath, argv[1]);
	FILE* temp = fopen(tpath, "w");
	
	char passphrase[255];
	do {
		/* Now we need the passphrase. Get it */
		printf("Enter Passphrase:\n");
		junk = fgets(passphrase, 255, stdin);
	} while (strlen(passphrase) <= 0);
	
	int passlen = strlen(passphrase) - 1;
	int c,j=0;
	/* Now we encrypt! */
	while((c=fgetc(file)) != EOF) {
	if(j==passlen) {
			fputc(c ^ passphrase[0], temp);
			j=1;
		} else {
			fputc(c ^ passphrase[j], temp);
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
	if (system(cmd) != 0) {
		fprintf(stderr, "Your encrypted file is located in %s.", tpath);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

