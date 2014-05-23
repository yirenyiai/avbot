
#pragma once

#include <string>
#include <boost/function.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/shared_ptr.hpp>

#include "libavbot/avbot.hpp"
#include "boost/stringencodings.hpp"

class avbot_extension;

namespace detail{
class avbotexteison_interface
{
public:
	virtual void operator()(const boost::property_tree::ptree & msg) = 0;
};

template<class ExtensionType>
class avbotexteison_adapter : public avbotexteison_interface
{
	ExtensionType m_pextension;
	void operator()(const boost::property_tree::ptree & msg)
	{
		(m_pextension)(msg);
	}

public:
	avbotexteison_adapter(const ExtensionType & obj)
		: m_pextension(obj)
	{
	}

	avbotexteison_adapter(ExtensionType * obj)
		: m_pextension(*obj)
	{
	}
};

} // namespace detail

// type erasure for avbot extension
class avbot_extension
{
	boost::shared_ptr<detail::avbotexteison_interface> m_exteison_obj;
	std::string m_channel_name;

public:

	template<class ExtensionType>
	avbot_extension(std::string channel_name, const ExtensionType & extensionobj)
		: m_channel_name( channel_name )
	{
		m_exteison_obj.reset(
			new detail::avbotexteison_adapter<
				typename boost::remove_reference<ExtensionType>::type
			>(extensionobj)
		);
	}

	template<class ExtensionType>
	avbot_extension & operator = (const ExtensionType & extensionobj)
	{
		m_exteison_obj.reset(
			new detail::avbotexteison_adapter<
				typename boost::remove_reference<ExtensionType>::type
			>(extensionobj)
		);
		return *this;
	}

	template<class ExtensionType>
	avbot_extension & operator = (ExtensionType * extensionobj)
	{
		m_exteison_obj.reset(
			new detail::avbotexteison_adapter<
			typename boost::remove_reference<ExtensionType>::type
			>(extensionobj)
		);
		return *this;
	}

	avbot_extension & operator = (const avbot_extension & rhs)
	{
		m_exteison_obj = rhs.m_exteison_obj;
		m_channel_name = rhs.m_channel_name;
		return *this;
	}

	void operator()(const boost::property_tree::ptree & msg)
	{
		try{
			if (msg.get<std::string>("channel") != m_channel_name)
				return;
			// 调用实际的函数
			(*m_exteison_obj)(msg);
		}catch (const boost::property_tree::ptree_error&)
		{
            // error access the ptree
            // ignore it
        }
	}
	typedef void result_type;
};

void new_channel_set_extension(boost::asio::io_service &io_service, avbot & mybot , std::string channel_name);
