#pragma once
#include "RoomManager.h"
#include "HttpServer.h"
#include "Macros.h"
void getRoom(http::HttpContext& ctx);
void createRoomRoute(http::HttpContext& ctx);
void getRoomsRoute(http::HttpContext& ctx);
void joinRoomRoute(http::HttpContext& ctx);