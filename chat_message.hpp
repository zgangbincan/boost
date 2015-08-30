#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

// 聊天的数据包
class chat_message
{
public:
	enum { header_length = 4 };
	enum { max_body_length = 532 };

	chat_message() : body_length_(0) { }

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	void body_length(size_t length)
	{
		body_length_ = length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

	// 解码头部
	bool decode_header()
	{
		using namespace std; // For strncat and atoi.
		char header[header_length + 1] = "";
		strncat(header, data_, header_length);
		body_length_ = atoi(header);
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	// 加密头部
	void encode_header()
	{
		using namespace std; // For sprintf and memcpy.
		char header[header_length + 1] = "";
		sprintf(header, "%4d", body_length_);
		memcpy(data_, header, header_length);
	}

private:
	// 整个数据包的数据，分为两部分，数据长度，数据。
	char data_[header_length + max_body_length];
	// 数据长度
	size_t body_length_;
};

#endif // CHAT_MESSAGE_HPP