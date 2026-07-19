#pragma once
#include "Person.h"
#include "Database.h"

class Teacher : public Person
{
private:
	std::string subject;
public:
	Teacher(int age, std::string name, std::string subject);
	~Teacher() override;

	void displayInfo() const override;

	void saveToDB(Database& db) const override;	
};