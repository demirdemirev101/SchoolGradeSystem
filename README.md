\# SchoolGradeSystem



A C++ console application for managing students and teachers, with full CRUD operations connected to SQL Server.



\## Concepts Demonstrated



\- \*\*Abstract Classes / Pure Virtual\*\* – `Person` cannot be instantiated directly

\- \*\*Inheritance\*\* – `Student` and `Teacher` extend abstract `Person`

\- \*\*Polymorphism\*\* – `Classroom<Person>` stores mixed types, methods dispatch virtually

\- \*\*Virtual Destructor\*\* – correct cleanup order (derived → base)

\- \*\*Static Members\*\* – `Person::totalPersons` counts all instances globally

\- \*\*Templates\*\* – `Classroom<T>` is a generic container working with any type

\- \*\*Smart Pointers\*\* – `unique\_ptr<T>` manages heap memory automatically (no manual delete)

\- \*\*Forward Declarations\*\* – avoid circular includes between `Person.h` and `Database.h`

\- \*\*References\*\* – `Classroom` and `Database` passed by reference to avoid copying



\## Database



\- \*\*SQL Server 2025\*\* via \*\*ODBC\*\* connection

\- Full \*\*CRUD\*\* operations (Create, Read, Update, Delete)

\- Auto-load from database on startup



\## Project Structure



```

SchoolGradeSystem/

├── Person.h / Person.cpp         # Abstract base class

├── Student.h / Student.cpp       # Derived class (grade)

├── Teacher.h / Teacher.cpp       # Derived class (subject)

├── Classroom.h                   # Generic template container

├── Database.h / Database.cpp     # SQL Server ODBC connection + CRUD

└── SchoolGradeSystem.cpp         # Main entry point with interactive menu

```



\## Features



\- Add Students and Teachers

\- Display all persons (from memory)

\- Save all to SQL Server database

\- Load from database (display only)

\- Update person by name

\- Delete person by name

\- Auto-sync memory after update/delete



\## Requirements



\- Visual Studio 2022+

\- SQL Server 2016+ with SSMS

\- ODBC Driver for SQL Server



\## How to Run



1\. Create database in SSMS:

```sql

CREATE DATABASE SchoolGradeSystem;

USE SchoolGradeSystem;

CREATE TABLE Persons (

&#x20;   Id INT PRIMARY KEY IDENTITY,

&#x20;   Name NVARCHAR(100) NOT NULL,

&#x20;   Age INT NOT NULL,

&#x20;   PersonType NVARCHAR(20) NOT NULL,

&#x20;   Grade FLOAT NULL,

&#x20;   Subject NVARCHAR(100) NULL

);

```

2\. Update connection string in `Database.cpp` with your server name

3\. Open `SchoolGradeSystem.slnx` in Visual Studio

4\. Build: `Ctrl + Shift + B`

5\. Run: `Ctrl + F5`

