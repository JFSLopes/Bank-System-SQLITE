import random

def generate_insert_statements():
    first_names = ['Alice', 'Bob', 'Charlie', 'David', 'Emma', 'Frank', 'Grace', 'Henry']
    last_names = ['Smith', 'Johnson', 'Williams', 'Jones', 'Brown', 'Davis', 'Miller', 'Wilson']

    statements = []

    for i in range(1, 9):  # Assuming you want to generate 8 clients
        first_name = random.choice(first_names)
        last_name = random.choice(last_names)
        email_domain = random.choice(['gmail.com', 'hotmail.com', 'sapo.pt'])
        email = f'{first_name.lower()}_{last_name.lower()}@{email_domain}'
        password = f'password{i}'  # Replace with your own plain passwords

        bank_id = random.randint(1, 1)

        # Generate the SQL statement and add to the list
        if i == 1:
            sql_statement = f"INSERT INTO Client (firstName, lastName, email, encPassWord, bank) VALUES ('{first_name}', '{last_name}', '{email}', '{password}', {bank_id}),"
        else:
            if i == 8:
                sql_statement = f"('{first_name}', '{last_name}', '{email}', '{password}', {bank_id});"
            else:
                sql_statement = f"('{first_name}', '{last_name}', '{email}', '{password}', {bank_id}),"
        statements.append(sql_statement)

    return statements

# Get the list of SQL statements
sql_statements = generate_insert_statements()

# Print the generated SQL statements
for statement in sql_statements:
    print(statement)
