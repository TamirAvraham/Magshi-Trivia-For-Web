#pragma once
#include <string>
#include <vector>
struct RoomData {
	int numberOfQuestions;
	int timeToAnswer;
	int adminId;
	bool isActive;
	std::string name;
};
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

