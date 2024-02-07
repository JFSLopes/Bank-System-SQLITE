# Simple Local SQLite Database Interaction

This project demonstrates a simple interaction with a local SQLite database using an uncomplicated application. It showcases the direct communication between the application and the SQLite database without the overhead of a separate API layer. The primary focus is on illustrating how an application interacts with a SQLite database, emphasizing simplicity and clarity over complexity.

## Overview

The project consists of a simple application written in C++ that interacts directly with a local SQLite database file (.db) stored on the user's machine. The application performs basic CRUD (Create, Read, Update, Delete) operations on the database, allowing users to manage data efficiently.

## Technologies Used

- **SQLite**: SQLite serves as the lightweight and easy-to-use relational database management system (RDBMS) for storing and managing the application's data.
- **C++**: The application is written in C++ for its simplicity and efficiency, providing direct access to the SQLite database file.
- **SQLite C/C++ Interface**: The application utilizes the SQLite C/C++ interface to execute SQL queries and interact with the SQLite database.

## Functionality

The application offers the following functionality:

- **Database Initialization**: The application initializes the SQLite database file if it doesn't exist, creating the necessary tables and schema.
- **Data Management**: Users can perform basic CRUD operations on the database, including adding, retrieving, updating, and deleting records.
- **Query Execution**: Users can execute custom SQL queries directly on the database, enabling more advanced data manipulation.

## Usage

To use the application:

1. **Compile the Application**: Compile the C++ application source code using a C++ compiler compatible with your operating system.
2. **Run the Application**: Execute the compiled application binary, which will interact with the local SQLite database file.
3. **Interact with the Database**: Use the application's user interface to perform various operations on the database, such as adding, retrieving, updating, or deleting records.

## Contributions

Contributions to the project are welcome! If you have any ideas for improvements or new features, feel free to submit a pull request or open an issue on the GitHub repository.
