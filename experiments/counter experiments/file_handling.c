/*
 * stdc-file-copy.c - copy one file to a new location, possibly under a
 * different name.
 */

#include <stdio.h>              /* standard input/output routines.    */

#define MAX_LINE_LEN 1000	/* maximal line length supported.     */

/*
 * function: main. copy the given source file to the given target file.
 * input:    path to source file and path to target file.
 * output:   target file is being created with identical contents to
 *           source file.
 */
void
main(int argc, char* argv[])
{
    char* file_path_from;	/* path to source file.   */
    char* file_path_to;		/* path to target file.   */
    FILE* f_from;		/* stream of source file. */
    FILE* f_to;			/* stream of target file. */
    char buf[MAX_LINE_LEN+1];   /* input buffer.          */

    /* read command line arguments */
    if (argc != 3 || !argv[1] || !argv[2]) {
	fprintf(stderr, "Usage: %s <source file path> <target file path>\n",
		argv[0]);
	exit(1);
    }
    file_path_from = argv[1];
    file_path_to = argv[2];

    /* open the source and the target files. */
    f_from = fopen(file_path_from, "r");
    if (!f_from) {
	fprintf(stderr, "Cannot open source file: ");
	perror("");
	exit(1);
    }
    f_to = fopen(file_path_to, "w+");
    if (!f_to) {
	fprintf(stderr, "Cannot open target file: ");
	perror("");
	exit(1);
    }

    /* copy source file to target file, line by line. */
    while (fgets(buf, MAX_LINE_LEN+1, f_from)) {
	if (fputs(buf, f_to) == EOF) {  /* error writing data */
	    fprintf(stderr, "Error writing to target file: ");
	    perror("");
	    exit(1);
	}
    }
    if (!feof(f_from)) { /* fgets failed _not_ due to encountering EOF */
        fprintf(stderr, "Error reading from source file: ");
        perror("");
        exit(1);
    }

    /* close source and target file streams. */
    if (fclose(f_from) == EOF) {
	fprintf(stderr, "Error when closing source file: ");
	perror("");
    }
    if (fclose(f_to) == EOF) {
	fprintf(stderr, "Error when closing target file: ");
	perror("");
    }
}

