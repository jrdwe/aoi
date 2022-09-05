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
builtin_welcome(void)
{
	printf(" _       __       __                                   __              ___           _\n");
  printf("| |     / /___   / /_____ ____   ____ ___   ___       / /_ ____       /   |  ____   (_)\n");
  printf("| | /| / // _ \\ / // ___// __ \\ / __ `__ \\ / _ \\     / __// __ \\     / /| | / __ \\ / /\n");
  printf("| |/ |/ //  __// // /__ / /_/ // / / / / //  __/    / /_ / /_/ /    / ___ |/ /_/ // /\n");
  printf("|_______ ____//_/ \\___/ \\____/__/ /_/ /_/ \\___/    ____/ \\____/    /__  |_|\\____/__/__\n");
  printf(" /_  __// /_   ___     _____ (_)____ ___   ____   / /___     _____ / /_   ___   / // /\n");
  printf("  / /  / __ \\ / _ \\   / ___// // __ `__ \\ / __ \\ / // _ \\   / ___// __ \\ / _ \\ / // /\n");
  printf(" / /  / / / //  __/  (__  )/ // / / / / // /_/ // //  __/  (__  )/ / / //  __// // /\n");
  printf("/_/  /_/ /_/ \\___/  /____//_//_/ /_/ /_// .___//_/ \\___/  /____//_/ /_/ \\___//_//_/\n");
  printf("                                       /_/                                            \n\n");
	printf("Type any command to get started or 'help' to find out more\n\n");
}

void 
builtin_help(char** argument)
{
	printf("\nWelcome! You've called the 'help' command.\n");
	printf("This program is a simple shell with a few builtin commands\n\n");
	printf("These commands are listed below: \n");

	for (int i = 0; i < builtin_count(); i++)
		printf("-> %s\n", builtin_commands[i]);

	printf("\nAll other valid system commands and arguments can be used as well.\n\n");
}

void 
builtin_exit(char** argument)
{
	printf("\nSee you soon! Exiting now..\n");

	exit(EXIT_SUCCESS);
}

char** 
parse_input(char* line)
{
	int ctr = 0, bufferlen = AOI_ARGS_BUFSIZE;
	char *arg;
	char **args = malloc(sizeof(*args) * bufferlen);

	// check malloc has successfully allocated memory space
	if (!args)
	{
		fprintf(stderr, "Unable to allocate required memory for arguments\n");
		exit(EXIT_FAILURE);	
	}

	while ((arg = strsep(&line, " \n")) != NULL)
	{
		args[ctr++] = arg;

		if (ctr > bufferlen)
		{
			printf("ALLOC!\n");
			bufferlen *= 2;
			args = realloc(args, sizeof(*args) * (bufferlen));

			if (!args) 
			{
				fprintf(stderr, "Unable to allocate required memory for arguments\n");
				exit(EXIT_FAILURE);	
			}
		}
	}

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

int 
execute_command(char **args)
{
	
}

void
userloop(void)
{
	char* user_input;
	char** parsed_input;

	for(;;)
	{
		printf("-> ");
		user_input = read_input();
		parsed_input = parse_input(user_input);

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
	// seperate out the execute and cnntrol flow
	
	builtin_welcome();
	userloop();	

	exit(EXIT_SUCCESS);
}
