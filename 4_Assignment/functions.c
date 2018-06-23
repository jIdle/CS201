/*
 * Kobe Davis
 * 15 August 2017
 * Prof. Morrissey
 * CS 201
 *
 * File purpose: Implementation file for the functions defined in proto_structs.h
 *
 */

#include "proto_structs.h"

//u_exit is the first function pointed to in the function dispatch table. u_exit will exit the program with
//an exit message. u_exit has its current format (return type and parameter) to satisfy the typedef that 
//dictates what kind of function may be used in the function_dispatch_table. this solves having to implement
//special code to catch when the user wants to exit the program rather than do calculations.
double u_exit(arg_list * to_ignore)
{
    printf("Program exiting...\n\n");
    exit(EXIT_SUCCESS);
}

double add(arg_list * to_add)
{
    int sum = 0;            //accumulates the sum of given args
    char * end_ptr = NULL;  //temp pointer for strtol

    printf("You are attempting to add %d numbers together.\n", to_add->arg_total);  //displays # of args
    for(int i = 0; i < to_add->arg_total; ++i)      //adds arguments together
    {
        sum += strtol(to_add->user_args[i], &end_ptr, 0);   //strtol converts given string into actual numbers
    }
    return sum;
}
double subtract(arg_list * to_sub)
{
    int sum = 0;            //accumulates sum of given args
    char * end_ptr = NULL;  //temp pointer for strtol

    printf("You are attempting to subtract %d numbers.\n", to_sub->arg_total);  //displays # of args
    for(int i = 0; i < to_sub->arg_total; ++i)      //adds arguments together (like adding negatives kind of)
    {
        sum -= strtol(to_sub->user_args[i], &end_ptr, 0);  //strtol converts given string into actual numbers
    }
    return sum;
}
//works similar to add and subtract
double multiply(arg_list * to_mult)
{
    int product = 1;        //1 instead of 0 because 0 will cancel out all arguments
    char * end_ptr = NULL;

    printf("You are attempting to multiply %d numbers together.\n", to_mult->arg_total);
    for(int i = 0; i < to_mult->arg_total; ++i)
    {
        product *= strtol(to_mult->user_args[i], &end_ptr, 0);
    }
    return product;
}
//works fairly similar to add, subtract, mult
double divide(arg_list * to_div)
{
    double quotient = 0;
    char * end_ptr = NULL;

    printf("You are attempting to divide %d numbers.\n", to_div->arg_total);
    if(to_div->arg_total > 2)   //only uses first two args message
    {
        printf("Only the first two arguments are used when dividing. The rest will be discarded.\n");
    }
    double numerator = (double) strtol(to_div->user_args[0], &end_ptr, 0); //store first arg, cast as double
    double denominator = (double) strtol(to_div->user_args[1], &end_ptr, 0); //store second arg, cast as double
    quotient = numerator/denominator;   //divide them
    return quotient;
}
//works almost identically to divide
double mod(arg_list * to_mod)
{
    int remain = 0;
    char * end_ptr = NULL;

    printf("You are attempting to mod %d numbers.\n", to_mod->arg_total);
    if(to_mod->arg_total > 2)   //only uses first two args message
    {
        printf("Only the first two arguments are used by the modulo function. The rest will be discarded.\n");
    }
    //mod the first by the second
    remain = strtol(to_mod->user_args[0], &end_ptr, 0) % strtol(to_mod->user_args[1], &end_ptr, 0);
    return remain;
}

//this function uses another function "swap_char" which reverses a string by incrementing and decrementing the
//start and end pointers while trading values. each word in the array of args is hit and passed to this function.
//the actual place of the word relative to each other is not changed, rather they are just displayed backwards.
double reverse(arg_list * to_turn)
{
    printf("You are attempting to reverse %d words.\n", to_turn->arg_total);

    for(int i = 0; i < to_turn->arg_total; ++i) //pass each string in to_turn's char * array to swap_char to
    {                                           //reverse the string
        swap_char(to_turn->user_args[i]);
    }
    printf("\n\t");
    for(int i = (to_turn->arg_total - 1); i >= 0; --i)  //display backwards
    {
        printf("%s ", to_turn->user_args[i]);
    }
    printf("\n\n");
    return 0;
}
//receives the option_list struct called menu as a pointer. this struct contains the number of menu options and
//a char ** which is the two dimensional array that is the menu to be displayed to the user. print_menu displays
//this array to the user and then takes numerical input and returns it.
int print_menu(option_list * menu)
{
    if(!menu || menu->option_total != 7)    //confirming valid data
    {
        return 0;
    }
    printf("\nChoose from one of the %d options:\n", menu->option_total);   //display number of menu items
    for(int i = 0; i < menu->option_total; ++i) //display all menu items
    {
        printf("%d. %s\n", i, menu->m_list[i]); 
    }
    int ret_val;
    printf("\nMenu option #: ");
    scanf("%d", &ret_val);          //prompt user input for preferred menu item
    return ret_val;                 //return user's selection
}
//doesn't return data, but returns via altering data through the string pointer. swap_char reverses given strings
void swap_char(char * adr_start)
{
    char intermediary; //starting address of char *
    char * adr_end = (adr_start + strlen(adr_start)); //ending address of char *
    while(--adr_end > adr_start)   //swaps data until addresses cross
    { 
        intermediary = *adr_start;  //holds data
        *adr_start++ = *adr_end;    //increments and copies data
        *adr_end = intermediary;    //copies stored data
    }
}
