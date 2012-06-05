#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

	// We need a file to encrypt
	if (argc != 2) {
		fprintf(stderr, "Usage: encrypt <file>");
		return EXIT_FAILURE;
	}

	// Now lets open that file
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		fprintf(stderr, "No file specified\n");
		return EXIT_FAILURE;
	}

	// Now we need the passphrase. Get it
	char *passphrase = malloc(256);
	do {
		printf("Enter Passphrase: ");
		if (fgets(passphrase, 255, stdin) == NULL) {
			fclose(file);
			fprintf(stderr, "Read error or end of file");
			return EXIT_FAILURE;
		}
	} while (strlen(passphrase) <= 0);

	// And a temporary file to hold the encrypted data
	char tpath[] = "SimCr.XXXXXX";
	int tempfd = mkstemp(tpath);
	FILE* temp = fdopen(tempfd, "w");

	// Now we encrypt!
	int passlen = strlen(passphrase) - 1;
	int c,j=0;
	while ((c=fgetc(file)) != EOF) {
		if (j == passlen) {
			fputc(c ^ passphrase[0], temp);
			j=1;
		} else {
			fputc(c ^ passphrase[j], temp);
			j++;
		}
	}

	// Close the files
	fflush(temp);
	fclose(temp);
	fclose(file);

	// Move the file back
	if (rename(tpath, argv[1]) != 0) {
		fprintf(stderr, "Your encrypted file is located in %s.", tpath);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
