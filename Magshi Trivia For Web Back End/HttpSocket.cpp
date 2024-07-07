#include "HttpSocket.h"
#include <string>
void http::HttpSocket::bindMsg(const HttpStatus status, const json::JsonObject& json, const std::unordered_map<std::string, std::string>& cookies, HttpHeaders headers = HttpHeaders())
{
    for (const auto& cookie:cookies)
    {
        std::string connectedKVPair = cookie.first + std::string("=") + cookie.second;
        headers.headers.insert(std::make_pair("Set-Cookie", connectedKVPair));
    }
    bindMsg(status, json, headers);
}
void http::HttpSocket::bindMsg(const HttpStatus status, const FileReader& htmlFile, const std::unordered_map<std::string, std::string>& cookies, HttpHeaders headers = HttpHeaders())
{
    for (const auto& cookie : cookies)
    {
        std::string connectedKVPair = cookie.first + std::string("=") + cookie.second;
        headers.headers.insert(std::make_pair("Set-Cookie", connectedKVPair));
    }
    bindMsg(status, htmlFile, headers);
}
void http::HttpSocket::bindMsg(const HttpStatus status, const json::JsonObject& json, const HttpHeaders headers)
{
    std::string msg = generateHttpResponceFromRequst(status, json, headers);
    write(msg);
}
std::string http::HttpSocket::generateHttpResponceFromRequst(HttpStatus status, json::JsonObject json, const HttpHeaders headers) const
{
    std::string ret = "HTTP/1.1 ",jsonAsString= json.ToString();
    ret += GetStatusLine(status);
    for(const auto& [headerName ,headerValue] : headers.headers)
    {
        ret += '\n';
        ret += headerName;
        ret += ": ";
        ret += headerValue;
    }
    std::cout << ret;
    if (ret.find("Content-Type")==std::string::npos)
        ret += "\nContent-Type: application/json";
    if (ret.find("Content-Length") == std::string::npos) {
        ret += "\nContent-Length: ";
        int length = jsonAsString.length();
        ret += std::to_string(length);
    }
    ret += "\n\n";
    ret += jsonAsString;
    return ret;
}
void http::HttpSocket::bindMsg(const HttpStatus status, const FileReader& htmlFile, const HttpHeaders headers)
{
    write(generateHttpResponceFromRequst(status, htmlFile, headers));
}
void http::HttpSocket::bindCss(const HttpStatus status, const std::string cssFileName)
{
    FileReader htmlFile(cssFileName);
    std::string ret = "HTTP/1.1 ";
    ret += GetStatusLine(status);
    std::cout << ret;
    ret += "\nContent-Type: text/css";
        ret += "\nContent-Length: ";
        int length = htmlFile.getFileAsString().length();
        ret += std::to_string(length);
    ret += "\n\n";
    ret += htmlFile.getFileAsString();
    write(ret);
}
void http::HttpSocket::bindJs(const HttpStatus status, const std::string jsFileName)
{
    FileReader htmlFile(jsFileName);
    std::string ret = "HTTP/1.1 ";
    ret += GetStatusLine(status);
    std::cout << ret;
    ret += "\nContent-Type: application/javascript";
    ret += "\nContent-Length: ";
    int length = htmlFile.getFileAsString().length();
    ret += std::to_string(length);
    ret += "\n\n";
    ret += htmlFile.getFileAsString();
    write(ret);
}
void http::HttpSocket::bindMsg(const HttpStatus status, const HttpHeaders& headers = HttpHeaders())
{
    std::string ret = "HTTP/1.1 ";
    ret += GetStatusLine(status);
    ret += "\r\n";
    for (const auto& [headerName, headerValue] : headers.headers)
    {
        ret += headerName;
        ret += ": ";
        ret += headerValue;
        ret += "\r\n";

    }
    ret+="\r\n";
    write(ret);
}
std::string http::HttpSocket::generateHttpResponceFromRequst(HttpStatus status, FileReader htmlFile, const HttpHeaders headers) const
{
    std::string ret = "HTTP/1.1 ";
    ret += GetStatusLine(status);
    for (auto [headerName, headerValue] : headers.headers)
    {
        ret += '\n';
        ret += headerName;
        ret += ": ";
        ret += headerValue;
    }
    std::cout << ret;
    if (ret.find("Content-Type") == std::string::npos)
        ret += "\nContent-Type: text/html";
    if (ret.find("Content-Length") == std::string::npos) {
        ret += "\nContent-Length: ";
        int length = htmlFile.getFileAsString().length();
        ret += std::to_string(length);
    }
    ret += "\n\n";
    ret += htmlFile.getFileAsString();
    return ret;
}