/*
 * Kobe Davis
 * Prof. Morrissey
 * 20 July 2017
 * CS 201
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//The goal of this program is to accept two hexadecimal 32-bit integers and display which bits the two
//number both have set to 1 as well as the resulting number in hexadecimal, signed integer and unsigned
//integer formats. If the input it incorrect (not exactly two hexadecimal integers as input) then the
//program will display an error and abort.

int main(int argc, char * argv[]) //main receives arguments which will be used to turn on corresponding bits.
{
    //end_ptr is a character pointer that will be used for strtol to function properly.
    char * end_ptr;
    //the following if statement checks argc to confirm there being exactly two arguments.
    if(argc != 3)
    {
        printf("Error: please provide two hexadecimal numbers as arguments to the program.\n");
        exit(EXIT_FAILURE);//abort
    }
    //result is just the result of the first and second hex integers &'d together. the point of this
    //is to find the bits that both have in common.
    uint32_t result = (strtol(argv[1], &end_ptr, 16) & strtol(argv[2], &end_ptr, 16));
    uint32_t common = 0x80000000;//common is just a mask that will be used to display 1 bit at a time.
    printf("Bits in common: ");
    //the following loop uses the & operator on result and common(the mask) to determine whether the bit
    //in the specified position is 1 or 0. Once this is determined, a boolean expression is used to simplify
    //the result to either 0 or 1 rather than a string of bits. if the result is 1, then we know that that
    //bit position is where both hex inputs had a 1 bit in common.
    for(int i = 0; i < 32; ++ i)
    {
        uint32_t display = (result & common) != 0; //determine if bit is 1 or 0.
        if(display) //if it is 1 then display the bit position.
            printf("%d ", (31 - i));//display the bit position
        common >>= 1;//right shift to continue checking new bit position of result with bit mask common.
    }
    printf("\nHexadecimal: %X\n", result);  //display hex format
    printf("Signed Integer: %d\n", result); //display signed int format
    printf("Unsigned Integer: %u\n", result);   //display unsigned int format

    return 0;
}
