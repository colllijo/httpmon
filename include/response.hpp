#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "http.hpp"

namespace coll::http
{

	class Response
	{
	public:
		Response();
		~Response();

		void setBody(const std::vector<uint8_t>& data);
		std::optional<std::string> getBody() const;

		void setVersion(const Version& version);
		Version getVersion() const;

		void setStatus(const StatusCode& status);
		StatusCode getStatus() const;

		void setHeader(const std::string& key, const std::string& value);
		void removeHeader(const std::string& key);
		bool hasHeader(const std::string& key) const;
		std::optional<std::string> getHeader(const std::string& key) const;
		std::unordered_map<std::string, std::optional<std::string>> getHeaders() const;
		

	private:
		Version version;
		StatusCode status;

		std::unordered_map<std::string, std::optional<std::string>> headers;
		std::optional<std::vector<uint8_t>> body;

		const std::string determineHttpVersion(const std::vector<uint8_t>& response);
	};

};  // namespace coll::http
