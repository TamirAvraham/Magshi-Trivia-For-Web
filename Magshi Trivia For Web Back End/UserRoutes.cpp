#include "UserRoutes.h"
#include "IDataBase.h"
void signupRoute(http::HttpContext& ctx)
{
	try
	{
		auto body = ctx.GetBodyAsJson();

		const auto& username = body["username"].string_value();
		const auto& password = body["password"].string_value();
		const auto& email = body["email"].string_value();

		auto user = IDatabase::getInstance()->signup(username,password,email);
		http::json::JsonObject responce;

		responce.insert("id", user.getId());
		addUserCookieIdToContext(user, ctx);
		ctx.sendJson(http::HttpStatus::OK, responce);
	}
	catch (const std::exception& e)
	{
		auto json = http::json::JsonObject::JsonObject();
		json.insert("error", e.what());
		ctx.sendJson(http::HttpStatus::BadRequest, json);
		
	}
}

void loginRoute(http::HttpContext& ctx)
{
	try
	{
		auto body = ctx.GetBodyAsJson();

		const auto& username = body["username"].string_value();
		const auto& password = body["password"].string_value();

		auto user = IDatabase::getInstance()->login(username, password);

		http::json::JsonObject responce;
		responce.insert("id", user.getId());
		addUserCookieIdToContext(user, ctx);
		ctx.sendJson(http::HttpStatus::OK, responce);
	}
	catch (const std::exception& e)
	{
		auto json = http::json::JsonObject::JsonObject();
		json.insert("error", e.what());
		ctx.sendJson(http::HttpStatus::BadRequest, json);
	}
}

void addUserCookieIdToContext(const User& user, http::HttpContext& ctx)
{
	auto idAsString = std::to_string(user.getId());
	ctx.addCookie(USER_ID_COOKIE_NAME, idAsString);
}
