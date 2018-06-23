/*
 * Kobe Davis
 * 15 August 2017
 * Prof. Morrissey
 * CS 201
 *
 * Program Purpose:
 *
 * The goal of this program is to allow a user to enter anywhere from 2 to 15 arguments from the command line
 * and either add, subtract, multiply, divide, mod, or reverse them. The latter two only accepting 2 arguments.
 * This is to be done through a menu based system where the menu option corresponds to a function.
 * The purpose is to bring together several class concepts such as: Program Arguments, Data Conversion,
 * C Structures, and Pointers to Functions.
 *
 */

//NOTE: HEXADECIMAL INPUT MUST BE PREFACED WITH 0x FOR PROGRAM TO FUNCTION APPROPRIATELY. 
//THIS IS TO ALLOW THE PROGRAM TO DIFFERENTIATE BETWEEN HEX AND DECIMAL.

#include "proto_structs.h"

int main(int argc, char * argv[])
{
    //error checking for user's input. error if not correct number of arguments.
    if(argc < 3 || argc > 16)
    {
        printf("\nError. Incorrect number of arguments: %d\nValid argument range: 2 - 15\n\n", (argc - 1));
        exit(EXIT_FAILURE);
    }

    //flexible array to temporarily hold menu text. this will be copied to an option_list struct momentarily.
    char * list[] = {"Exit", "Addition", "Subtraction", "Multiplication", "Division", "Modulo", "Reverse Input"};
    int size = sizeof(list)/sizeof(list[0]);    //size of list calculated dynamically

    option_list * menu = malloc(sizeof(option_list));   //allocating memory for struct data
    menu->option_total = size;                          //copying calcuated menu size to struct
    menu->m_list = malloc(size * sizeof(char*));        //allocating memory for array of char * inside struct

    //below for loop takes elements inside the above flexible array "list" and deep copies them to menu
    for(int i = 0; i < size; ++i)
    {
        int len = strlen(list[i]) + 1;              //calculating amount of memory to allocate
        menu->m_list[i] = malloc(len);              //allocating that amount of memory to specified char *
        strncpy(menu->m_list[i], list[i], len);     //copying specified data from "list" to struct's array
    }

    //calling print_menu function which will display the menu previously copied to menu and allow user input
    int user_option = print_menu(menu);  
    if(user_option < 0 || user_option > 6)      //confirms user input (which menu item they chose) is valid
    {
        printf("Please enter a valid menu option.\n");
        exit(EXIT_FAILURE);
    }

    argv++;                                                 //incrementing command line args to second arg
    int size2 = argc - 1;                                   //storing amount of command line args
    arg_list * user_al = malloc(sizeof(arg_list));          //allocating memory for arg_list struct
    user_al->arg_total = size2;                             //copying amount of command line args to user_al
    user_al->user_args = malloc(size2 * sizeof(char*));     //allocating memory for char * array in user_al

    //below for loop deep copies array elements from the command line (argv) array to the struct's (user_al) array
    for(int i = 0; i < user_al->arg_total; ++i)
    {	
        int len = strlen(argv[i]) + 1;                  //calculating amount of memory to allocate
        user_al->user_args[i] = malloc(len);            //allocating that amount of memory to specfied char *
        strncpy(user_al->user_args[i], argv[i], len);   //copying data from argv array to struct's array
    }

    //as the type implies, this is the function dispatch table that allows the user input to correspond to
    //which function is invoked. essentially, this is an array of structs that each hold a pointer to a function
    //and a name/description of that function/what it does.
    function_dispatch_table fdt[] = {
        {"Exit", u_exit},
        {"Addition", add},
        {"Subtraction", subtract},
        {"Multiplication", multiply},
        {"Division", divide},
        {"Modulo", mod},
        {"Input Reversal", reverse}
    };
    
    printf("\nUser has chosen to invoke the %s function.\n", fdt[user_option].name); //output user choice
    double result = (*fdt[user_option].to_invoke)(user_al);     //calls user specified function, returns to result
    if(user_option != 6)    //Input Reversal function displays in function, therefore not requiring this printf
    {
        printf("The result is: \n\nDecimal: %f\n\n", result); //displays result back to user
    }

    exit(EXIT_SUCCESS);
}

