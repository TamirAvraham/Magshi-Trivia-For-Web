#include "Room.h"
#include <stdexcept>
Room::Room(RoomData data, int roomId):_data(data),_roomId(roomId),_users()
{
	_users.push_back(_data.adminId);
}

void Room::start(int userId)
{
	if (_data.adminId==userId)
	{
		_data.isActive = true;
	}
	else {
		throw std::runtime_error("Error: User Is Not Admin And Therefore Cant Start The Game");
	}
}

void Room::removeUser(int userId)
{
	_users.erase(std::find(_users.begin(), _users.end(), userId));
}

void Room::joinRoom(int userId)
{
	_users.push_back(userId);
}

const RoomData& Room::getRoomData() const
{
	return _data;
}

const std::vector<int>& Room::getUsers() const
{
	return _users;
}
