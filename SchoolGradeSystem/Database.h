#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <iostream>

template<typename T> class Classroom;
class Person;

class Database
{
private:
    SQLHENV env;
    SQLHDBC dbc;

public:
    Database();
    ~Database();

    void savePerson(const std::string& name, int age, const std::string& personType,
        double grade = -1, const std::string& subject = "");

    void updatePerson(const std::string& name, int newAge, double newGrade = -1,
        const std::string& newSubject = "");

    void deletePerson(const std::string& name);

    void loadAndDisplay();

    void loadIntoClassroom(Classroom<Person>& members);
};