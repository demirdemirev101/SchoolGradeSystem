#include "Teacher.h"
#include <iostream>

Teacher::Teacher(int age, std::string name, std::string subject) : Person(age, name), subject(subject)
{
	std::cout << "Teacher constructor called for " << name << std::endl;
}

Teacher::~Teacher()
{
	std::cout << "Teacher destructor called for " << name << std::endl;
}

void Teacher::displayInfo() const
{
	std::cout << "Teacher Name: " << name << ", Age: " << age << ", Subject: " << subject << std::endl;
}

void Teacher::saveToDB(Database& db) const
{
	db.savePerson(name, age, "Teacher", -1, subject);
}