#include "UserManager.h"
#include <algorithm>
#include <stdexcept>
const User& UserManager::login(const std::string & username)
{
    auto id = ++_id;
    _users.emplace(id,User(username, id));
    return this->getUserById(id);
}

const User& UserManager::getUserById(int id) const 
{
    const auto& iter = std::find_if(_users.begin(), _users.end(), [&id](const auto& user) {
        return user.first == id;
        });
    if (iter!=_users.end())
    {
        return iter->second;
    }
    else
    {
        throw std::runtime_error("User Not Found");
    }
}
UserManager UserManager::_instance;
UserManager UserManager::getInstance()
{
    return _instance;
}

