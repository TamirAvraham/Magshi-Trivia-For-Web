#pragma once
#include "HttpServer.h"
#include "UserManager.h"
#include "UserRoutes.h"

const User& getUserFromContext(const http::HttpContext& ctx) {
	const auto& userIdAsString = ctx.getCookieValue(USER_ID_COOKIE_NAME);
	auto userId = std::stoi(userIdAsString);
	return UserManager::getInstance().getUserById(userId);
}