#include "headers.h"
#define BUFFER_SIZE 1024

int main()
{
    //this string of char save the provides message from the parent process in controller.c
    char str1[BUFFER_SIZE];
    
    // opening fifo1(actuator_fifo) and checking for any fifo opening errors
    int actuator_fifo = open("fifo1", O_RDONLY);
    if(actuator_fifo == -1)
    {
        exit(EXIT_FAILURE);
    }

    //reading to str1 and checking for any reading errors
    if(read(actuator_fifo, &str1, BUFFER_SIZE) == -1)
    {
        exit(EXIT_FAILURE);
    }

    //printing the message
    printf("%s\n", str1);
    close(actuator_fifo);

    return 0;
}