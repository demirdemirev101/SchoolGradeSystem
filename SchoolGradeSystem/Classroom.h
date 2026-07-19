#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <functional>

template <typename T>
class Classroom
{
private:
    std::vector<std::unique_ptr<T>> members;

public:
    void add(std::unique_ptr<T> person)
    {
        members.push_back(std::move(person));
    }

    void forEach(std::function<void(T*)> callback) const
    {
        for (const auto& member : members)
        {
            callback(member.get());
        }
    }
    void displayAll() const
    {
        for (const auto& person : members)
        {
            person->displayInfo();
        }
    }

    int count() const
    {
        return members.size();
    }

	void clear()
	{
		members.clear();
	}
};