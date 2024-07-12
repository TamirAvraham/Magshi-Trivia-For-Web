#pragma once
#include <string>
#include <vector>
#include "JsonObject.h"
struct RoomData {
	std::string name;
	int numberOfQuestions;
	int timeToAnswer;
	int adminId;
	bool isActive;
};
namespace RoomDataMethods {
	http::json::JsonObject seralizeRoomDataAsJson(const RoomData& roomData);
}
class Room
{
private:
	std::vector<int> _users;
	RoomData _data;
	int _roomId;
public:
	Room(RoomData data,int roomId);
	void start(int userId);
	void removeUser(int userId);
	void joinRoom(int userId);
	const RoomData& getRoomData()const;
	const std::vector<int>& getUsers()const;
};

