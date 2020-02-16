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

    for i in range(numberOfJobs):

        runtime = random.randint(runtimeMin, runtimeMax)  
        
        memory = random.randint(memoryMin, memoryMax) * int(sys.argv[2])
        
        jobs.append( job(i + 1, runtime, memory))
    
    print(colored('\nJob Queue:', 'blue'))
    
    print(colored('Job #\tRuntime\tMemory', 'blue'))
    
    for jb in jobs:
        
        print(colored(str(jb),'blue')) 
    
    return jobs

def jobsAreRunning(activeJobs):

    for job in activeJobs:
        
        if (job.getStatus() == 'Running' or job.getStatus() == 'Starting'):
            
            return True
    
    return False

def simulator(jobs):

    print(colored('\nSimulator Starting:\n', 'green'))
    
    numSteps = 0

    while (jobsAreRunning(jobs)):
        
        numSteps += 1
        
        if(numSteps == 1):
            
            for i in range(len(jobs)):
                
                print('Job ' + str(i + 1) + ' Starting')
            
            print('Job 1 Running')
            
            jobs[0].setStatus('Running')
            
            jobs[0].run()
        
        else:
            
            runningJob = numSteps % (len(jobs)) 
            
            if(runningJob == 0):
                
                runningJob = len(jobs)

            noRun = True
            
            while(noRun):
                #print('Running Job: ' + str(runningJob)) debug for running job out of bounds
                if(jobs[runningJob - 1].isComplete()):
                
                    runningJob = (runningJob + 1) % len(jobs)
                    
                    if(runningJob == 0):
                        
                        runningJob = len(jobs)
                
                else:

                    jobs[runningJob - 1].setStatus('Running')

                    jobs[runningJob - 1].run()
                    
                    print('Job ' + str(runningJob) + ' Running')
                    
                    if(jobs[runningJob - 1].isComplete()):
                        
                        print('Job ' + str(runningJob) + ' Completed')
                    
                    noRun = False
'''
To do list:
1. Page table output
2. Job info @ end
3. Make pretty 
4. Document
5. Profit
'''
def main():
    
    random.seed(os.environ['RANDOM_SEED'])
    
    if len(sys.argv) != 8:
        
        print(colored('Invalid number of arguments', 'red'))
        
        print(colored('Proper usage: ./projecttwo.py <memory size> <page size> <number of jobs> <runtime min> <runtime max> <job memory min> <job memory max>', 'red'))
    
    else:
        
        print(colored('\nProper number of arguments passed!\n', 'green'))
        
        #print(colored(str(sys.argv[1]), 'green')) used for debugging sys.argv input
        
        printParams()
        
        jobQ = createJobs()
        
        simulator(jobQ)


main()