#pragma once
#include "Person.h"
#include "Database.h"

class Student : public Person
{
private:
	double grade;
public:
	Student(int age, std::string name, double grade);
	~Student() override;
	
	void setGrade(double newGrade);

	void displayInfo() const override;

	void saveToDB(Database& db) const override;
};