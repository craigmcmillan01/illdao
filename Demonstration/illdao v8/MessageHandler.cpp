#include "MessageHandler.h"
#include "Entity.h"
#include <iostream>

using namespace std;

queue<Message> MessageHandler::messages = queue<Message>();

MessageHandler* MessageHandler::instance = 0;

MessageHandler::~MessageHandler()
{
	while (!messages.empty())
		messages.pop();
	instance = 0;
}

void MessageHandler::init()
{
	MessageHandler::instance = new MessageHandler();
}
void MessageHandler::sendMessage(const Message& message)
{
	//std::cout<<"PUSH\n";
	messages.push(message);
}
void MessageHandler::update()
{
	while (!messages.empty())
	{
		Message msg = messages.front();
		messages.pop();
		msg.entity->handleMessage(msg);
	}
}


