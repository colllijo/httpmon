#include "httpmon.hpp"

int main()
{
	coll::http::Request request;
	request.set_method(coll::http::Method::GET);
	request.set_host("example.com");
	request.set_path("/");
	request.set_port(80);
	request.set_header("Host", "example.com");

	coll::http::Response response = request.execute();

	for (const auto& [key, value] : response.getHeaders())
	{
		printf("%s: %s\n", key.c_str(), value.value_or("").c_str());
	}

	return 0;
}
