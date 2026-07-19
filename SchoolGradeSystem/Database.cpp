#define NOMINMAX
#include "Database.h"
#include "Classroom.h"
#include "Student.h"
#include "Teacher.h"
#include <iostream>

Database::Database()
{
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

    std::string connStr =
        "DRIVER={SQL Server};"
        "SERVER=DESKTOP-1RDEUMH;"
        "DATABASE=SchoolGradeSystem;"
        "Trusted_Connection=yes;"
        "TrustServerCertificate=yes;";

    SQLCHAR outStr[1024];
    SQLSMALLINT outLen;

    SQLRETURN ret = SQLDriverConnectA(
        dbc, NULL,
        (SQLCHAR*)connStr.c_str(), SQL_NTS,
        outStr, sizeof(outStr), &outLen,
        SQL_DRIVER_NOPROMPT
    );

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
        std::cout << "Connected to SQL Server!" << std::endl;
    else
        std::cout << "Connection FAILED!" << std::endl;
}

Database::~Database()
{
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);
    std::cout << "Database connection closed." << std::endl;
}

void Database::savePerson(const std::string& name, int age, const std::string& personType,
    double grade, const std::string& subject)
{
    std::string sql;

    if (personType == "Student")
    {
        sql = "INSERT INTO Persons (Name, Age, PersonType, Grade) VALUES ('"
            + name + "', " + std::to_string(age) + ", 'Student', " + std::to_string(grade) + ")";
    }
    else
    {
        sql = "INSERT INTO Persons (Name, Age, PersonType, Subject) VALUES ('"
            + name + "', " + std::to_string(age) + ", 'Teacher', '" + subject + "')";
    }

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    SQLRETURN ret = SQLExecDirectA(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
        std::cout << "Saved to database!" << std::endl;
    else
        std::cout << "Failed to save!" << std::endl;

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Database::updatePerson(const std::string& name, int newAge, double newGrade, const std::string& newSubject)
{
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    std::string sql;

    if (newGrade >= 0)
    {
        sql = "UPDATE Persons SET Age = " + std::to_string(newAge)
            + ", Grade = " + std::to_string(newGrade)
            + " WHERE Name = '" + name + "'";
    }
    else
    {
        sql = "UPDATE Persons SET Age = " + std::to_string(newAge)
            + ", Subject = '" + newSubject
            + "' WHERE Name = '" + name + "'";
    }

    SQLRETURN ret = SQLExecDirectA(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
        std::cout << "Updated successfully!" << std::endl;
    else
        std::cout << "Update failed!" << std::endl;

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Database::deletePerson(const std::string& name)
{
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    std::string sql = "DELETE FROM Persons WHERE Name = '" + name + "'";

    SQLRETURN ret = SQLExecDirectA(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
        std::cout << "Deleted successfully!" << std::endl;
    else
        std::cout << "Delete failed!" << std::endl;

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Database::loadAndDisplay()
{
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    std::string sql = "SELECT Id, Name, Age, PersonType, Grade, Subject FROM Persons";
    SQLExecDirectA(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);

    char name[100] = { 0 };
    char personType[20] = { 0 };
    char subject[100] = { 0 };
    int age, id;
    double grade;
    SQLLEN nameLen, ageLen, typeLen, gradeLen, subjectLen, idLen;

    std::cout << "\n--- Persons from Database ---" << std::endl;
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, &idLen);
        SQLGetData(stmt, 2, SQL_C_CHAR, name, sizeof(name), &nameLen);
        SQLGetData(stmt, 3, SQL_C_LONG, &age, 0, &ageLen);
        SQLGetData(stmt, 4, SQL_C_CHAR, personType, sizeof(personType), &typeLen);
        SQLGetData(stmt, 5, SQL_C_DOUBLE, &grade, 0, &gradeLen);
        SQLGetData(stmt, 6, SQL_C_CHAR, subject, sizeof(subject), &subjectLen);

        if (std::string(personType) == "Student")
            std::cout << "[ID: " << id << "] [Student] " << name
            << " | Age: " << age
            << " | Grade: " << grade << std::endl;
        else
            std::cout << "[ID: " << id << "] [Teacher] " << name
            << " | Age: " << age
            << " | Subject: " << subject << std::endl;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Database::loadIntoClassroom(Classroom<Person>& members)
{
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    std::string sql = "SELECT Name, Age, PersonType, Grade, Subject FROM Persons";
    SQLExecDirectA(stmt, (SQLCHAR*)sql.c_str(), SQL_NTS);

    char name[100] = { 0 };
    char personType[20] = { 0 };
    char subject[100] = { 0 };
    int age;
    double grade;
    SQLLEN nameLen, ageLen, typeLen, gradeLen, subjectLen;

    std::cout << "Loading from database..." << std::endl;
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        SQLGetData(stmt, 1, SQL_C_CHAR, name, sizeof(name), &nameLen);
        SQLGetData(stmt, 2, SQL_C_LONG, &age, 0, &ageLen);
        SQLGetData(stmt, 3, SQL_C_CHAR, personType, sizeof(personType), &typeLen);
        SQLGetData(stmt, 4, SQL_C_DOUBLE, &grade, 0, &gradeLen);
        SQLGetData(stmt, 5, SQL_C_CHAR, subject, sizeof(subject), &subjectLen);

        if (std::string(personType) == "Student")
            members.add(std::make_unique<Student>(age, std::string(name), grade));
        else
            members.add(std::make_unique<Teacher>(age, std::string(name), std::string(subject)));
    }

    std::cout << "Loaded " << members.count() << " persons from database." << std::endl;
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}