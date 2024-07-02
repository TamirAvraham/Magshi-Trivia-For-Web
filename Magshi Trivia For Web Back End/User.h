#pragma once
#include <string>
class User
{
private:
	std::string _username;
	int _id;

public:
	User(const std::string& _username, int _id)	: _username(_username), _id(_id)
	{
	}

	bool operator==(const User& other) const
	{
		return _username == other._username && _id == other._id;
	}
	bool operator<(const User& other) const {
		return _username < other._username;
	}
	int getId()const {
		return _id;
	}
	const std::string& getUsername() const {
		return _username;
	}
};

