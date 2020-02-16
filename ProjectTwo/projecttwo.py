#!/usr/bin/env python3
'''
Seth Hinson & Patrick McCabe
CSCI 340 Project Two, Spring 2020
Round Robbin Simulator
'''
import sys, os, random
from page import *
from job import *
from termcolor import colored

def printParams():
    
    print(colored('Memory Size: ' + str(sys.argv[1]), 'magenta'))
    print(colored('Page Size: ' + str(sys.argv[2]), 'magenta'))
    print(colored('Random Seed: ' + str(os.environ['RANDOM_SEED']), 'magenta'))
    print(colored('Number of jobs: ' + str(sys.argv[3]), 'magenta'))
    print(colored('Runtime (min-max) timesteps: ' + str(sys.argv[4]) + '-' + str(sys.argv[5]), 'magenta'))
    print(colored('Memory (min-max): ' + str(sys.argv[6]) + '-' + str(sys.argv[7]), 'magenta'))

def createJobs():

    numberOfJobs = int(sys.argv[3])
    runtimeMin = int(sys.argv[4])
    runtimeMax = int(sys.argv[5])
    memoryMin = int(sys.argv[6]) // int(sys.argv[2])
    memoryMax = int(sys.argv[7]) // int(sys.argv[2])
    
    jobs = []

    for i in range(numberOfJobs - 1):

        runtime = random.randint(runtimeMin, runtimeMax)  
        memory = random.randint(memoryMin, memoryMax) * int(sys.argv[2])
        jobs.append( job(i + 1, runtime, memory))
    
    print(colored('\nJob Queue:', 'blue'))
    print(colored('Job #\tRuntime\tMemory', 'blue'))
    for jb in jobs:
        print(colored(str(jb),'blue')) 
    


def main():
    
    random.seed(os.environ['RANDOM_SEED'])
    if len(sys.argv) != 8:
        print(colored('Invalid number of arguments', 'red'))
        print(colored('Proper usage: ./projecttwo.py <memory size> <page size> <number of jobs> <runtime min> <runtime max> <job memory min> <job memory max>', 'red'))
    else:
        print(colored('\nProper number of arguments passed!\n', 'green'))
        #print(colored(str(sys.argv[1]), 'green')) used for debugging sys.argv input
        printParams()
        createJobs()

main()