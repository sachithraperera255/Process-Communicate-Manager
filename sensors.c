#include "headers.h"

int main(int argc, char *argv[])
{
    //check for correct amount of arguments provided from the user.
    if (argc != 3)
    {
        printf("\nNot enough or more argument\n");
        exit(EXIT_FAILURE);
    }

    //calling the strct in "headers.h";
    passData compareTreshold;

    //saving data in the struct.
    compareTreshold.device_Name = argv[1];
    compareTreshold.treshold_Value = atoi(argv[2]);
    //printing terminal argument inputs
    printf("\nName of the device: %s\n", compareTreshold.device_Name);
    printf("\nEntered treshold value: %d\n", compareTreshold.treshold_Value);

    //decleairng sensorValue variable.
    int sensorValue;

    //generating random numbers if any argumets are entred.
    if (argc > 0)
    {
        srand(time(NULL));
        sensorValue = rand() % 50;
        printf("\nSensor value: %d\n", sensorValue);
    }

    //writing the fifo3 twice since there are 2 devices.
    while (1)
    {
        //fifo3 write to the controller from sensor.
        mkfifo("fifo3", 0777);
        int sensor_fifo = open("fifo3", O_WRONLY);
        //checking for any opening errors for fifo3.
        if (sensor_fifo == -1)
        {
            exit(EXIT_FAILURE);
        }

        //fifo3 is writing to the controller and checking for any wrting errors.
        if (write(sensor_fifo, &sensorValue, sizeof(int)) == -1)
        {
            exit(EXIT_FAILURE);
        }

        // closing fifo3.
        close(sensor_fifo);
    }

    return 0;
}