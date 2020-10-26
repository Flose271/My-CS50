from csv import reader, DictReader
from sys import argv

def stringin(string,x):
    count = 0
    for start in range(len(string) - len(x) + 1):
        snippet = string[start:start+len(x)]
        if(snippet == x):
            count += 1
    return count
    

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