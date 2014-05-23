#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
namespace asio = boost::asio;
using boost::property_tree::ptree;
#include <boost/random.hpp>
#include <boost/function.hpp>

#include "extension.hpp"

avbot_extension make_v8_executer(asio::io_service& io, std::string channel_name, boost::function<void(std::string)> sender);
