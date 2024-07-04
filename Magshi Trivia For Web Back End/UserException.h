#pragma once
#include <exception>

class UserException : public std::exception
{
	private:
		const char* message;

	public:
		UserException(const char* msg): message(msg)
		{

		}

		const char* what() const
		{
			return message;
		}

};