#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <functional>

template <typename T>
class StateMachine
{
public:
	//using StateMachineCB = void (*)(T prevState, T currState);
	//using StateMachineCB = std::function<int(T, T)>;
	typedef std::function<void(T, T)> StateMachineCB;

private:
	T prevState, currState;
	StateMachineCB callback;
public:

	StateMachine(StateMachineCB callback, T initialState)
	{
		this->callback = callback;
		this->prevState = initialState;
		this->currState = initialState;
	}

	void updateState(T state)
	{
		this->prevState = this->currState;
		this->currState	= state;

		if(callback){
			callback(this->prevState, this->currState);
		}
	}

	T getState()
	{
		return currState;
	}
};

#endif