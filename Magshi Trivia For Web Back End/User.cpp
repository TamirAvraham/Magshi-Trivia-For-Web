#include "User.h"
#include <stdexcept>
User::User(const User& other):_username(other._username),_id(other._id),_current_state(_current_state!=nullptr?std::make_unique<UserState>((*other._current_state)):nullptr),_prev_state(_prev_state!=nullptr?std::make_unique<UserState>((*other._prev_state)):nullptr)
{

}
void User::advanceToAuth()
{
	_current_state = std::make_unique<UserState>(CurrentUserState::Auth);
}

void User::joinRoom(int roomId)
{
	if (_current_state->getUserSate() < CurrentUserState::RoomMember)
	{
		_prev_state = std::move(_current_state);
		_current_state = std::make_unique<UserState>(CurrentUserState::RoomMember, UserStateData{ .roomId = roomId });
	}
	else
	{
		throw std::runtime_error("Error: User Already In A Room");
	}
}

void User::createGame(int roomId)
{
	if (_current_state->getUserSate() < CurrentUserState::RoomMember)
	{
		_prev_state = std::move(_current_state);
		_current_state = std::make_unique<UserState>(CurrentUserState::RoomAdmin, UserStateData{ .roomId = roomId });
	}
	else
	{
		throw std::runtime_error("Error: User Already In A Room");
	}
}

int User::getRoomId() const
{
	return _current_state->getUserData().roomId;
}

int User::getGameId() const
{
	return _current_state->getUserData().gameId;
}

UserState::UserState(CurrentUserState _state, UserStateData _data) : _state(_state), _data(_data)
{
}

UserState::UserState(CurrentUserState _state):_state(),_data(UserStateData{.gameId=0})
{
}

CurrentUserState UserState::getUserSate() const
{
	return _state;
}

UserStateData UserState::getUserData() const
{
	return _data;
}

