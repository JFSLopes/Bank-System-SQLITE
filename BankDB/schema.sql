PRAGMA foreign_keys = ON;
DROP TABLE IF EXISTS MyBank;
DROP TABLE IF EXISTS Client;
DROP TABLE IF EXISTS Account;
DROP TABLE IF EXISTS State;
DROP TABLE IF EXISTS Type;
DROP TABLE IF EXISTS Transfer;
CREATE TABLE State(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    state VARCHAR(15) NOT NULL
);
CREATE TABLE Type(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    type VARCHAR(15) NOT NULL
);
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
    hashPassWord VARCHAR(60) NOT NULL UNIQUE,
    salt VARCHAR(20) NOT NULL UNIQUE,
    bank INTEGER,
    FOREIGN KEY (bank) REFERENCES Bank(id) ON UPDATE CASCADE ON DELETE CASCADE
);
CREATE TABLE Account(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    balance REAL CHECK(balance > 0),
    date DATETIME NOT NULL,
    client INTEGER,
    FOREIGN KEY (client) REFERENCES Client(id) ON UPDATE CASCADE ON DELETE CASCADE
);
CREATE TABLE Transfer(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    date DATETIME NOT NULL,
    amount REAL CHECK(amount > 0),
    origin INTEGER,
    dest INTEGER,
    type INTEGER,
    state INTEGER,
    FOREIGN KEY(origin) REFERENCES Account(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY(dest) REFERENCES Account(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY(type) REFERENCES Type(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY(state) REFERENCES State(id) ON UPDATE CASCADE ON DELETE CASCADE,
    CHECK (origin != dest)
);