#include "socket.hpp"

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdint>
#include <expected>
#include <vector>


using namespace coll::http;

Socket::Socket(): fd(-1) {};
Socket::~Socket() = default;

std::expected<Socket, Socket::error> Socket::create_socket(const std::string& host, const int port)
{
	Socket s;
	const auto result = s.connect(host, port);
	if (!result)
	{
		return std::unexpected(result.error());
	}
	return s;
}

std::expected<void, Socket::error> Socket::connect(const std::string& host, const int port)
{
	struct addrinfo hints{}, *res;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res) != 0)
	{ return std::unexpected(error::FAILED_TO_GETADDRINFO); }

	fd = ::socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (fd == -1)
	{
		freeaddrinfo(res);
		return std::unexpected(error::FAILED_TO_CREATE_SOCKET);
	}

	if (::connect(fd, res->ai_addr, res->ai_addrlen) == -1)
	{
		::close(fd);
		freeaddrinfo(res);
		return std::unexpected(error::FAILED_TO_CONNECT);
	}

	freeaddrinfo(res);
	return {};
}

std::expected<void, Socket::error> Socket::close()
{
	if (fd == -1) { return std::unexpected(error::NOT_CONNECTED); }

	::close(fd);
	fd = -1;

	return {};
}

std::expected<void, Socket::error> Socket::send(const std::vector<uint8_t>& request) const
{
	if (fd == -1) { return std::unexpected(error::NOT_CONNECTED); }

	if (::send(fd, request.data(), request.size(), 0) == -1)
	{
		::close(fd);
		return std::unexpected(error::FAILED_TO_SEND);
	}

	return {};
}

std::expected<std::vector<uint8_t>, Socket::error> Socket::receive() const
{
	if (fd == -1) { return std::unexpected(error::NOT_CONNECTED); }

	std::vector<uint8_t> buffer(BUFFER_SIZE);
	std::vector<uint8_t> response;

	size_t bytes_received;
	while ((bytes_received = ::recv(fd, buffer.data(), BUFFER_SIZE, 0)) > 0)
	{
		response.insert(response.end(), buffer.begin(), buffer.begin() + bytes_received);
	}

	if (static_cast<int>(bytes_received) == -1)
	{
		::close(fd);
		return std::unexpected(error::FAILED_TO_RECV);
	}

	return response;
}
