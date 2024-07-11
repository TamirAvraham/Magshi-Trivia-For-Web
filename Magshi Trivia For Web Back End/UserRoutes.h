#pragma once
#include "HttpServer.h"
#include "UserManager.h"
constexpr const char* USER_ID_COOKIE_NAME = "user-id";
void signupRoute(http::HttpContext& ctx);
void loginRoute(http::HttpContext& context);
void addUserCookieIdToContext(const User& user, http::HttpContext& ctx);