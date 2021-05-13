import psycopg2
from configparser import ConfigParser

conn = psycopg2.connect(
    host="localhost",
    database="postgres",
    user="postgres",
    password="postgres")


cursor = conn.cursor()

cursor.execute("SELECT * FROM monsters")
record = cursor.fetchall()
print(record)

cursor.execute(
    '''INSERT INTO monsters(name, race, lvl, hp, atk, def)
    VALUES('Bahamut', 'Dragon', 99, 500000, 5000, 5000)'''
)
cursor.execute("SELECT * FROM monsters")
record = cursor.fetchall()
print(record)

conn.commit()
cursor.close()
conn.close()