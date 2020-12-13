# Returns sum of digits in an integer
def sumdigits(integer):
    string = str(integer)
    total = 0
    for letter in string:
        total += int(letter)
    return total

# Gets an integer input
while(True):
    n = input("Number: ")
    try:
        n = int(n)
        break
    except:
        pass

# Makes the input a string for handling
n = str(n)
length = len(n)
# Our final total
totalsum = 0

# Gets the numbers that need to be doubled in a list
double_numbers = [n[i] for i in range(length % 2, length, 2)]
# Doubles each of them
double_numbers = [2 * int(d) for d in double_numbers]
# Applies the sum digits function
double_numbers = [sumdigits(d) for d in double_numbers]
# Adds the sum to totalsum
totalsum += sum(double_numbers)

# Gets the numbers that don't need to be doubled
single_numbers = [n[i] for i in range(1 - length % 2, length, 2)]
# Converts them to integers
single_numbers = [int(s) for s in single_numbers]
# Adds the sum to totalsum
totalsum += sum(single_numbers)

# If not a valid number
if(totalsum % 10 != 0):
    print("INVALID")
# If length 15 and starts with 34 or 37
elif(length == 15 and n[0] == '3' and (n[1] == '4' or n[1] == '7')):
    print("AMEX")
# If length 16 and starts with 51, 52, 53, 54 or 55
elif(length == 16 and n[0] == '5' and 0 < int(n[1]) < 6):
    print("MASTERCARD")
# If length 13 or 16 and starts with 4
elif((length == 13 or length == 16) and n[0] == '4'):
    print("VISA")
else:
    print("INVALID")