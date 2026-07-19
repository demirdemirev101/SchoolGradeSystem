#include "Person.h"
#include <iostream>

int Person::totalPersons = 0;

Person::Person(int age, std::string name) : age(age), name(name)
{
	if (age < 0 || age>120)
	{
		throw std::exception("Age cannot be negative or above 120.");
	}
	totalPersons++;
}

Person::~Person()
{
	std::cout << "Person destructor called for " << name << std::endl;
}

int Person::getTotalPersons()
{
	return totalPersons;
}