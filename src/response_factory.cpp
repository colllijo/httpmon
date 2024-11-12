#include "response_factory.hpp"

#include <cstdio>
#include <string>
#include <regex>

#include "constants.hpp"
#include "http.hpp"

using namespace coll::http;

Response ResponseFactory::createResponse(const std::vector<uint8_t> &data) {
	Version version = determineResponseVersion(data);

	switch (version) {
		case Version::HTTP_0_9:
			printf("Response Factory: HTTP/0.9\n");
			return createHTTP_0_9_Response(data);
		case Version::HTTP_1_0:
			printf("Response Factory: HTTP/1.0\n");
			return createHTTP_1_0_Response(data);
		default:
			return Response();
	}
}

Version ResponseFactory::determineResponseVersion(const std::vector<uint8_t>& data) {
	const std::string response = std::string(reinterpret_cast<const char*>(data.data()), data.size());

	auto pos = response.find(CRLF);
	if (pos != std::string::npos)
	{
		const std::string line = response.substr(0, pos);

		const std::regex statusLineRegex(R"((HTTP\/\d+\.\d+) (\d{3,3}) (.+))");
		std::smatch match;
		if (std::regex_search(line, match, statusLineRegex))
		{
			const auto version = Version::fromString(match[1]);
			if (version.has_value()) { return version.value(); }
		}
	}

	return Version();
}

Response ResponseFactory::createHTTP_0_9_Response(const std::vector<uint8_t>& data) {
	Response res;

	res.setBody(data);

	return res;
}

Response ResponseFactory::createHTTP_1_0_Response(const std::vector<uint8_t>& data) {
	std::string response = std::string(reinterpret_cast<const char*>(data.data()), data.size());

	Response res;

	auto pos = response.find(CRLF);
	if (pos != std::string::npos)
	{
		const std::string statusLine = response.substr(0, pos);
		response.erase(0, pos + CRLF.size());

		const std::regex statusLineRegex(R"((HTTP\/\d+\.\d+) (\d{3,3}) (.+))");
		std::smatch match;
		if (std::regex_search(statusLine, match, statusLineRegex))
		{
			res.setVersion(Version::HTTP_1_0);

			auto status = StatusCode::fromCode(match[2]);
			if (status.has_value())
			{
				if (status.value() == StatusCode::OTHER)
				{
					status.value().setCode(match[2]);
					status.value().setReason(match[3]);
				}

				res.setStatus(status.value());
			}
		}
	}

	while ((pos = response.find(CRLF)) != std::string::npos)
	{
		const std::string header = response.substr(0, pos);
		response.erase(0, pos + CRLF.size());

		if (header.empty()) { break; }

		const std::regex headerRegex(R"((.+): ?(.+))");
		std::smatch match;
		if (std::regex_search(header, match, headerRegex))
		{
			res.setHeader(match[1], match[2]);
		}
	}

	if (!response.empty()) { res.setBody(std::vector<uint8_t>(response.begin(), response.end())); }

	return res;
}
