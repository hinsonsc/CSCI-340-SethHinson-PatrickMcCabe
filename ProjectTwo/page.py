#!/usr/bin/env python3
'''
Seth Hinson & Patrick McCabe
CSCI 340 Project Two, Spring 2020
Page class
'''
class Page:

    data = ""
    pageAddr = 0
    empty = True
    pageSize = 0

    def __init__(self, memory, pagesize, addr):
        
        self.data = memory
        self.pageSize = pagesize
        self.pageAddr =  addr

    def setMemory(self, newdata):
        
        self.data = newdata
    
    def readData(self):
        
        return self.data 
    
    def clean(self):

        self.data = ""

    
