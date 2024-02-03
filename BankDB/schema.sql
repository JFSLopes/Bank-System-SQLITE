PRAGMA foreign_keys = ON;
CREATE TABLE MyBank(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(20) NOT NULL
);
CREATE TABLE Client(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    firstName VARCHAR(15) NOT NULL,
    lastName VARCHAR(15) NOT NULL,
    email VARCHAR(30) CHECK(
        email LIKE '%@%'
        AND (
            email LIKE '%gmail.com'
            OR email LIKE '%hotmail.com'
            OR email LIKE '%sapo.pt'
        )
    ),
    bank INTEGER,
    FOREIGN KEY (bank) REFERENCES Bank(id) ON UPDATE CASCADE ON DELETE
    SET NULL
);
CREATE TABLE Account()