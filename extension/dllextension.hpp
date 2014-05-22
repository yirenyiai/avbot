/*
 * Copyright (C) 2014  microcai <microcai@fedoraproject.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#ifndef __DLL_EXTENSION_HPP_
#define __DLL_EXTENSION_HPP_

#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/thread/once.hpp>
#include <boost/thread/thread.hpp>

#include <boost/cfunction.hpp>
#include "extension.hpp"

template<class MsgSender>
class dllextention_caller
{
private:
	boost::asio::io_service &io_service;
	std::string m_channel;
	typename boost::remove_reference<MsgSender>::type m_sender;
public:
	dllextention_caller(boost::asio::io_service & _io_service, std::string _channel, MsgSender sender)
		: m_sender(sender)
		, io_service(_io_service)
		, m_channel(_channel)
	{
	}

	typedef void (*message_sender_t)(const char * message, void* _apitag);

	typedef void (*avbot_on_message_t)(const char * message, const char * channel, message_sender_t sender, void* _apitag);

	void operator()(boost::property_tree::ptree msg)
	{
		std::string textmsg = boost::trim_copy(msg.get<std::string>("message.text"));

		boost::thread t(boost::bind(&dllextention_caller<MsgSender>::call_dll_message, this, textmsg, m_channel, m_sender));
		t.detach();
	}

	void call_dll_message(std::string textmsg, std::string channel, boost::function<void(std::string)> sender)
	{
		boost::shared_ptr<void> dll_module;
		static boost::mutex m;
		{
			boost::mutex::scoped_lock l(m);

			dll_module.reset(
				LoadLibraryW(L"avbotextension"),
				[&](void * p)
				{
					boost::mutex::scoped_lock l(m);
					FreeLibrary((HMODULE)p);
					std::cerr << literal_to_localstr("已卸载 avbotextension.dll") << std::endl;
			}
			);

			if (dll_module)
			{
				std::cerr << literal_to_localstr("已加载 avbotextension.dll!!!") << std::endl;
			}
			else
			{
				std::cerr << literal_to_localstr("没有找到 avbotextension.dll!!!") << std::endl;
				std::cerr << literal_to_localstr("无调用!") << std::endl;
				return ;
			}
		}

		auto p = GetProcAddress((HMODULE)(dll_module.get()), "avbot_on_message");
		avbot_on_message_t f = reinterpret_cast<avbot_on_message_t>(p);

		if (!f)
		{
			MessageBoxA(0, "avbot_on_message 函数没找到", "avbotdllextension.dll", MB_OK);
		}

		// 调用 f 吧！
		boost::cfunction<1, message_sender_t> sender_for_c = sender;
		f(textmsg.c_str(), channel.c_str(), sender_for_c.c_func_ptr(), sender_for_c.c_void_ptr());

		std::cout << "called avbot_on_message()" << std::endl;
	}
};

template<class MsgSender>
avbot_extension make_dllextention(boost::asio::io_service & io_service,
	std::string _channel, const MsgSender & sender)
{
	return avbot_extension(
		_channel,
		dllextention_caller<typename boost::remove_reference<MsgSender>::type>(io_service, _channel, sender)
	);
}

#endif // __DLL_EXTENSION_HPP_
