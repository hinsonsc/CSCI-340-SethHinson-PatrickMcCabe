#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

//Global variables
int wordCount = 0;
#define BUFSIZE 100
FILE *fp;
char buff[BUFSIZE];

char *bruce_buffer[5000][BUFSIZE];

//declaration of semaphores
sem_t full;
sem_t empty;
sem_t mutex;

//max for the Q
const int MAX = 15;
int done = 0;

int q_num = 0;

// Code taken from Queue_V1.c 

typedef struct __node_t {
    
    int              value;
    struct __node_t * next;
    
} node_t;

// Code taken from Queue_V1.c 

typedef struct {
    
    node_t *        head;
    node_t *        tail;
    pthread_mutex_t head_lock;
    pthread_mutex_t tail_lock;

} queue_t;

queue_t *Q;

// Code taken from Queue_V1.c 

void Queue_Init(queue_t *q) {
    
    node_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;
    
    pthread_mutex_init(&q->head_lock, NULL);
    pthread_mutex_init(&q->tail_lock, NULL);
    
}


// Code taken from Queue_V1.c 

void Queue_Enqueue(queue_t * q, int value) {
    
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp != NULL);
    tmp->value = value;
    tmp->next  = NULL;

    sem_wait(&full);
    pthread_mutex_lock(&q->tail_lock);
    q->tail->next = tmp;
    q->tail = tmp;
    sem_post(&empty);
    pthread_mutex_unlock(&q->tail_lock);
    
}

// Code taken from Queue_V1.c 

int Queue_Dequeue(queue_t * q,int *value) {

    // Failure is always msan option
    int rc = -1;
    
    sem_wait(&empty);
    pthread_mutex_lock(&q->head_lock);
    
    node_t *tmp = q->head;
    node_t *new_head = tmp->next;
    if (new_head != NULL) {
        *value = new_head->value;
        q->head = new_head;
        free(tmp);
        rc = 0;
    }

    sem_post(&full);
    pthread_mutex_unlock(&q->head_lock);
    
    return rc;

}



int countWords (char buffer[]){

    //used to interate over the string
    int counter = 0;

    //checks for only single spaces for accuracy
    if (strlen(buffer) > 2) {
        
        //iterates over the line
        while(counter < strlen(buffer)){
            
            //checks for special characters to signify a word
            if ((buffer[counter] == ' ' || buffer[counter] == '\n' || buffer[counter] == '\0') 
                && (buffer[counter - 1] != ' ')){
                
                //protection for the counter from the threads
                sem_wait(&mutex);
                wordCount++;
                sem_post(&mutex);

            }

            //move to the next array index
            counter++;

        }

    }
    //printf("Buffer: %s\n", buffer);

    return 0;

}

void *consumer(void* arg){

    //gets the thread id and converts to int
    int t_id = (long)arg;

    //decriments empty
    sem_wait(&empty);

    int locate;

    Queue_Dequeue(Q, locate);

    //used to take lines off of the Q
    char michael_buffer = bruce_buffer[locate];

    //incriment full
    sem_post(&full);

    //function to count words
    countWords(michael_buffer);

    return NULL;
}

void *producer(){

    //char file = (char)arg; 

    //FILE *fp = fopen(file, "r"); 

     
    //parses the files for the lines and adds them to the Q
    while(fgets(buff, BUFSIZE - 1, fp) != NULL) {
            
            //decriments full
            sem_wait(&full);
            
            Queue_Enqueue(Q, q_num);
            q_num++;

            *bruce_buffer[q_num - 1] = buff;

            //incriments empty
            sem_post(&empty);

            //printf("Buff: %s\n", buff);
            //printf("Word count: %d\n", wordCount);

    }

    fclose(fp);

    done = 1;

    return NULL;

}



int main(int argc, char *argv[]){

    //check for the args
    if (argc != 3){

        printf("Usage: ./projectThree <filename or path> <number of threads>\n");
        exit(1);

    }

    //initialize the semaphores
    sem_init(&full, 0, 15);
    sem_init(&empty, 0, 0);
    sem_init(&mutex, 0, 1);

    //debugging
    printf("argc: %d\n", argc);
    printf("Argv[1]: %s\n", argv[1]);
    printf("Threads: %s\n", argv[2]);

    //opening the file
    fp = NULL;
    fp = fopen(argv[1], "r");

    //file pointer check
    if (fp == NULL){

        printf("File failed!\n");
        exit(1);

    }

    //Initialize the queue
    Q = malloc(sizeof(node_t) * 15);

    Queue_Init(Q);

    //number of threads to create
    int num_threads = atoi(argv[2]);

    //producer and consumer threads
    pthread_t consumers_t [num_threads];
    pthread_t producer_t;

    //rip off the producer thread
    assert(pthread_create(&producer_t, NULL, (void*)producer, NULL) == 0);

    //array for the threads
    int thread_args[num_threads];

    for (int i = 0; i < argv[2]; i++){
        
        //thread ID and the creation of the consumers
        thread_args[i]= i;
        assert(pthread_create(&consumers_t[i], NULL, consumer, (void *)&thread_args[i]) == 0);
        
    }

    //check on if the threads are done

    while(1 == 1){

        int val;
        sem_getvalue(&empty, val);

        if((done == 1) && (val <= 0)){

            for(int i = 0; i < num_threads; i++){
                
                //join all the threads together
                assert(pthread_join(consumers_t[i], NULL) == 0);

            }

        }

    }

    //final wordcount
    printf("Word count: %d\n", wordCount);

    
}

/**
 * 
 * pthread_t thread;
            threads[i] = thread;
           
            pthread_create(&threads[i], NULL, countWords, buff); 
 * 
 * 
 * 
*/ 