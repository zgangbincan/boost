#include "Session.hpp"
#include <boost/bind.hpp>



tcp::socket&  Session::socket()
{
	return socket_;	
}

Session::Session(boost::asio::io_service& io_service, Room& room):socket_(io_service), room_(room)
{
	
}

void Session::start()
{
	//  把用户加入房间
	room_.join(shared_from_this());

	boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), 
		chat_message::header_length), boost::bind(&Session::handle_read_header, 
			shared_from_this(), boost::asio::placeholders::error));
}

void Session::handle_read_header(const boost::system::error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), 
			read_msg_.body_length()), boost::bind(&Session::handle_read_body, 
				shared_from_this(), boost::asio::placeholders::error));	
	}
	else
	{
		// 读取文件头出错，直接离开
		room_.leave(shared_from_this());
	}
}

void Session::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		room_.deliver(read_msg_);
		boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), 
			chat_message::header_length), boost::bind(&Session::handle_read_header, 
				shared_from_this(), boost::asio::placeholders::error));	
	}
	else
	{
		room_.leave(shared_from_this());
	}
}

void Session::deliver(const chat_message& msg)
{
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);
	if (write_in_progress)
	{
		boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), 
			write_msgs_.front().length()), boost::bind(&Session::handle_write,shared_from_this(), 
				boost::asio::placeholders::error));
	}
}

void Session::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		write_msgs_.pop_front();
		if (!write_msgs_.empty())
		{
			boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), 
				write_msgs_.front().length()), boost::bind(&Session::handle_write, shared_from_this(), 
					boost::asio::placeholders::error));
		}
	}
}

