/** @file aoi.h
 *  @brief Function prototypes for the simple shell.
 *
 *  This contains the prototypes for a simple shell
 *  alongwith all constants, and global variables you need.
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
#define AOI_ARGS_DELIM " " 

/* @brief Reads in a text-line from stdin 
 * @return A heap-allocated line 
 */
char* readinput(void);

/* @brief Seperates the user's input by whitespace 
 *				to acquire the desired commmand and any 
 *				arguments
 *
 * @param	line The user's input
 * @return An array of strings taken from line
 */
char** parseinput(char* line);

#endif
