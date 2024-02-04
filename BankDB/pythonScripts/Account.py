from datetime import datetime, timedelta
import random

def generate_random_datetime():
    start_date = datetime(2000, 1, 1)
    end_date = datetime(2017,1,1)

    time_difference = end_date - start_date
    random_days = random.randint(0, time_difference.days)
    random_hours = random.randint(0, 23)
    random_minutes = random.randint(0, 59)
    random_seconds = random.randint(0, 59)

    random_datetime = start_date + timedelta(
        days=random_days,
        hours=random_hours,
        minutes=random_minutes,
        seconds=random_seconds
    )

    return random_datetime

def generate_insert_statements():
    statements = []

    for i in range(1, 9):
        balance = i * 1000.0  # Vary the initial balance for each account
        date = generate_random_datetime().strftime('%Y-%m-%d %H:%M:%S')
        client_id = i  # Assuming client IDs start from 1

        # Generate the SQL statement and add to the list
        if i == 1:
            sql_statement = f"INSERT INTO Account (balance, date, client) VALUES ({balance}, '{date}', {client_id}),"
        else:
            if i == 8:
                sql_statement = f"({balance}, '{date}', {client_id});"
            else:
                sql_statement = f"({balance}, '{date}', {client_id}),"
        statements.append(sql_statement)

    return statements

# Get the list of SQL statements
sql_statements = generate_insert_statements()

# Print the generated SQL statements
for statement in sql_statements:
    print(statement)
