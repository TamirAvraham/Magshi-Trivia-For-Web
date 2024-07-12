#pragma once
#include "HttpServer.h"
#include "UserManager.h"


const User& getUserFromContext(const http::HttpContext& ctx) {
	const auto& userIdAsString = ctx.getCookieValue(USER_ID_COOKIE_NAME);
	auto userId = std::stoi(userIdAsString);
	return UserManager::getInstance().getUserById(userId);
}
void sendErrorJsonWithException(const std::exception& error, http::HttpContext& ctx) {
	auto json = http::json::JsonObject::JsonObject();
	json.insert("error", error.what());
	ctx.sendJson(http::HttpStatus::BadRequest, json);
}
http::json::JsonValue seralizeVectorToJsonValue(const std::vector<std::string>& vec) {
	std::stringstream ss;
	ss << "[";
	for (size_t i = 0; i < vec.size(); i++)
	{
		ss << vec[i] << (i != vec.size()) ? "," : "]";
		
	}
	auto ret = JsonValue{http::json::JsonType::Array,ss.str()};
	return ret;
}
http::json::JsonValue seralizeVectorToJsonValue(const std::vector<int>& vec) {
	std::vector<std::string> middleVector;
	std::transform(vec.begin(), vec.end(), middleVector.begin(), [](int value) {return std::to_string(value); });
	return seralizeVectorToJsonValue(middleVector);
}