import sqlite3
import csv
import sys

def main():
    
    if (len(sys.argv) != 2):
        sys.exit("Two arguments required")
        
    housename = sys.argv[1].lower()
    
    houses = ["ravenclaw", "gryffindor", "hufflepuff", "slytherin"]
    
    if housename.lower() not in houses:
        sys.exit("Not a house name")
        
    con = sqlite3.connect("students.db")
    cur = con.cursor()
    
    cur.execute('SELECT first, middle, last, birth FROM students WHERE lower(house) = "{}" ORDER BY last, first;'.format(housename))
    
    table = cur.fetchall()
    
    for row in table:

        if not row[1]:
            print("{} {}, born {}".format(row[0], row[2], row[3]))
        else:
            print("{} {} {}, born {}".format(row[0], row[1], row[2], row[3]))

    con.close()

if __name__ == "__main__":
    main()