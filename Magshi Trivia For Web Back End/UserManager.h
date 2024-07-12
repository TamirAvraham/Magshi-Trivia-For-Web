#pragma once
#include "User.h"
#include "Macros.h"
#include <map>
constexpr const char* USER_ID_COOKIE_NAME = "user-id";

class UserManager
{
public:
	const User& login(const std::string & username);
	const User& getUserById(int id)const;
private:
	std::map<int, User> _users{};
	int _id=0;



public: 
static UserManager& getInstance() {
	static UserManager instance; return instance;
} 
private: 
	UserManager() = default;
	~UserManager() = default; 
	UserManager(const UserManager&) = delete; 
	UserManager& operator=(const UserManager&) = delete; 
	UserManager(UserManager&&) = delete; 
	UserManager& operator=(UserManager&&) = delete;
};

