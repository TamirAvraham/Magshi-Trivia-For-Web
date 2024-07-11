#include "RoomManager.h"



void RoomManager::createRoom(RoomData _data)
{
	_id += 1;
	_rooms.insert(std::make_pair(_id, Room(_data, _id)));
}

void RoomManager::joinRoom(int userId, int roomId)
{
	_rooms.at(roomId).joinRoom(userId);
}

const RoomData& RoomManager::getRoomData(int roomId)
{
	_rooms.at(roomId).getRoomData();
}
