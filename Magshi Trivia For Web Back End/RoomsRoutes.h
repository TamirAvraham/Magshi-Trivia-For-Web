#pragma once
#include "RoomManager.h"
#include "HttpServer.h"

void createRoomRoute(http::HttpContext& ctx);
void getRoomsRoute(http::HttpContext& ctx);