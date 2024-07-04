#include "IDataBase.h"
#include "SqlliteDatabase.h"
std::unique_ptr<IDatabase> IDatabase::_instance = nullptr;
std::unique_ptr<IDatabase>& IDatabase::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = std::make_unique<SqlliteDatabase>();
	}
	return _instance;
}
