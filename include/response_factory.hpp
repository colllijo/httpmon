#include "response.hpp"

namespace coll::http
{
	class ResponseFactory
	{
	public:
		static Response createResponse(const std::vector<uint8_t>& data);

	private:
		static Version determineResponseVersion(const std::vector<uint8_t>& data);

		static Response createHTTP_0_9_Response(const std::vector<uint8_t>& data);
		static Response createHTTP_1_0_Response(const std::vector<uint8_t>& data);
	};
}  // namespace coll::http
