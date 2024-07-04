#pragma once
#include "IDataBase.h"
#include "sqlite3.h"

class SqlliteDatabase : public IDatabase
{
	public:

		SqlliteDatabase();
		// Inherited via IDatabase
		virtual User login(const std::string& username, const std::string& password) override;
		virtual User signup(const std::string& username, const std::string& password, const std::string& email) override;
		virtual ~SqlliteDatabase();
	private:
		sqlite3* _db;

			
};