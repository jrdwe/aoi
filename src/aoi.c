#include "aoi.h"

const char *builtin_commands[] =
{
  "help",
  "exit"
};

int (*builtin_functions[]) (void) =
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


int 
builtin_help(void)
{
  int i;

  printf("\nWelcome! You've called the 'help' command.\n");
  printf("This program is a simple shell with a few builtin commands\n\n");
  printf("These commands are listed below: \n");

  for (i = 0; i < builtin_count(); i++)
    printf("> %s\n", builtin_commands[i]);

  printf("\nAll other valid system commands and arguments can be used as well.\n\n");

  return 1;
}


int
builtin_exit(void)
{
  printf("\nSee you soon! Exiting now..\n");

  return 0;
}


char** 
parse_input(char* line)
{
  int ctr = 0, bufferlen = ARGS_BUFSIZE;          
  void *ptr;                                          
  char *arg;
  char **args = malloc(sizeof(*args) * bufferlen);

  // check malloc has successfully allocated memory space
  if (!args)
  {
    fprintf(stderr, "Unable to allocate required memory for arguments\n");
    exit(EXIT_FAILURE); 
  }

  while ((arg = strsep(&line, " \n\t")) != NULL)
  {
    // if NULL then pass to next token
    if (*arg == '\0') continue;

    if (ctr == bufferlen)
    {
      // double buffer size and allocate more memory 
      bufferlen *= 2;
      ptr = realloc(args, sizeof(*args) * bufferlen);

      // check realloc has successfully allocated memory space
      if (!ptr) 
      {
        fprintf(stderr, "Unable to allocate required memory for arguments\n");
        exit(EXIT_FAILURE); 
      }

      args = ptr;
    }

    // save current token into array
    args[ctr++] = arg;
  }

  args[ctr] = NULL;

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
  int i;

  // empty command check
  if (args[0] == NULL)
    return 1;

  // builtin command check
  for (i = 0; i < builtin_count(); i++)
  {
    if (strcmp(args[0], builtin_commands[i]) == 0)
      return builtin_functions[i]();
  }

  // system command call
  return enact_syscall(args);
}


int 
enact_syscall(char **args)
{
  int state;
  pid_t pid;

  if ((pid = fork()) == -1)
  {

    fprintf(stderr, "Fork failed - couldn't execute command!\n");

  } else if (pid == 0) {

    if (execvp(args[0], args) == -1)
      fprintf(stderr, "Failed to execute command! Please check your spelling. \n");

    exit(EXIT_FAILURE);
  }

  waitpid(pid, &state, WUNTRACED);

  return 1;
}


void
userloop(void)
{
  int state = 1;
  char* user_input;
  char** parsed_input;

  while (state) 
  {
    printf("-> ");
    user_input = read_input();
    parsed_input = parse_input(user_input);
    state = execute_command(parsed_input);

    free(user_input);
    user_input = NULL;

    free(parsed_input);
    parsed_input = NULL;
  }
}


int
main(void)
{
  builtin_welcome();
  userloop(); 

  exit(EXIT_SUCCESS);
}

