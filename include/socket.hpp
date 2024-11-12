#pragma once

#include <cstdint>
#include <expected>
#include <string>
#include <vector>

namespace coll::http
{
	class Socket
	{
	public:
		enum class error
		{
			FAILED_TO_GETADDRINFO,
			FAILED_TO_CREATE_SOCKET,
			FAILED_TO_CONNECT,
			NOT_CONNECTED,
			FAILED_TO_SEND,
			FAILED_TO_RECV
		};

		Socket();
		~Socket();

		static std::expected<Socket, error> create_socket(const std::string& host, const int port);

		std::expected<void, Socket::error> connect(const std::string& host, const int port);
		std::expected<void, Socket::error> close();
		std::expected<void, Socket::error> send(const std::vector<uint8_t>& request) const;
		std::expected<std::vector<uint8_t>, Socket::error> receive() const;

	private:
		inline constexpr static const int BUFFER_SIZE = 4096;

		int fd;
	};
};  // namespace coll::http
