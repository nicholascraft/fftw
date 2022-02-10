import glob
import re
import os

filenames = glob.glob('output_*.txt')  # list of all .txt files in the directory
sort = sorted(filenames)

filename = input("enter file name: ") + ".txt"

with open(filename, 'w') as f:
    for file in sort:
        with open(file) as infile:
            f.write(infile.read())

for path in filenames: # deletes bajillion text files
    os.remove(path)