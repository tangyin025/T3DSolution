
#pragma once

class MyState
{
public:
	virtual void enterState(void);

	virtual void leaveState(void);
};

typedef boost::shared_ptr<MyState> MyStatePtr;

typedef std::map<std::string, MyStatePtr> MyStatePtrMap;

class MyStateChart
{
protected:
	MyStatePtrMap m_stateMap;

	MyStatePtr m_currentState;

public:
	void addState(const std::string & name, MyStatePtr state);

	void setCurrentState(const std::string & name);

	template <class DRIVED_STATE_CLASS>
	boost::shared_ptr<DRIVED_STATE_CLASS> getCurrentState(void)
	{
		// current state must be set
		_ASSERT(m_currentState);

		// use boost smart ptr conversion
		return boost::dynamic_pointer_cast<DRIVED_STATE_CLASS, MyState>(m_currentState);
	}
};
