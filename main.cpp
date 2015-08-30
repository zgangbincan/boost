#include "Connection.hpp"
#include <cstdlib>
#include <list>
#include <algorithm>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

typedef boost::shared_ptr<Connection> connection_ptr;
typedef std::list<connection_ptr> connection_ptr_list;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
		{
			std::cerr << "Usage: chat_server <port> [<port> ...]" << std::endl;
		}
		
		boost::asio::io_service io_service;
		// 根据传进来的port的数量，创建多个server
		connection_ptr_list connections;

		for (int i = 1; i < argc ; ++i)
		{
			using namespace std;
			tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), atoi(argv[i]));
			connection_ptr connection(new Connection(io_service, endpoint));
			connections.push_back(connection);
		}
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception" << e.what() << std::endl;
	}
	
}
