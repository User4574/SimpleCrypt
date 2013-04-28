/*
 * SimpleCrypt
 * Non-ECB version
 * So simple it's all one function.
 *
 * Nathan Lasseter (User_4574)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

	// We need a file to encrypt
	if (argc != 2) {
		fprintf(stderr, "Usage: encrypt <file>\n");
		return EXIT_FAILURE;
	}

	// Now lets open that file
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		fprintf(stderr, "No such file\n");
		return EXIT_FAILURE;
	}

	// Now we need the passphrase. Get it
	char *passphrase = malloc(256);
	do {
		printf("Enter Passphrase: ");
		if (fgets(passphrase, 255, stdin) == NULL) {
			fclose(file);
			fprintf(stderr, "Read error or end of file\n");
			return EXIT_FAILURE;
		}
	} while (strlen(passphrase) <= 0);

	// And a temporary file to hold the encrypted data
	char tpath[] = ".SimCr.XXXXXX";
	int tempfd = mkstemp(tpath);
	FILE* temp = fdopen(tempfd, "w");

	// Now we decrypt!
	int passlen = strlen(passphrase) - 2;
	int c, d, j = 0;

	while ((c=fgetc(file)) != EOF) {
		d = c - passphrase[j];
		passphrase[j] = c;
		fputc(d, temp);

		if (j == passlen) j=0;
		else j++;
	}

	// Close the files
	fflush(temp);
	fclose(temp);
	fclose(file);

	// Free used memory
	free(passphrase);

	// Move the file back
	if (rename(tpath, argv[1]) != 0) {
		fprintf(stderr, "Your encrypted file is located in %s.", tpath);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
