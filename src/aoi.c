#include "aoi.h"

char** 
parseinput(char* line)
{
	exit(EXIT_FAILURE);
}

char*
readinput(void)
{
	char* line = NULL;
	size_t buflen = 0;
	size_t linelen;
	
	if ((linelen = getline(&line, &buflen, stdin)) > 0)
		return line;

	exit(EXIT_FAILURE);
}

int
main(void)
{
	// Step 1: Read in user input from stdin
	// Step 2: Parse user input from stdin
	// Step 3: Exec command with the provided arguments
	
	printf("String: %s", readinput());
	

	exit(EXIT_SUCCESS);
}
