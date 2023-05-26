#include "headers.h"
#define BUFFER_SIZE 1024

int main()
{
    //this string of char save the provides message from the parent process in controller.c
    char str[BUFFER_SIZE];
    
    //opening fifo2(cloud_fifo) and checking for any fifo opening errors
    int cloud_fifo = open("fifo2", O_RDONLY);
    if (cloud_fifo == -1)
    {
        exit(EXIT_FAILURE);
    }
    
    //reading to str and checking for any reading errors
    if (read(cloud_fifo, &str, BUFFER_SIZE) == -1)
    {
        exit(EXIT_FAILURE);
    }

    //printing the message
    printf("%s\n", str);
    close(cloud_fifo);
}