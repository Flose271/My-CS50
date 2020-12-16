n = 0

while(not 0 < n < 9):
    n = input("Size: ")
    try:
        n = int(n)
    except:
        n = 0
    
for i in range(1, n + 1):
    layer = ""
    layer += " " * (n - i)
    layer += "#" * i
    layer += " " * 2
    layer += "#" * i
    print(layer)