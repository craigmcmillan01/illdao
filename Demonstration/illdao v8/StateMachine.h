#pragma once

#include <hash_map>
#include <string>
#include "State.h"

template<typename T>
class StateMachine
{
private:
	T* owner;
	std::hash_map<std::string, State<T>*> states;
	State<T>* currentState;
public:
	StateMachine(T* owner) : owner(owner), currentState(0) { }
	~StateMachine();
	void addState(std::string name, State<T>* state);
	State<T>* getState(std::string name);
	State<T>* getCurrentState(); //added in to return the current state
	void removeState(std::string name);
	void changeState(std::string name);
	void update(float deltaTime);
};

template<typename T>
StateMachine<T>::~StateMachine()
{
	std::hash_map<std::string, State<T>*>::iterator iter = states.begin();
	for (; iter != states.end(); ++iter)
	{
		delete iter->second;
		iter->second = 0;
	}
	states.clear();
	owner = 0;
	currentState = 0;
}

template<typename T>
void StateMachine<T>::addState(std::string name, State<T>* state)
{
	states[name] = state;
}

template<typename T>
State<T> * StateMachine<T>::getState(std::string name)
{
	return states[name];
}

template<typename T>
void StateMachine<T>::removeState(std::string name)
{
	states.remove(name);
}

template<typename T>
void StateMachine<T>::changeState(std::string name)
{
	currentState = states[name];
}

template<typename T>
State<T> * StateMachine<T>::getCurrentState() //returns the current state usefull for checking what state each player is in
{
	return currentState;
}

template<typename T>
void StateMachine<T>::update(float deltaTime)
{
	currentState->execute(owner, deltaTime);
}