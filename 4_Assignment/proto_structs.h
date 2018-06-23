/*
 * Kobe Davis
 * 15 August 2017
 * Prof. Morrissey
 * CS 201
 *
 * File purpose: Contains the prototypes of functions and the struct definitions.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//The option_list struct is used to store the number of menu items that user has access to,
//and the text of those menu items in a two dimensional array
typedef struct option_list
{
    int option_total;   //number of menu options
    char ** m_list;     //actual menu options in 2d array
} option_list;

//The arg_list struct is used to store the command line arguments that the user has entered
//in a two dimensional array and how many there are.
typedef struct arg_list
{
    int arg_total;      //number of command line arguments
    char ** user_args;  //actual arguments in 2d array
} arg_list;

//typedef used to define the type of function that will be included in the
//function dispatch table in main. Functions of this type will return there
//calculations though a double, and receive their data through a struct pointer argument.
typedef double function_pointer(arg_list *);

//The function_dispatch_table isn't really an ftd by itself, but since the struct can hold
//a pointer to a function of a certain type, an array of these structs will form the ftd.
//Through this method, this program will allow the users menu selection to correspond to
//a particular function. 
typedef struct function_dispatch_table
{
    char * name;                    //name of function pointed to
    function_pointer * to_invoke;   //function pointer
} function_dispatch_table;

void swap_char(char * to_reverse);          //reverse a given string
double u_exit(arg_list * to_ignore);        //exits the program
double add(arg_list * to_add);              //adds given arguments together
double subtract(arg_list * to_sub);         //subtracts given arguments from each other
double multiply(arg_list * to_mult);        //multiplies given arguments together
double divide(arg_list * to_div);           //divides a first argument by the second
double mod(arg_list * to_mod);              //mods a first argument by a second
double reverse(arg_list * to_turn);         //reverse an entire array of strings, making use of the swap_char function.
int print_menu(option_list * menu);         //prints the menu options to the user. menu options are found in main.
