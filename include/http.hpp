#pragma once

#include <expected>
#include <string>
#include <variant>

namespace coll::http
{
	class Method
	{
	public:
		enum Value
		{
			GET,
			HEAD,
			POST,
			PUT,
			DELETE
		};

		Method() = default;
		constexpr Method(Value method) : value(method) {}

		explicit operator bool() const = delete;
		constexpr operator Value() const { return value; }
		constexpr bool operator==(Method other) const { return value == other.value; }
		constexpr bool operator!=(Method other) const { return value != other.value; }

		std::string toString() const;
		static std::expected<Method, std::monostate> fromString(const std::string& method);

	private:
		Value value;
	};

	class StatusCode
	{
	public:
		enum Value
		{
			OK,
			CREATED,
			ACCEPTED,
			NO_CONTENT,
			MOVED_PERMANENTLY,
			MOVED_TEMPORARILY,
			NOT_MODIFIED,
			BAD_REQUEST,
			UNAUTHORIZED,
			FORBIDDEN,
			NOT_FOUND,
			INTERNAL_SERVER_ERROR,
			NOT_IMPLEMENTED,
			BAD_GATEWAY,
			SERVICE_UNAVAILABLE,
			OTHER
		};

		StatusCode();
		StatusCode(Value status);
		StatusCode(int code, const std::string& reason);

		explicit operator bool() const = delete;
		constexpr operator Value() const { return value; }
		constexpr bool operator==(StatusCode other) const { return value == other.value; }
		constexpr bool operator==(Value other) const { return value == other; }
		constexpr bool operator!=(StatusCode other) const { return value != other.value; }

		void setCode(const std::string& code);
		int getCode() const;
		
		void setReason(const std::string& reason);
		std::string getReason() const;

		static std::expected<StatusCode, std::monostate> fromCode(const std::string &code);

	private:
		Value value;

		int code;
		std::string reason;

		int _getCode() const;
		std::string _getReason() const;
	};

	class Version
	{
	public:
		enum Value
		{
			HTTP_0_9,
			HTTP_1_0,
		};

		Version() = default;
		constexpr Version(Value version) : value(version) {}

		explicit operator bool() const = delete;
		constexpr operator Value() const { return value; }
		constexpr bool operator==(Version other) const { return value == other.value; }
		constexpr bool operator!=(Version other) const { return value != other.value; }

		std::string toString() const;
		static std::expected<Version, std::monostate> fromString(const std::string& version);

	private:
		Value value;
	};

	// std::string url_encode(const std::string& uri);
	// std::string url_decode(const std::string& uri);
};  // namespace coll::http
