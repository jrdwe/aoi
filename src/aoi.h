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
#include <stdlib.h>
#include <string.h>

#define AOI_ARGS_BUFSIZE 32

// Variables for the built-in shell commands 
extern const char *builtin_commands[];
extern void (*builtin_functions[]) (char **);

/* @brief Returns the number of builtin commands 
 * 
 * @return int 
 */
int builtin_count(void); 

/* @brief Displays help and advice to the programs user
 * 
 * @return void
 */
void builtin_help(char **args); 

/* @brief Exits the program gracefully at the users request
 * 
 * @return void
 */
void builtin_exit(char **args); 

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
 *				to acquire the desired commmand and any 
 *				arguments
 *
 * @param	line The user's input
 * @return An array of strings taken from line
 */
char **parse_input(char *line);

/* @brief The core program loop of the shell
 *				which runs until the user exits
 *
 * @return void
 */ 
void userloop(void);

#endif
