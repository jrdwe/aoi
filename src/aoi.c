#include "aoi.h"

const char *builtin_commands[] =
{
	"help",
	"exit"
};

void (*builtin_functions[]) (char **) =
{
	&builtin_help,
	&builtin_exit
};

int 
builtin_count(void)
{
	return sizeof(builtin_commands) / sizeof(char *);
}

void 
builtin_help(char** argument)
{
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Welcome! You've called the 'help' command.\n");
	printf("This program is a simple shell with a few builtin commands\n\n");
	printf("These commands are listed below: \n");

	for (int i = 0; i < builtin_count(); i++)
		printf("++ %s\n", builtin_commands[i]);

	printf("\nAll other valid system commands and arguments can be used as well.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

void 
builtin_exit(char** argument)
{
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("See you soon! Exiting now..\n");

	exit(EXIT_SUCCESS);
}

char** 
parse_input(char* line)
{
	int ctr = 0;
	char *arg;
	char **args = malloc(sizeof(*args) * AOI_ARGS_BUFSIZE);

	// check malloc has successfully allocated memory space
	if (!args)
	{
		fprintf(stderr, "Unable to allocate required memory for arguments\n");
		exit(EXIT_FAILURE);	
	}

	while ((arg = strsep(&line, " ")) != NULL)
		args[ctr++] = arg;

	return args;
}

char*
read_input(void)
{
	char *line = NULL;
	size_t buflen = 0;
	size_t linelen;
	
	if ((linelen = getline(&line, &buflen, stdin)) > 0)
		return line;

	exit(EXIT_FAILURE);
}

void
userloop(void)
{
	for(;;)
	{
		printf("--> ");
		char* user_input = read_input();

		for (int i = 0; i < builtin_count(); i++)
		{
			if (strcmp(parse_input(user_input)[0], builtin_commands[i]) == 0)
				builtin_functions[i](parse_input(user_input));
		}
	}
}

int
main(void)
{
	// Todo
	// Exec command with the provided arguments
	// Welcome art! 
	// Trim function to remove whitespace

	userloop();	

	exit(EXIT_SUCCESS);
}
