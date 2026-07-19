#define NOMINMAX        // ЗАДЪЛЖИТЕЛНО преди windows.h - изключва min/max macros
#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Classroom.h"
#include "Database.h"
#include <limits>
#include <iostream>

using namespace std;

void showMenu()
{
    cout << "\n===== Menu =====" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Add Teacher" << endl;
    cout << "3. Display All (memory)" << endl;
    cout << "4. Save All to Database" << endl;
    cout << "5. Load from Database(display only)" << endl;
	cout << "6. Update Person in Database" << endl;
    cout << "7. Delete Person from Database" << endl;
	cout << "8. Exit" << endl;
    cout << "Choose an option: ";
}

void addStudent(Classroom<Person>& members)
{
    int age;
    string name;
    double grade;
    cout << "Enter Student Name: ";
    cin >> name;
    cout << "Enter Student Age: ";
    cin >> age;
    cout << "Enter Student Grade: ";
    cin >> grade;
    try
    {
        members.add(make_unique<Student>(age, name, grade));
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}

void addTeacher(Classroom<Person>& members)
{
    int age;
    string name;
    string subject;
    cout << "Enter Teacher Name: ";
    cin >> name;
    cout << "Enter Teacher Age: ";
    cin >> age;
    cout << "Enter Teacher Subject: ";
    cin >> subject;
    try
    {
        members.add(make_unique<Teacher>(age, name, subject));
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}
void updatePerson(Database& db)
{
	std::string name;
	int newAge;
	double newGrade;
	std::string newSubject;
	cout << "Enter Person name to update: ";
	cin >> name;
	cout << "Enter new Age: ";
	cin >> newAge;
	cout << "Is this a Student or Teacher? (s/t): ";
	char type;
	cin >> type;
	if (type == 's')
	{
		cout << "Enter new grade: ";
		cin >> newGrade;
		db.updatePerson(name, newAge, newGrade);
	}
	else if (type == 't')
	{
		cout << "Enter new Subject: ";
		cin >> newSubject;
		db.updatePerson(name, newAge, -1, newSubject);
	}
	else
	{
		cout << "Invalid type." << endl;
	}
}

void deletePerson(Database& db)
{
	std::string name;
	cout << "Enter Person name to delete: ";
	cin >> name;
	db.deletePerson(name);
}

int main()
{
    Classroom<Person> classroom;
    Database db;

	cout << "Loading existing persons from database into memory..." << endl;
	db.loadIntoClassroom(classroom);

    int option{};

    while (option != 8)
    {
        showMenu();
        cin >> option;

        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number between 1 and 8." << endl;
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            continue;
        }

        switch (option)
        {
        case 1:
            addStudent(classroom);
            break;
        case 2:
            addTeacher(classroom);
            break;
        case 3:
            classroom.displayAll();
            break;
        case 4:
			classroom.forEach([&db](Person* p) { p->saveToDB(db); });
            break;
        case 5:
            db.loadAndDisplay();
            break;
        case 6:
            updatePerson(db);
            classroom.clear();
            db.loadIntoClassroom(classroom);
            break;
        case 7:
            deletePerson(db);
            classroom.clear();
            db.loadIntoClassroom(classroom);
            break;
		case 8:
			cout << "Exiting..." << endl;
			break;
        default:
            cout << "Invalid option." << endl;
        }
    }

    return 0;
}