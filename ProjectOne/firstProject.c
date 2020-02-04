#include <stdio.h>
#include <dirent.h>
/*
Seth Hinson & Patrick McCabe
CSCI 340 Project One, Spring 2020
Printing Proc filesystem ids
*/

struct node {

    char parent[16];
    char child[16];
    struct node *next;


};

struct dirent *de;

int main(int argc, char *argv[]){
    
    DIR *dr = opendir("/proc");

     if (dr == NULL){ // opendir returns NULL if couldn't open directory  
        printf("Could not open current directory" ); 
        return 0; 
    } 

    while ((de = readdir(dr)) != NULL) 
            printf("%s\n", de->d_name); 

    closedir(dr);
    return 0;

}