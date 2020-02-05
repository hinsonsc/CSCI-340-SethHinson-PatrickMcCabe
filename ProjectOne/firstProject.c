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
        char temp[16];
        strcpy(temp, de->d_name);
        if (isdigit(temp[0])){

            //printf("%s\n", temp);    
        }
        

    }
    
    closedir(dr);
    return 0;

}