#include "Room.hpp"
#include "chat_message.hpp"
#include <cstdlib>
#include <boost/bind.hpp>

void Room::join(paticipant_ptr paticipant)
{
	// 加入到用户的集合
	paticipants_.insert(paticipant);

	// 将最近的消息全部传给用户
	std::for_each(messages.begin(), messages.end(), boost::bind(&Paticipant::deliver, paticipant, _1));
}

// 用户离开，删除用户
void Room::leave(paticipant_ptr paticipant)
{
	paticipants_.erase(paticipant);	
}

// 给用户发送消息
void Room::deliver(const chat_message &msg)
{
	messages.push_back(msg);
	
	// 对记录的信息进行控制
	while(messages.size() > max_msgs)
		messages.pop_front();

	std::for_each(paticipants_.begin(), paticipants_.end(), boost::bind(&Paticipant::deliver, _1, boost::ref(msg)));
}


