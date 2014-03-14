#pragma once

template<typename T>
class State
{
public:
	virtual ~State() { }
	virtual void execute(T* owner, float frameTime) = 0;
};