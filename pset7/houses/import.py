import sqlite3
import sys
import csv

def main():

    if(len(sys.argv) != 2):
        sys.exit("Two arguments required")

    con = sqlite3.connect("students.db")
    cur = con.cursor()
    csvfile = open(sys.argv[1], "r")

    reader = csv.DictReader(csvfile)

    for row in reader:

        values = row["name"].split(' ')
        values.append(row["house"])
        values.append(row["birth"])

        if (len(values) == 5):
                cur.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", values[:5])

        if (len(values) == 4):
            cur.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)", values[:4])

    con.commit()
    con.close()

if __name__ == "__main__":
    main()