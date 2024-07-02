#pragma once
#include "HttpServer.h"
#include "UserManager.h"
void signupRoute(http::HttpContext& ctx);
void loginRoute(http::HttpContext& context);