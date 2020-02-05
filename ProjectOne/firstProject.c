#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

/*
Seth Hinson & Patrick McCabe
CSCI 340 Project One, Spring 2020
Printing Proc filesystem ids
*/

/*
Struct to define tree structure node 
*/
struct node{


    char exe[32];
    char children[64];
    struct node *next;

};

struct dirent *de;
/*
Main function to initialize program and parse through /proc
*/
int main(int argc, char *argv[]){
    
    DIR *dr = opendir("/proc"); 
    
    //parsing through /proc for PID directories
    while ((de = readdir(dr)) != NULL){ 
        
        char pid[sizeof(de->d_name)];
        strcpy(pid, de->d_name);

        if (isdigit(pid[0])){
            char filepath [32]; 
            strcat(filepath, "/proc/");
            strcat(filepath, pid);
            strcat(filepath, "/stat");

            //debugging print statement
            //printf("filepath: %s\n", filepath);
            
            //operations to open the file
            FILE *file;
            char buf[255];
            printf("filepath: %s\n", filepath)
            file = fopen(filepath, "r");
            
            // dummy variables for parsing 
            int tempd = 0;
            unsigned int tempu = 0;
            long unsigned int templu = 0;
            long int templd = 0;
            long long unsigned int templlu = 0;
            char tempc;
            //real variables
            unsigned int PID;
            char COMM;
            int PPID;
            long unsigned MEMORY;

            fscanf(file, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %d", 
            &PID, &COMM, &tempc, &tempd, &tempd, &tempd, &tempd, &tempd, &tempu, &templu, &templu, &templu, &templu, &templu, &templu, &templd, &templd, &templd, &templd, &templd, &templd, 
            &templlu, &MEMORY, &templd, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &tempd, &tempd, &tempu, &tempu,
            &templlu, &templu, &templd, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &tempd); 
            
            //current problem: parsing /proc/<PID>/stat is messed up
            printf("tempc: %s\n", &tempc);
            printf("PID: %d\n", PID);
            memset(&filepath[0], 0, 32 ); //clear filepath for the next pid  

        }
        

    }
    
    closedir(dr);
    return 0;

}