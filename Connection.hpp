#include "Session.hpp"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

class Connection
{
	public:
		Connection(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);

	public:
		typedef boost::shared_ptr<Session> session_ptr;

	public: 	
		// 处理用户的连接
		void handle_accept(session_ptr session, const boost::system::error_code& error);

	private:
		boost::asio::io_service& io_service_;
		tcp::acceptor acceptor_;
		Room room_;
};



