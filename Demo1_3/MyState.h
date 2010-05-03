
#pragma once

class MyState
{
public:
	MyState(void);

	virtual ~MyState(void);

public:
	virtual void enterState(void);

	virtual void leaveState(void);
};

typedef boost::shared_ptr<MyState> MyStatePtr;

typedef std::map<std::basic_string<charT>, MyStatePtr> MyStatePtrMap;

class MyStateChart
{
protected:
	MyStatePtrMap m_stateMap;

	MyStatePtr m_currentState;

public:
	MyStateChart(void);

	virtual ~MyStateChart(void);

public:
	void addState(const std::basic_string<charT> & name, MyStatePtr state);

	void setCurrentState(const std::basic_string<charT> & name);

	template <class DRIVED_STATE_CLASS>
	boost::shared_ptr<DRIVED_STATE_CLASS> getCurrentState(void)
	{
		// current state must be set
		_ASSERT(m_currentState);

		// use boost smart ptr conversion
		return boost::dynamic_pointer_cast<DRIVED_STATE_CLASS, MyState>(m_currentState);
	}
};
