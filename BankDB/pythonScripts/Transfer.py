from datetime import datetime, timedelta
import random

def generate_random_datetime():
    start_date = datetime(2017, 1, 2)  # Adjusted to start from 2018
    end_date = datetime.now()

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

    for i in range(1, 150):
        date = generate_random_datetime().strftime('%Y-%m-%d %H:%M:%S')
        amount = round(random.uniform(1, 1000),2)  # Random amount between 1 and 1000
        dest = random.randint(1, 8)  # Random destination account ID
        origin = dest

        # Ensure origin and dest are not the same
        while origin == dest:
            origin = random.randint(1, 8)

        type_id = random.randint(1, 2)  # Random type ID (assuming Type has IDs 1 and 2)
        state_id = random.randint(1, 3)  # Random state ID (assuming State has IDs 1, 2, and 3)

        # Generate the SQL statement and add to the list
        if i == 1:
            sql_statement = f"INSERT INTO Transfer (date, amount, origin, dest, type, state) VALUES ('{date}', {amount}, {origin}, {dest}, {type_id}, {state_id}),"
        else:
            if i == 149:
                sql_statement = f"('{date}', {amount}, {origin}, {dest}, {type_id}, {state_id});"
            else:
                sql_statement = f"('{date}', {amount}, {origin}, {dest}, {type_id}, {state_id}),"
        statements.append(sql_statement)

    return statements

# Get the list of SQL statements
sql_statements = generate_insert_statements()

# Print the generated SQL statements
for statement in sql_statements:
    print(statement)

