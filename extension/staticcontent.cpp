#include "staticcontent.hpp"
#include <boost/property_tree/xml_parser.hpp>
using namespace boost::property_tree::xml_parser;
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#include <boost/regex.hpp>
#include <ctime>
#include <boost/foreach.hpp>

StaticContent::StaticContent(asio::io_service& io, boost::function<void(std::string)> sender)
	: io_(io)
	, sender_(sender)
	, d_(0, 10000)
{
	g_.seed(std::time(0));
	std::string filename = "static.xml";
	if(fs::exists(filename))
	{
		ptree pt;
		read_xml(filename, pt);
		BOOST_FOREACH(const ptree::value_type & item,  pt.get_child("static"))
		{
			std::string keyword = item.second.get<std::string>("keyword");
			std::vector<std::string> messages;
			BOOST_FOREACH(const ptree::value_type & message,  item.second.get_child("messages"))
			{
				messages.push_back(message.second.get_value<std::string>());
			}
			static_contents_[boost::regex(keyword)] = boost::move(messages);
		}
	}
}

void StaticContent::operator()(const ptree& pt)
{
	typedef std::pair<Keywords, Messages> item_type;
	std::string text = pt.get<std::string>("message.text");

	BOOST_FOREACH(const item_type & item,  static_contents_)
	{
		if(boost::regex_search(text, item.first))
		{
			sender_(item.second[d_(g_) % item.second.size()]);
		}
	}
}