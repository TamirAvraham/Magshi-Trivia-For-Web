#include "RoomsRoutes.h"
#include "helper.hpp"
void createRoomRoute(http::HttpContext& ctx)
{
	try
	{
		auto body = ctx.GetBodyAsJson();
		const auto& user = getUserFromContext(ctx);
		auto roomData = RoomData{
			.name = body["name"].string_value(),
			.numberOfQuestions = body["numberOfQuestion"].integer_value(),
			.timeToAnswer = body["timeToAnswer"].integer_value(),
			.adminId = user.getId(),
			.isActive = false,
		};

		RoomManager::getInstance().createRoom(roomData);
		http::HttpHeaders headers;
		ctx.sendEmpty(http::HttpStatus::Created, headers);
	}
	catch (const std::exception& e)
	{
		sendErrorJsonWithException(e, ctx);
	}
}

void getRoomsRoute(http::HttpContext& ctx)
{
	try
	{
		const auto& rooms = RoomManager::getInstance().getRooms();

		http::json::JsonObject json;
		std::vector<http::json::JsonValue> roomsJsonArray;
		roomsJsonArray.resize(rooms.size());
		std::transform(rooms.begin(), rooms.end(), roomsJsonArray.begin(), [](const std::pair<int, Room>& pair) {
			return JsonValue{ http::json::JsonType::Object,RoomDataMethods::seralizeRoomDataAsJson(pair.second.getRoomData()).ToString() };
			});
		json.insert({ {"rooms"},{roomsJsonArray} });

		ctx.sendJson(http::HttpStatus::OK, json);
	}
	catch (const std::exception& e)
	{
		sendErrorJsonWithException(e, ctx);
	}
}
