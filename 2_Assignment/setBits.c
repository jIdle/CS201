/*
 * Kobe Davis
 * Prof. Morrissey
 * 20 July 2017
 * CS 201
 */

#include <stdio.h>
#include <stdlib.h>

//The goal of this program is to accept a list of integers in the range [0 ... 15] and turn on the 
//corresponding bits in an unsigned short to output a result that shows set membership. If any integer
//is not in the correct range an error message will be printed and the program will abort.

int main(int argc, char *argv[]) //main receives arguments which will be used to turn on corresponding bits.
{
    //end_ptr is a character pointer that will be used for strtol to function properly.
    char * end_ptr; 
    //this loop checks each argument passed in through main and verifies that the given values
    //are in the correct range [0 ... 15].
    for(int i = 1; i < argc; ++i)
    {
        int to_check = strtol(argv[i], &end_ptr, 10); //using strtol to convert character argument into int.
        if(to_check < 0 || to_check > 15)   //checking argument is within bounds.
        {
            printf("Input was not inside valid range. Program will exit.\n");//outputing error message
            exit(EXIT_FAILURE);//abort
        }
    }
    int select = 0x8000;//creating a mask which will be used to display the bits of bit_array
    unsigned short bit_array = 0;//bit_array, is an unsigned short, which is an array of bits.
    //this turns on the specified bits in bit_array
    for(int i = 1; i < argc; ++i)
    {
        //using the << operator to shift to the specified bit, then using | operator to assign it to bit_array.
        bit_array |= (1 << strtol(argv[i], &end_ptr, 10));
    }
    //this loop displays the bits of bit_array by right shifting the mask each iteration and
    //using & to display whether or not the specified bit is turned on.
    while(select > 0)   //when select is right shift to 0 this loop ends
    {
        //select has only one bit active therefore the & operator can only result in a bit string
        //with 1 bit active or no bits active. if anything is active the boolean comparison will
        //result in a 1 being displayed for the place designated by the current mask position.
        int display = (bit_array & select) != 0;
        printf("%d", display);  //displaying either 1 or 0
        select >>= 1;   //right shifting to display next bit position
    }
    printf("\n");

    return 0;
}
