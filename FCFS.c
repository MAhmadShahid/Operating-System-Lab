#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

struct Process{
    int processNumber;
    int cpuBurstTime;
    int arrivalTime;
    int waitTime;
    int TAT;
} process[3];

void sortByArrivalTime(struct Process * process, int numberOfProcess)
{
    struct Process key;
    int j;

    for ( int i = 1; i < numberOfProcess; i++)
    {
        key = process[i];
        j = i - 1;

        while( j >= 0 && (process[j].arrivalTime>key.arrivalTime))
        {
            process[j+1] = process[j];
            j--;
        }

        process[j + 1] = key;
        
    }
}

int main(int argc, char * argv[])
{

    process[0].processNumber = 1;
    process[0].cpuBurstTime = 7;
    process[0].arrivalTime = 2;
    process[0].waitTime = 0;
    process[0].TAT = 0;


    process[1].processNumber = 2;
    process[1].cpuBurstTime = 4;
    process[1].arrivalTime = 0;
    process[1].waitTime = 0;
    process[1].TAT = 0;

    process[2].processNumber = 3;
    process[2].cpuBurstTime = 10;
    process[2].arrivalTime = 3;
    process[2].waitTime = 0;
    process[2].TAT = 0;


    sortByArrivalTime(process, 3);

    process[0].TAT = process[0].cpuBurstTime;

    int timeline = 0 + process[0].arrivalTime;
    for( int i = 1 ; i < 3 ; i ++)
    {
        timeline += process[i-1].cpuBurstTime;
        process[i].waitTime = timeline - process[i].arrivalTime;
        process[i].TAT = timeline + process[i].cpuBurstTime - process[i].arrivalTime;
    }

    printf("%-20s %-20s %-20s %-20s\n", "Process Number", "CPU Burst Time", "Wait Time", "Turn Around Time");

    
    for( int i = 0; i < 3; i ++)
    {
        printf("%-20d %-20d %-20d %-20d \n", process[i].processNumber, process[i].cpuBurstTime, process[i].waitTime, process[i].TAT);
    }


    return 0;
}