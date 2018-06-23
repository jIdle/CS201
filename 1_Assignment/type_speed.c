/*
 * Kobe Davis
 * Prof. Morrissey
 * 27 June 2017
 * CS 201
 *
 * First assignment of CS 201. The purpose of this assignment is to record how fast a user can
 * correctly type some given words. Alongside this, this assignment is used for the professor to
 * find out whether we can do some basic programming. This .c file will be submitted along with
 * a Make file and a Typescript.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void opt_rand(char array[9][6], int index, int * max)
{
    --(*max);
    while(index < *max)
    {
        strcpy(array[index], array[index+1]);
        ++index;
    }
}

int main()
{
    int max = 9;    
    char input[6];
    struct timeval start, end, result;
    char array[9][6] = {
        "The",
        "quick",
        "brown",    
        "fox",
        "jumps",
        "over",
        "the",
        "lazy",
        "dog"
    };
    printf("This game will test your typing speed.");
    gettimeofday(&start, NULL);
    srand(start.tv_usec);
    while(max > 0)
    {
        int index = rand() % max;
        do
        {
            printf("Type the word: %s\n", array[index]); 
            scanf("%s", input);
        }while(strcmp(input, array[index]) != 0);
        int c;
        while((c = getchar()) != '\n' && c != EOF);
        opt_rand(array, index, &max);
    }
    gettimeofday(&end, NULL);
    timersub(&end, &start, &result);
    printf("Seconds to complete: %ld seconds and %ld usec\n", result.tv_sec, result.tv_usec);
    return 0;
}








