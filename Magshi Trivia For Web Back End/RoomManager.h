#pragma once
#include "Room.h"
#include "Macros.h"
#include <map>
class RoomManager
{

private:
	std::map<int, Room> _rooms;
	int _id;

public:
	RoomManager()=default;
	void createRoom(RoomData _data);
	void joinRoom(int userId, int roomId);
	const RoomData& getRoomData(int roomId);

	SINGLETON_GENERATOR(RoomManager)
};

