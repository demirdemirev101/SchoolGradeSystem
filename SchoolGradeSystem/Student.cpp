#include "Student.h"
#include <iostream>

Student::Student(int age, std::string name, double grade) : Person(age, name), grade(grade)
{
	std::cout << "Student constructor called for " << name << std::endl;
}

Student::~Student()
{
	std::cout << "Student destructor called for " << name << std::endl;
}

void Student::setGrade(double newGrade)
{
	if (newGrade < 0.0 || newGrade > 6.0)
	{
		throw std::exception("Grade must be between 0.0 and 6.0 .");
	}
	grade = newGrade;
}

void Student::displayInfo() const
{
	std::cout << "Student Name: " << name << ", Age: " << age << ", Grade: " << grade << std::endl;
}

void Student::saveToDB(Database& db) const
{
	db.savePerson(name, age, "Student", grade);
}