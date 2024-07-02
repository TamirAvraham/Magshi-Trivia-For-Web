#pragma once
#include <string>
#include "User.h"
class IDatabase {
public:
	virtual User login(const std::string& username,const std::string& password)=0;
	virtual User signup(const std::string& username, const std::string& password, const std::string& email)=0;
	virtual ~IDatabase()=default;
};