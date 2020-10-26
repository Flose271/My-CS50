from csv import reader, DictReader
from sys import argv

def stringin(string,x):
    count = 0
    maxcount = 0
    start = 0
    while True:
        snippet = string[start:start+len(x)]
        #print(snippet)
        if(snippet == x):
            #print("True")
            count += 1
            start += len(x)
        else:
            #print("False")
            if(count > maxcount):
                maxcount = count
            count = 0
            start += 1
        #print(count)
        if start > (len(string) - len(x) + 1):
            break
        
    return maxcount
    


if len(argv) < 3:
    print("usage error, dna.py sequence.txt database.csv")
    exit()

with open(argv[2]) as dnafile:
    dnareader = list(reader(dnafile))
    dna = dnareader[0][0]

with open(argv[1]) as peoplefile:
    people = list(reader(peoplefile))

strs = people[0].copy()
del strs[0]
strcounts = [0 for i in range(len(strs))]

for i in range(len(strs)):
    strcounts[i] = stringin(dna, strs[i])
    
strcounts = [str(s) for s in strcounts]

print(dna)

print(strcounts)

print(people)

match = False
for row in people:
    rowcounts = row.copy()
    del rowcounts[0]
    if(rowcounts == strcounts):
        print(row[0])
        match = True
if(not match):
    print("No Match")