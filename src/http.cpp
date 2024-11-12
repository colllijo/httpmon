#include "http.hpp"

#include <expected>
#include <string>
#include <unordered_map>

namespace coll::http
{
	std::string Method::toString() const
	{
		switch (value)
		{
			case Value::GET:
				return "GET";
			case Value::HEAD:
				return "HEAD";
			case Value::POST:
				return "POST";
			case Value::PUT:
				return "PUT";
			case Value::DELETE:
				return "DELETE";
		}
	}

	std::expected<Method, std::monostate> Method::fromString(const std::string& method)
	{
		const std::unordered_map<std::string, Method> HTTP_METHODS = {{"GET", Method::GET},
		                                                              {"HEAD", Method::HEAD},
		                                                              {"POST", Method::POST},
		                                                              {"PUT", Method::PUT},
		                                                              {"DELETE", Method::DELETE}};

		if (const auto it = HTTP_METHODS.find(method); it != HTTP_METHODS.end())
		{
			return it->second;
		}
		return std::unexpected(std::monostate{});
	}

	StatusCode::StatusCode() = default;
	StatusCode::StatusCode(Value status) : value(status), code(_getCode()), reason(_getReason()) {}
	StatusCode::StatusCode(int code, const std::string& reason) : value(OTHER), code(code), reason(reason) {}

	void StatusCode::setCode(const std::string& code) { this->code = std::stoi(code); }

	int StatusCode::getCode() const { return code; }

	int StatusCode::_getCode() const
	{
		switch (value)
		{
			case Value::OK:
				return 200;
			case Value::CREATED:
				return 201;
			case Value::ACCEPTED:
				return 202;
			case Value::NO_CONTENT:
				return 204;
			case Value::MOVED_PERMANENTLY:
				return 301;
			case Value::MOVED_TEMPORARILY:
				return 302;
			case Value::NOT_MODIFIED:
				return 304;
			case Value::BAD_REQUEST:
				return 400;
			case Value::UNAUTHORIZED:
				return 401;
			case Value::FORBIDDEN:
				return 403;
			case Value::NOT_FOUND:
				return 404;
			case Value::INTERNAL_SERVER_ERROR:
				return 500;
			case Value::NOT_IMPLEMENTED:
				return 501;
			case Value::BAD_GATEWAY:
				return 502;
			case Value::SERVICE_UNAVAILABLE:
				return 503;
			case Value::OTHER:
				return code;
		}
	}

	void StatusCode::setReason(const std::string& reason) { this->reason = reason; }

	std::string StatusCode::getReason() const { return reason; }

	std::string StatusCode::_getReason() const
	{
		switch (value)
		{
			case Value::OK:
				return "Ok";
			case Value::CREATED:
				return "Created";
			case Value::ACCEPTED:
				return "Accepted";
			case Value::NO_CONTENT:
				return "No Content";
			case Value::MOVED_PERMANENTLY:
				return "Moved Permanently";
			case Value::MOVED_TEMPORARILY:
				return "Moved Temporarily";
			case Value::NOT_MODIFIED:
				return "Not Modified";
			case Value::BAD_REQUEST:
				return "Bad Request";
			case Value::UNAUTHORIZED:
				return "Unauthorized";
			case Value::FORBIDDEN:
				return "Forbidden";
			case Value::NOT_FOUND:
				return "Not Found";
			case Value::INTERNAL_SERVER_ERROR:
				return "Internal Server Error";
			case Value::NOT_IMPLEMENTED:
				return "Not Implemented";
			case Value::BAD_GATEWAY:
				return "Bad Gateway";
			case Value::SERVICE_UNAVAILABLE:
				return "Service Unavailable";
			case Value::OTHER:
				return reason;
		}
	}

	std::expected<StatusCode, std::monostate> StatusCode::fromCode(const std::string& code)
	{
		int value;

		try
		{
			value = std::stoi(code);
		}
		catch (...)
		{
			return std::unexpected(std::monostate{});
		}

		switch (value)
		{
			case 200:
				return StatusCode(StatusCode::OK);
			case 201:
				return StatusCode(StatusCode::CREATED);
			case 202:
				return StatusCode(StatusCode::ACCEPTED);
			case 204:
				return StatusCode(StatusCode::NO_CONTENT);
			case 301:
				return StatusCode(StatusCode::MOVED_PERMANENTLY);
			case 302:
				return StatusCode(StatusCode::MOVED_TEMPORARILY);
			case 304:
				return StatusCode(StatusCode::NOT_MODIFIED);
			case 400:
				return StatusCode(StatusCode::BAD_REQUEST);
			case 401:
				return StatusCode(StatusCode::UNAUTHORIZED);
			case 403:
				return StatusCode(StatusCode::FORBIDDEN);
			case 404:
				return StatusCode(StatusCode::NOT_FOUND);
			case 500:
				return StatusCode(StatusCode::INTERNAL_SERVER_ERROR);
			case 501:
				return StatusCode(StatusCode::NOT_IMPLEMENTED);
			case 502:
				return StatusCode(StatusCode::BAD_GATEWAY);
			case 503:
				return StatusCode(StatusCode::SERVICE_UNAVAILABLE);
			default:
				return StatusCode(StatusCode::OTHER);
		}
	}

	std::string Version::toString() const
	{
		switch (value)
		{
			case Value::HTTP_0_9:
				return "HTTP/0.9";
			case Value::HTTP_1_0:
				return "HTTP/1.0";
		}
	}

	std::expected<Version, std::monostate> Version::fromString(const std::string& version)
	{
		const std::unordered_map<std::string, Version> HTTP_VERSIONS = {{"HTTP/0.9", Version::HTTP_0_9},
		                                                                {"HTTP/1.0", Version::HTTP_1_0}};

		if (const auto it = HTTP_VERSIONS.find(version); it != HTTP_VERSIONS.end())
		{
			return it->second;
		}
		return std::unexpected(std::monostate{});
	}
};  // namespace coll::http
