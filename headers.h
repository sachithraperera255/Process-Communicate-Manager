#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>



typedef struct pass_data
{
    char *device_Name;
    int treshold_Value;
    pid_t processor_id;
}passData;

