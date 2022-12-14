/** @file aoi.h
 *  @brief Function prototypes for aoi, the simple shell.
 *
 *  This contains the prototypes for the project 
 *  alongwith all constants, and global variables.
 *
 *  @author Jarryd W (jrdwe)
 *  @bug No known bugs.
 */

#ifndef AOI_H
#define AOI_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ARGS_BUFSIZE 32

// Variables for the built-in shell commands 
extern const char *builtin_commands[];
extern int (*builtin_functions[]) (void);

/* @brief Returns the number of builtin commands 
 * 
 * @return int 
 */
int builtin_count(void); 

/* @brief Displays help and advice to the programs user
 * 
 * @return Returns 1 for program to continue 
 */
int builtin_help(void); 

/* @brief Exits the program gracefully at the users request
 * 
 * @return Returns 0 for program to exit
 */
int builtin_exit(void); 

/* @brief Displays welcome message when terminal is loaded
 * 
 * @return void
 */
void builtin_welcome(void); 

/* @brief Executes the users command
 *
 * @return Status code signalling success or failure 
 */
int execute_command(char **args);

/* @brief Forks and calls the system command
 *
 * @return Status code signalling success or failure 
 */
int enact_syscall(char **args);

/* @brief Reads in a text-line from stdin 
 *
 * @return A heap-allocated line 
 */
char *read_input(void);

/* @brief Seperates the user's input by whitespace 
 *        to acquire the desired commmand and any 
 *        arguments
 *
 * @param line The user's input
 * @return An array of strings taken from line
 */
char **parse_input(char *line);

/* @brief The core program loop of the shell
 *        which runs until the user exits
 *
 * @return void
 */ 
void userloop(void);

#endif
