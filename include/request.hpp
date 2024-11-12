#pragma once

#include <cstdint>
#include <cstring>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "http.hpp"
#include "response.hpp"

namespace coll::http
{

	class Request
	{
	public:
		Request();
		~Request();

		Response execute() const;

		void set_host(const std::string &host);
		void set_path(const std::string &path);
		void set_port(const int port);
		void set_method(const Method &method);
		void set_header(const std::string &key, const std::string &value);

		// Request-Header = Authorization            ; Section 10.2
		//                | From                     ; Section 10.8
		//                | If-Modified-Since        ; Section 10.9
		//                | Referer                  ; Section 10.13
		//                | User-Agent

	private:
		std::string host;
		std::string path;
		int port;

		std::unordered_map<std::string, std::optional<std::string>> headers;
		std::optional<std::vector<uint8_t>> body;

		Method method;
		const Version httpVersion = Version::HTTP_1_0;

		std::vector<uint8_t> buildRequest() const;
	};

};  // namespace coll::http
