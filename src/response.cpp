#include "response.hpp"

#include <cstdio>
#include <regex>
#include <string>
#include <unordered_map>

#include "constants.hpp"

using namespace coll::http;

Response::Response() = default;
Response::~Response() = default;

void Response::setBody(const std::vector<uint8_t>& data) { body = data; }

std::optional<std::string> Response::getBody() const
{
	if (body)
	{
		return std::string(reinterpret_cast<const char*>(body->data()), body->size());
	}

	return std::nullopt;
}

void Response::setVersion(const Version& version)
{
	this->version = version;
}

Version Response::getVersion() const
{
	return version;
}

void Response::setStatus(const StatusCode& status)
{
	this->status = status;
}

StatusCode Response::getStatus() const
{
	return status;
}

void Response::setHeader(const std::string& key, const std::string& value)
{
	headers[key] = value;
}

void Response::removeHeader(const std::string& key)
{
	headers.erase(key);
}

bool Response::hasHeader(const std::string& key) const
{
	return headers.contains(key);
}

std::optional<std::string> Response::getHeader(const std::string& key) const
{
	if (headers.contains(key))
	{
		return headers.at(key);
	}

	return std::nullopt;
}

std::unordered_map<std::string, std::optional<std::string>> Response::getHeaders() const
{
	return headers;
}

const std::string Response::determineHttpVersion(const std::vector<uint8_t>& response)
{
	const std::string data = std::string(reinterpret_cast<const char*>(response.data()), response.size());

	auto pos = data.find(CRLF);
	if (pos != std::string::npos)
	{
		const std::string line = data.substr(0, pos);

		const std::regex statusLineRegex(R"((HTTP\/\d+\.\d+) (\d{3,3}) (.+))");
		std::smatch match;
		if (std::regex_search(line, match, statusLineRegex))
		{
			return std::string(match[1]);
		}
	}

	return std::string();
}
