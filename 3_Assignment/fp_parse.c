/*
 * Kobe Davis
 * Prof. Morrissey
 * 25 July 2017
 * CS 201
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * The purpose of this program is to implement an IEEE floating point parser for an arbitrary number of bit settings.
 */

void fp_display(int frac_bits, int exp_bits, int to_parse); //function prototype for fp_display. returns nothing, receives three integers as arguments.

int main(int argc, char * argv[])
{
    printf("\n");   //making the console output pretty
    if(argc != 4)   //confirming correct number of arguments
    {
        printf("Incorrect number of arguments.\n\n");
        exit(EXIT_FAILURE);//program abort
    }

    int frac_bits = 0;  //number of fraction bits specified
    int exp_bits = 0;   //number of exponent bits specified
    int to_parse = 0;   //the hexadecimal integer to be parsed
    sscanf(argv[1], "%d", &frac_bits);  //placing argv args into appropriate variables
    sscanf(argv[2], "%d", &exp_bits);
    sscanf(argv[3], "%x", &to_parse);

    fp_display(frac_bits, exp_bits, to_parse);  //calling fp_display function which will convert the given hex digit into a (1 + frac_bits + exp_bits) bit floating point number.

    return 0;   //program completes succesfully
}

void fp_display(int frac_bits, int exp_bits, int to_parse)
{
    if(frac_bits < 2 || frac_bits > 10) //confirming correct number of fraction bits.
    {
        printf("Illegal number of fraction bits(%d). Should be between 2 and 10.\n\n", frac_bits);
        exit(EXIT_FAILURE); //invalid number of fractions bits causes the program to abort.
    }
    if(exp_bits < 3 || exp_bits > 5)    //confirming correct number of exponent bits.
    {
        printf("Illegal number of exponent bits(%d). Should be between 3 and 5.\n\n", exp_bits);
        exit(EXIT_FAILURE); //invalid number of exponent bits causes the program to abort.
    }

    //total bits calculates the number of bits specified by the user for the resulting floating point number.
    int total_bits = 1 + exp_bits + frac_bits;
    //max val calculates the maximum value the above mentioned floating point number should be able to represent.
    int max_val = pow(2, total_bits) - 1;
    if(to_parse > max_val)  //if the hex digit to convert is larger than max val, then we know we can't represent the specified hex digit with the parameters given.
    {
        printf("Supplied hex value is larger than the specified floating point's maximum respresentable value(%d)\n\n", max_val);
        exit(EXIT_FAILURE); //since we can't represent the hex digit correctly we have to specify this error and abort.
    }

    //each of the following calculation begin by creating a bit mask that corresponds to their respective areas in the user given hex digit.
    //int casting is necessary for use of bitwise operators (bitwise operators will not work between ints and float/doubles).
    //what follows is the math to calculate each field, taken directly from the B/O textbook (pgs. 113-117).
    double frac = (to_parse & (int)(pow(2, frac_bits) - 1))/pow(2, frac_bits);  //calculating the value of the fraction.
    double exp = ((to_parse >> frac_bits) & (int)(pow(2, exp_bits) - 1));   //calculating the value represented by considering the exponent field to be an unsigned integer.
    double sign = ((to_parse >> (frac_bits + exp_bits)) & 1);   //calculating the sign of the value (whether or not it should be negative).

    if(exp == (pow(2, exp_bits) - 1))   //checking for special cases.
    {
        if(frac)    //checking for NaN
        {
            printf("NaN\n\n");
            return;
        }
        //if special case isn't NaN, then it's definitely infinity, below decides whether that will be pos or neg.
        if(sign)
            printf("-");
        else
            printf("+");
        printf("inf\n\n");
        return;
    }

    double bias = (pow(2, (exp_bits-1)) - 1);   //calculating bias
    double decimal_value = 0;   //declaring result variable
    if(!exp)    //checking for denormalized case
        decimal_value = pow(2, (1 - bias)) * frac;  //denormalized specific calculation
    else    //checking for normalized case
        decimal_value = pow(2, (exp - bias)) * (1 + frac);  //normalized specific calculation

    if(sign)    //adding a negative to the value if needed.
        printf("-");
    printf("%f\n\n", decimal_value);    //displaying resulting floating point number.

    return;
}

