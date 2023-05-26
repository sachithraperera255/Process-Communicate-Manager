#include "headers.h"

void handle_siguserEnter1(int sig)
{
    printf("\nWriting information in the cloud\n");
}

int main()
{

    passData getInput;
    int b;

    int pid = fork();

    if (pid == 0)
    {
        printf("\nIn the child process, process id is %d\n", getpid());

        // Read values from sensor throught fifo3.
        int sensor_fifo = open("fifo3", O_RDONLY);

        // checking for opening errors
        if (sensor_fifo == -1)
        {
            exit(EXIT_FAILURE);
        }

        //saving sensor values at b.
        if (read(sensor_fifo, &b, sizeof(int)) == -1)
        {
            exit(EXIT_FAILURE);
        }
        if (b < getInput.treshold_Value)
        {
            printf("\nsensor value is less than threshold value\n");
            return 0;
        }
        //comparing sensor values to the treshold value
        if (b >= getInput.treshold_Value)
        {
            //fifo1 write to the actuator and cheking for opening errors.
            mkfifo("fifo1", 0777);
            int actuator_fifo = open("fifo1", O_WRONLY);
            if (actuator_fifo == -1)
            {
                exit(EXIT_FAILURE);
            }
            //writing to the fifo1 (actuator_fifo)
            if (write(actuator_fifo, "\nTurning off the device\n", sizeof("\nTurning off the device\n")) == -1)
            {
                exit(EXIT_FAILURE);
            }
            close(actuator_fifo);
            //Sending kill signal to the parent
            sleep(5);
            kill(getppid(), SIGUSR1);
        }

        printf("\nEnd of the child process\n");
    }
    else
    {
        //handling signal
        struct sigaction sa;
        sa.sa_handler = &handle_siguserEnter1;
        sigaction(SIGUSR1, &sa, NULL);
        
        //waiting for the kill signal
        pause();

        printf("\nIn parent process, process id is %d\n", getppid());

        //fifo2 write to the cloud and checking for opening errors
        mkfifo("fifo2", 0777);
        int cloud_fifo = open("fifo2", O_WRONLY);
        if (cloud_fifo == -1)
        {
            exit(EXIT_FAILURE);
        }

        //writing the message to the cloud
        if (write(cloud_fifo, "\nOver the treshold value!\n", sizeof("\nOver the treshold value!\n")) == -1)
        {
            exit(EXIT_FAILURE);
        }
        close(cloud_fifo);

        printf("\nEnd of parent process\n");
    }

    return 0;
}