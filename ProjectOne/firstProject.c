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

            FILE *file;
            char buf[255];
            file = fopen(filepath, "r");

            memset(&filepath[0], 0, 32);
            //printf("%s\n", temp);    
        }
        

    }
    
    closedir(dr);
    return 0;

}