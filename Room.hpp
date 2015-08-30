#include "Paticipant.hpp"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <set>

class Room
{
	public:
		// 参与者的共享指针对象
		typedef boost::shared_ptr<Paticipant> paticipant_ptr;

	public:
		enum {max_msgs = 100};

		// 所有连接上来的用户
		std::set<paticipant_ptr> paticipants_;

		// 所有的消息记录
		Paticipant::chat_message_queue messages;

	public:
		// 用户添加进来
		void join(paticipant_ptr paticipant);
	
		// 用户离开
		void leave(paticipant_ptr paticipant);

		// 发送消息
		void deliver(const chat_message& msg);
};
