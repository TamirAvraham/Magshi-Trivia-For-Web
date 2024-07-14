#pragma once
#include <string>
#include <memory>
enum class CurrentUserState :unsigned char
{
	Auth=1,
	RoomMember,
	RoomAdmin,
	InGame,
};
union UserStateData
{
	int roomId;
	int gameId;
};
class UserState
{
private:
	CurrentUserState _state;
	UserStateData _data;

public:

	UserState(CurrentUserState _state, UserStateData _data);
	UserState(CurrentUserState _state);
	CurrentUserState getUserSate()const;
	UserStateData getUserData()const;
};
class User
{
private:
	std::string _username;
	std::unique_ptr<UserState> _current_state;
	std::unique_ptr<UserState> _prev_state;
	int _id;

public:
	User(const std::string& _username, int _id)	: _username(_username), _id(_id),_current_state(nullptr),_prev_state(nullptr)
	{
	}
	User(const User&);
	void advanceToAuth();
	void joinRoom(int roomId);
	void createGame(int roomId);
	int getRoomId()const;
	int getGameId()const;

	bool operator==(const User& other) const
	{
		return _username == other._username && _id == other._id;
	}
	bool operator<(const User& other) const {
		return _username < other._username;
	}
	int getId()const {
		return _id;
	}
	const std::string& getUsername() const {
		return _username;
	}
};

