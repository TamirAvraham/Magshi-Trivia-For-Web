#pragma once
#include "User.h"
#include <map>
class UserManager
{
public:
	const User& login(const std::string & username);
	const User& getUserById(int id)const;
	static UserManager getInstance();
private:
	static UserManager _instance;
	UserManager() = default;
	std::map<int, User> _users;
	int _id;
};

