#include "request.hpp"

#include "constants.hpp"
#include "socket.hpp"
#include "response_factory.hpp"

using namespace coll::http;

Request::Request() = default;
Request::~Request() = default;

Response Request::execute() const
{
	const auto request = buildRequest();
	auto socket = Socket::create_socket(host, port);

	if (!socket)
	{
		return Response();
	}
	socket = socket.value();

	const auto send = socket->send(request);
	if (!send)
	{
		return Response();
	}

	auto response = socket.value().receive();
	if (!response)
	{
		return Response();
	}
	response = response.value();

	return ResponseFactory::createResponse(*response);
}

std::vector<uint8_t> Request::buildRequest() const
{
	std::string request;

	// Request-Line
	request.append(method.toString());
	request.append(SP);
	request.append(path);
	request.append(SP);
	request.append(httpVersion.toString());
	request.append(CRLF);

	// Headers
	for (const auto& [key, value] : headers)
	{
		request.append(key);
		request.append(": ");
		if (value)
		{
			request.append(value.value());
		}
		request.append(CRLF);
	}

	request.append(CRLF);

	// Body
	if (body)
	{
		const auto& data = body.value();
		request.append(reinterpret_cast<const char*>(data.data()), data.size());
	}

	printf("Request: \n%s\n\n", request.c_str());
	return std::vector<uint8_t>(request.begin(), request.end());
}

void Request::set_host(const std::string& host) { this->host = host; }

void Request::set_path(const std::string& path) { this->path = path; }

void Request::set_port(const int port) { this->port = port; }

void Request::set_method(const Method &method) { this->method = method; }

void Request::set_header(const std::string& key, const std::string& value) { headers[key] = value; }
