string = input("Text: ")
words = len(string.split(' '))

letters = 0
sentences = 0
for letter in string:
    if(64 < ord(letter) < 91 or 96 < ord(letter) < 123):
        letters += 1
    if(letter in ['?', '!', '.']):
        sentences += 1

L = 100*(letters/words)
S = 100*(sentences/words)

index = 0.0588 * L - 0.296 * S - 15.8
if(index > 16):
    print("Grade 16+")
if(index < 1):
    print("Before Grade 1")
else:
    print("Grade " + str(round(index)))