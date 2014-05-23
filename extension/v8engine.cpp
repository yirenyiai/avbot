#include "staticcontent.hpp"
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#include <boost/regex.hpp>
#include <ctime>
#include <boost/foreach.hpp>
#include "v8.h"

struct v8executer
{
	v8executer(asio::io_service& io, boost::function<void(std::string)> sender);

	void operator()(boost::system::error_code ec) {}

	void operator()(const ptree& pt);

	asio::io_service& io_;
	boost::function<void(std::string)> sender_;
	typedef boost::regex Keywords;
	typedef std::vector<std::string> Messages;
	std::map<Keywords, Messages> static_contents_;

	boost::random::mt19937 g_;
	boost::uniform_int<> d_;

};

v8executer::v8executer(asio::io_service& io, boost::function<void(std::string)> sender)
	: io_(io)
	, sender_(sender)
	, d_(0, 10000)
{
}

void v8executer::operator()(const ptree& pt)
{
}

avbot_extension make_v8_executer(asio::io_service& io, std::string channel_name, boost::function<void(std::string)> sender)
{
	return avbot_extension(
		channel_name,
		v8executer(io, sender)
	);
}
