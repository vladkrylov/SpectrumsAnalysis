#!/usr/bin/python

import os
from os import listdir
from subprocess import call

config_file = open('config', 'w')

datadir = '/data'
basedir = os.path.abspath(os.path.dirname(__file__))
gdatadir = basedir + datadir

config_file.write('DATADIR=' + datadir[1:] + '\n')

files = listdir(gdatadir)
datafiles = []
datafiles1 = []
number_of_spectrums = 0

for fname in files:
    if fname[0] == 'd' and fname[-4:] == '.txt' and fname[1:-4].isdigit() and len(fname) == 6:
        datafiles.append(fname)
        number_of_spectrums += 1
datafiles.sort()

for fname in files:
    if fname[0] == 'd' and fname[-4:] == '.txt' and fname[1:-4].isdigit() and len(fname) == 7:
        datafiles1.append(fname)
        number_of_spectrums += 1
datafiles1.sort()
datafiles.extend(datafiles1)
        
config_file.write("NUMBER_OF_SPECTRUMS=" + str(number_of_spectrums) +"\n")
        

config_file.write("DATAFILES:\n")
for fname in datafiles:
    config_file.write(fname + '\n')
    
config_file.close()

call(["./test_spectrum", "-nos", "8"])

