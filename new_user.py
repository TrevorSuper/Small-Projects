import sqlite3

# New user script
# need to import string to name database. Every user should have their own separate database.

connection = sqlite3.connect('email_id.db') # will create 'email_id.db' if it does not already exist
cursor = connection.cursor() # cursor is required to interact with the database
create_user_table = """CREATE TABLE IF NOT EXISTS
user(email_id TEXT PRIMARY KEY, login_password TEXT, master_password TEXT)"""
cursor.execute(create_user_table)

# create_user_stored_information = """CREATE TABLE IF NOT EXISTS
# user_stored_information(master_password TEXT PRIMARY KEY,
# Folder1 TEXT,
# Folder2 TEXT,
# Folder3 TEXT)"""
# cursor.execute(create_user_stored_information)
# connection.commit()

# create_folder1 = """CREATE TABLE IF NOT EXISTS
# Folder1(Folder1 TEXT PRIMARY KEY)"""
# create_folder2 = """CREATE TABLE IF NOT EXISTS
# Folder2(Folder2 TEXT PRIMARY KEY)"""
# create_folder3 = """CREATE TABLE IF NOT EXISTS
# Folder3(Folder3 TEXT PRIMARY KEY)"""
# cursor.execute(create_folder1)
# cursor.execute(create_folder2)
# cursor.execute(create_folder3)
# connection.commit()

connection.close()