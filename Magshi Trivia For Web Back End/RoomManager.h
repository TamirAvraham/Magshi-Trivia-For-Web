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
	void createRoom(RoomData _data);
	void joinRoom(int userId, int roomId);
	const RoomData& getRoomData(int roomId);
	const std::map<int,Room>& getRooms()const;



public: 
static RoomManager& getInstance() {
	static RoomManager instance; return instance;
} 
private: 
	RoomManager() = default;
	~RoomManager() = default; 
	RoomManager(const RoomManager&) = delete; 
	RoomManager& operator=(const RoomManager&) = delete; 
	RoomManager(RoomManager&&) = delete; 
	RoomManager& operator=(RoomManager&&) = delete;
};

