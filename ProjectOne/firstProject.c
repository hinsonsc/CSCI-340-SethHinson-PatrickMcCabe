#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
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
            printf("filepath: %s\n", filepath);
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
            char * COMM = malloc(32 * sizeof(char));
            int PPID;
            long unsigned MEMORY;
            char check[] = ")";
            char * r;
            
            fscanf(file, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %d", 
            &PID, COMM, &tempc, &PPID, &tempd, &tempd, &tempd, &tempd, &tempu, &templu, &templu, &templu, &templu, &templu, &templu, &templd, &templd, &templd, &templd, &templd, &templd, 
            &templlu, &MEMORY, &templd, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &tempd, &tempd, &tempu, &tempu,
            &templlu, &templu, &templd, &templu, &templu, &templu, &templu, &templu, &templu, &templu, &tempd); 
            

            r = strpbrk(COMM, check);
            //issues reading file for PPID of (Web content)
            if(r == 0){
                fscanf(file, "%d %s %c %d %d*", 
            &PID, COMM, &tempc, &tempd, &PPID ); 
            
                
                COMM = "(Web Content)";

            }
            
            fclose(file);
            
            //current problem: parsing /proc/<PID>/stat is messed up


          
            printf("COMM: %s\n", COMM);
            printf("PPID: %d\n", PPID);
          
            PID = 0;
            
            PPID = 0;
            MEMORY = 0;
            memset(&filepath[0], 0, 32 ); //clear filepath for the next pid  



        }
        

    }

    closedir(dr);
    return 0;

}