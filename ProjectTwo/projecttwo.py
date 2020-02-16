#!/usr/bin/env python3
'''
Seth Hinson & Patrick McCabe
CSCI 340 Project Two, Spring 2020
Round Robbin Simulator
'''
import sys, page, os, random
from termcolor import colored

def printParams():
    
    print(colored('Memory Size: ' + str(sys.argv[1]), 'blue'))
    print(colored('Page Size: ' + str(sys.argv[2]), 'blue'))
    print(colored('Random Seed: ' + str(os.environ['RANDOM_SEED']), 'blue'))
    print(colored('Number of jobs: ' + str(sys.argv[3]), 'blue'))
    print(colored('Runtime (min-max) timesteps: ' + str(sys.argv[4]) + '-' + str(sys.argv[5]), 'blue'))
    print(colored('Memory (min-max): ' + str(sys.argv[6]) + '-' + str(sys.argv[7]), 'blue'))

def createJobs():

    numberOfJobs = int(sys.argv[3])
    runtimeMin = int(sys.argv[4])
    runtimeMax = int(sys.argv[5])
    memoryMin = int(sys.argv[6])
    memoryMax = int(sys.argv[7])
    
    

def main():
    
    random.seed(os.environ['RANDOM_SEED'])
    if len(sys.argv) != 8:
        print(colored('Invalid number of arguments', 'red'))
        print(colored('Proper usage: ./projecttwo.py <memory size> <page size> <number of jobs> <runtime min> <runtime max> <job memory min> <job memory max>', 'red'))
    else:
        print(colored('Proper number of arguments passed!', 'green'))
        #print(colored(str(sys.argv[1]), 'green')) used for debugging sys.argv input
        printParams()
        createJobs()

main()