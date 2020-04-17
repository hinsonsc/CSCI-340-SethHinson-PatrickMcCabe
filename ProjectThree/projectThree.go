/*
Seth Hinson and Patrick McCabe
Project 3 CSCI 340
16 April 2020
*/

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"sync"
	"time"
)

//Global variables
var totalCounter int = 0  
var counterLock sync.Mutex  
var channelLock sync.Mutex


//Producer function
func producer(wordQ chan string){

	//Locking the channel
	channelLock.Lock()

	//Scanner for file I/O
	fileScanner := bufio.NewScanner(os.Stdin)

	for fileScanner.Scan(){
		
		wordQ <- fileScanner.Text()

	}

	defer channelLock.Unlock()

}

//Consumer function
func consumer(tid int, waitGrp *sync.WaitGroup, wordQ chan string){
	
	//individual counter for the thread
	currCount := 0

	//line parser
	for line := range wordQ{

		fmt.Printf("Thread ID: %d\nString: %s\n", tid, line)
		splitLine := strings.Split(line, " ")

		for _, word := range splitLine{
			
			//Parse for spaces
			if word != "" {

				currCount++

			}

		}

	} 

	//Locking to combine the counters from the threads
	counterLock.Lock()
	totalCounter += currCount
	defer counterLock.Unlock()
	defer waitGrp.Done()

}

//Main method to pass the arguments and start up the program

func main(){

	//Failsafe for the running of the program
	if len(os.Args) != 2{

		fmt.Printf("Usage: go run projectThree.go [number of threads] < [input]")
		os.Exit(0)

	}

	//Q for parsing lines
	wordQ := make(chan string)

	//Consumer Threads
	var consumerThreads, _= strconv.Atoi(os.Args[1])
	
	//Wait group to terminate tasks
	var waitGrp sync.WaitGroup

	for i:= 0; i < consumerThreads; i++{

		//Creating tasks and adding them to the wait group
		waitGrp.Add(1)
		go consumer (i, &waitGrp, wordQ)

	}

	//Spin off producers
	go producer(wordQ)
	time.Sleep(2 * time.Second)

	//Close the Q with lock protection
	channelLock.Lock()
	close(wordQ)
	channelLock.Unlock()

	//Wait for the task terminations
	waitGrp.Wait()

	//print the total words for the user
	fmt.Printf("Total word count for the file: %d\n", totalCounter)
	

}