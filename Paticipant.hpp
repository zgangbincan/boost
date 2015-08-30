#include "chat_message.hpp"
#include <queue>
#include <boost/asio.hpp>

class Paticipant
{
	public:

		typedef std::deque<chat_message> chat_message_queue;
	
	public:
		
		virtual ~Paticipant(){}

		virtual void deliver(const chat_message& msg) = 0;

};
