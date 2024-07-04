#include "UserRoutes.h"

void signupRoute(http::HttpContext& ctx)
{
	try
	{
		auto body = ctx.GetBodyAsJson();
		const auto& username = body["username"].string_value();
		const auto& password = body["password"].string_value();
		auto user = UserManager::getInstance().login(username);
		http::json::JsonObject responce;
		responce.insert("id", user.getId());
		auto idAsString = std::to_string(user.getId());
		ctx.addCookie("user-id", idAsString);
		ctx.sendJson(http::HttpStatus::OK, responce);
	}
	catch (const std::exception& e)
	{
		auto json = http::json::JsonObject::JsonObject();
		json.insert("error", e.what());
		ctx.sendJson(http::HttpStatus::BadRequest, json);
		
	}
}

void loginRoute(http::HttpContext& context)
{
	return signupRoute(context);
}
