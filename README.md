# Bank System (C++ OOP)

A console-based bank management system written in C++ using Object-Oriented Programming. It is an upgraded version of my first Bank Management System, rebuilt with classes and with many added features.

## Features

**Client Management**
- Add new clients
- Update and delete clients
- Find a client
- View the full clients list

**Transactions**
- Deposit
- Withdraw
- Transfer money between clients
- View total balances
- Transfer log that records every transfer

**User Management**
- Add, update, delete, and find system users
- View the users list
- Permissions system: each user gets a custom set of permissions, so they only access the screens they are allowed to
- Admin users with full access to every screen

**Security & Logging**
- Login screen
- Passwords are stored encrypted
- Login register that records every login to the system

## Project Structure

The project is built as separate classes, each with one clear job:

- Base classes: `clsPerson`, `clsBankClient`, `clsUser`
- One class for each screen (main menu, login, transactions, and so on) built on a shared `clsScreen`
- Helper classes: `clsInputValidate`, `clsString`, `clsDate`, `clsUtil`

## Tech Stack

- C++
- Object-Oriented Programming (classes, inheritance, encapsulation)
- File handling (data is stored in text files)
- Visual Studio

## How to Run

1. Download the project (Code → Download ZIP) and extract it.
2. Open the `BankSystem` folder, then open `Project1(BankSystem).vcxproj` in Visual Studio.
3. Press `Ctrl + F5` to build and run.

## Login

Use this admin account (full permissions) the first time you run the program:

- Username: `User1`
- Password: `1111`

You can then create other users from the Manage Users screen and give each one different permissions.

## Note

The data files included in this repository (`Users`, `Clients`, and others) contain sample data only, so you can try the system right away.

## What I Learned

- Designing a project as separate classes, each with one clear job
- Using inheritance to avoid repeating code
- Reusing my own libraries (string, date, input validation) inside a bigger project
- Reading and writing data with files
- Encrypting passwords before saving them
- Building a permissions system and validating user input
