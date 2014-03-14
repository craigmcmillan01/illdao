#pragma once

#include <string>

class Entity;

struct Message
{
	Entity* entity;
	std::string message;
	void* data;

	Message(Entity* entity, const std::string& msg, void* info)
		: entity(entity), message(msg), data(info)
	{
	}
};
