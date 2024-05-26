from cs50 import SQL
import csv

# Open database
db = SQL("sqlite:///roster.db")

with open("students.csv") as file:
    reader = csv.DictReader(file)
    # Keep track of already inserted heads and houses
    heads, houses, students = set(), set(), set()
    ''' Check for the heads and houses already in the database '''
    previous_heads = db.execute("SELECT (head) FROM heads")
    previous_houses = db.execute("SELECT (house) FROM houses")
    previous_students = db.execute("SELECT (student_name) FROM students")

    ''' ADD previous _heads and _houses to heads and houses sets '''
    for hd in previous_heads:
        try:
            heads.add(hd['head'])
        except TypeError:
            pass
    for hse in previous_houses:
        try:
            houses.add(hse['house'])
        except TypeError:
            pass
    for stud in previous_students:
        try:
            students.add(stud['student_name'])
        except TypeError:
            pass

    # Iterate over each student's dict()
    for student in reader:
        #'' Go to next student if the student is already in database ''
        if not (student['student_name'] in students):

            #'' INSERT in heads and houses TABLE if needed''
            if not (student['head'] in heads):
                heads.add(student['head'])
                # INSERT new head in heads TABLE
                db.execute("INSERT INTO heads (head) VALUES (?)", student['head'])

            if not (student['house'] in houses):
                houses.add(student['house'])
                # INSERT new house in houses TABLE
                db.execute("INSERT INTO houses (house) VALUES (?)", student['house'])

            #'' INSERT the new student in students TABLE ''
            house_id = db.execute("SELECT (house_id) FROM houses WHERE house = ?", student['house'])
            head_id = db.execute("SELECT (head_id) FROM heads WHERE head = ?", student['head'])
            db.execute("INSERT INTO students (student_name, house_id, head_id) VALUES (?, ?, ?)", student['student_name'], house_id[0]['house_id'], head_id[0]['head_id'])

        else:
            students.add(student['student_name'])
