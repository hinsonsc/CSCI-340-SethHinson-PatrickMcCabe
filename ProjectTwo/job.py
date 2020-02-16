#!/usr/bin/env python3
'''
Seth Hinson & Patrick McCabe
CSCI 340 Project Two, Spring 2020
Job Class
'''

class job:

    jobID = 0
    runtimeLength = 0
    memorySize = 0
    status = "Starting"
    startTime = 1
    endTime = 0 

    def __init__(self, jobNumber, runtime, memory):
        
        self.jobID = jobNumber
        self.runtimeLength = runtime
        self.memorySize = memory
    
    def setStatus (self, stat):
        
        self.status = stat
    
    def getStatus(self):

        return self.status
    
    def getStartTime(self):

        return self.startTime

    def setEndTime(self, time):
        
        self.endTime = time

    def getEndTime(self):

        return self.endTime

    def __str__(self):
        returnStr = str(self.jobID) + '\t' + str(self.runtimeLength) + '\t' + str(self.memorySize)
        return returnStr
