import pandas as pd

bin8 = pd.read_csv('bin8.txt', header = None, sep = ' ')
bin8hamm = pd.read_csv('bin8hamm.txt', header = None, sep = ' ')
bin8hann = pd.read_csv('bin8hann.txt', header = None, sep = ' ')

print(bin8.sum())
print(bin8hamm.sum())
print(bin8hann.sum())