#include "Room.hpp"
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session: public Paticipant, public boost::enable_shared_from_this<Session>
{
	public:
		Session(boost::asio::io_service& io_service, Room& room);

	public:
		tcp::socket socket_;
		Room& room_;
		chat_message read_msg_;
		chat_message_queue write_msgs_;


	public:
		// 获取socket
		tcp::socket& socket();

		// 会话开始，准备从客户端读取数据
		void start();

		// 读取文件头
		void handle_read_header(const boost::system::error_code &error);

		// 读body
		void handle_read_body(const boost::system::error_code &error);

		// 对客户端发送消息
		void deliver(const chat_message & msg);

		// 具体写消息
		void handle_write(const boost::system::error_code &error);

};
