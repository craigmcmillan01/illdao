#pragma once

#include <queue>
#include "Message.h"

class MessageHandler
{
private:
	static std::queue<Message> messages;
	static MessageHandler* instance;
	MessageHandler() { }
public:
	~MessageHandler();
	static void init();
	static void update();
	static void sendMessage(const Message& message);
};


