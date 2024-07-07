#pragma once
#include "TcpServer.h"
#include "HttpStatus.h"
#include "HttpParser.h"
#include "FileReader.h"
#include "JsonObject.h"


 
namespace http{

	struct HttpHeaders {
		std::multimap<std::string, std::string> headers;
	public:
		std::string GetHeaderValue(const std::string& key) const noexcept {
			auto header = headers.find(key);
			if (header != headers.end()) {
				return header->second;
			}
			return "";
		}
		HttpHeaders(){};
	};

	class HttpSocket :public tcp::simpleSocket
	{
	public:
		inline HttpSocket(SOCKET socket) :tcp::simpleSocket(socket){};
		void bindMsg(const HttpStatus status,const json::JsonObject& json,const std::unordered_map<std::string,std::string>& cookies, HttpHeaders headers);
		void bindMsg(const HttpStatus status,const FileReader& htmlFile,const std::unordered_map<std::string, std::string>& cookies, HttpHeaders headers);
		void bindMsg(const HttpStatus status, const json::JsonObject& json, const HttpHeaders headers = HttpHeaders());
		void bindMsg(const HttpStatus status, const FileReader& htmlFile, const HttpHeaders headers = HttpHeaders());
		void bindCss(const HttpStatus status, const std::string cssFileName);
		void bindJs(const HttpStatus status, const std::string jsFileName);
		void bindMsg(const HttpStatus status, const HttpHeaders& headers);

	private:
		std::string generateHttpResponceFromRequst(HttpStatus status, json::JsonObject json, const HttpHeaders headers)const;
		std::string generateHttpResponceFromRequst(HttpStatus status, FileReader htmlFile, const HttpHeaders headers)const;
	};
}

