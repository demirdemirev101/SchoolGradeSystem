#pragma once
#include <string>
#include <exception>

class Database;

class Person
{
protected:
	std::string name;
	int age;
	static int totalPersons;
public:
	Person(int age, std::string name);

	virtual ~Person();

	virtual void displayInfo() const = 0;

	virtual void saveToDB(Database& db) const = 0;
	
	static int getTotalPersons();
};
