#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <string.h>

//Global variables
int wordCount = 0;
FILE *inputFile;

// Code taken from Queue_V1.c 

typedef struct __node_t {
    
    int               value;
    struct __node_t * next;
    
} node_t;

// Code taken from Queue_V1.c 

typedef struct {
    
    node_t *        head;
    node_t *        tail;
    pthread_mutex_t head_lock;
    pthread_mutex_t tail_lock;

} queue_t;

// Code taken from Queue_V1.c 

void Queue_Enqueue(queue_t * q,
                   int       value) {
    
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp != NULL);
    tmp->value = value;
    tmp->next  = NULL;

    pthread_mutex_lock(&q->tail_lock);
    q->tail->next = tmp;
    q->tail = tmp;
    pthread_mutex_unlock(&q->tail_lock);
    
}

// Code taken from Queue_V1.c 

int Queue_Dequeue(queue_t * q,
                  int *     value) {

    // Failure is always an option
    int rc = -1;
    
    pthread_mutex_lock(&q->head_lock);
    
    node_t *tmp = q->head;
    node_t *new_head = tmp->next;
    if (new_head != NULL) {
        *value = new_head->value;
        q->head = new_head;
        free(tmp);
        rc = 0;
    }
     
    pthread_mutex_unlock(&q->head_lock);
    
    return rc;

}

int countWords(){

    return 0;

}

int main(int argc, char *argv[]){
 
    char str [256];
    char fileName = argv[1]; 
    char *newLine;

    if (fgets(fileName, sizof(fileName), stdin)){ 

        perror("File was not opened");
        return -1;
        
    }
    
    newLine = strchr(fileName, "\n");

    if (newLine){

        *newLine = "\n";

    }

    inputFile = fopen(fileName, "r");

    if (inputFile) {
    
        int chr;
    
        while ((chr = fgetc(inputFile)) != EOF){
    
            fputc(chr, stdout);
            
        }
    
        fclose(inputFile);
    
    } 

    else {

        printf("File not found.");
    
    }

    printf("\n");

    return 0;

}