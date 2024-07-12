#include "TcpServer.h"
#include "JsonObject.h"
#include "ThreadPool.h"
#include "HttpSocket.h"
#include "HttpServer.h"
#include "HtmlFileReader.h"
#include "Dog.h"
#include "CreateDogHandlerFunc.h"
#include <iostream>
#include "UserRoutes.h"
#include "RoomsRoutes.h"
/*
TODO:
db:
create dog model DONE
api:
create api route for adding a dog 
create api route to get all dogs as json
create api route to get a spesific dog deatails by id

front:
create the website

lib:

bugs:


*/
int main() {
	http::HttpRoute createDogRoute({ "/api/create" }, { CreateDogHandlerFunc });
	http::HttpRoute getDogRoute({ "/api/get_dog/:id" }, { getDogHandlerFunc });
	http::HttpRoute getAllDogsRoute({ "/api/get_all_dogs" }, { getAllDogsHandlerFunc });
	http::HttpRoute adpotDogRoute({ "/api/adopt_dog/:id" }, { adoptDog });
	http::HttpRoute loginHttpRoute({ "/api/login" }, { loginRoute });
	http::HttpRoute signupHttpRoute({ "/api/signup" }, { signupRoute });
	http::HttpRoute createRoomHttpRoute({ "/api/create_room" }, { createRoomRoute });
	http::HttpRoute getRoomsHttpRoute({ "/api/rooms" }, { getRoomsRoute  });


	http::HtmlFileReader homePageReader("home_page.htm");
	http::HtmlFileReader addDogReader("add_dog.html");
	http::HtmlFileReader dogDeatsReader("dog_details.html");
	http::HtmlFileReader loginPageReader("user_form.html");

	loginPageReader.optimizeFileForSending();
	homePageReader.optimizeFileForSending();
	addDogReader.optimizeFileForSending();
	dogDeatsReader.optimizeFileForSending();

	http::HttpServer server(8080,"127.0.0.1");

	server.HandleRoute(http::HttpGET, getDogRoute);
	server.HandleRoute(http::HttpGET, getAllDogsRoute);
	server.HandleRoute(http::HttpGET, getRoomsHttpRoute);

	server.HandleRoute(http::HttpDELETE, adpotDogRoute);

	server.HandleRoute(http::HttpPOST, loginHttpRoute);
	server.HandleRoute(http::HttpPOST, signupHttpRoute);
	server.HandleRoute(http::HttpPOST, createDogRoute);
	server.HandleRoute(http::HttpPOST, createRoomHttpRoute);

	server.ServeHtmlPage("/", homePageReader);
	server.ServeHtmlPage("/dog_details/:id", dogDeatsReader);
	server.ServeHtmlPage("/add_dog", addDogReader);
	server.ServeHtmlPage("/login", loginPageReader);
	server.enableCORSMiddleware();
	server.serve();


	return 0;
}
