#include "Connection.hpp"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

Connection::Connection(boost::asio::io_service& io_service, const tcp::endpoint& endpoint):io_service_(io_service), acceptor_(io_service, endpoint)
{
	session_ptr new_session(new Session(io_service_, room_));
	acceptor_.async_accept(new_session->socket(), boost::bind(&Connection::handle_accept, 
		this, new_session, boost::asio::placeholders::error));
}

void Connection::handle_accept(session_ptr session, const boost::system::error_code& error)
{
	if (!error)
	{
		session->start();
		session_ptr new_session(new Session(io_service_, room_));
		acceptor_.async_accept(new_session->socket(), boost::bind(&Connection::handle_accept, this, new_session, boost::asio::placeholders::error));
	}
}
