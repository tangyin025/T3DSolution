
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

typedef std::tr1::shared_ptr<MyState> MyStatePtr;

typedef std::map<std::basic_string<charT>, MyStatePtr> MyStatePtrMap;

class MyStateChart
{
protected:
	MyStatePtrMap m_stateMap;

	std::basic_string<charT> m_currentStateName;

	MyStatePtr m_currentState;

public:
	MyStateChart(void);

	virtual ~MyStateChart(void);

public:
	void addState(const std::basic_string<charT> & name, MyStatePtr state)
	{
		// the specified name state must not be in the map
		_ASSERT(m_stateMap.end() == m_stateMap.find(name));

		// insert this state to map
		m_stateMap[name] = state;
	}

	template <class DRIVED_STATE_CLASS>
	std::tr1::shared_ptr<DRIVED_STATE_CLASS> getState(const std::basic_string<charT> & name)
	{
		// the specified name state must be in the map
		_ASSERT(m_stateMap.end() != m_stateMap.find(name));

		// use smart ptr conversion
		return std::tr1::dynamic_pointer_cast<DRIVED_STATE_CLASS, MyState>(m_stateMap[name]);
	}

	const std::basic_string<charT> & getCurrentStateName(void) const
	{
		// return current state name
		return m_currentStateName;
	}

	void setCurrentState(const std::basic_string<charT> & name);

	template <class DRIVED_STATE_CLASS>
	std::tr1::shared_ptr<DRIVED_STATE_CLASS> getCurrentState(void)
	{
		// current state must be set
		_ASSERT(m_currentState == m_stateMap[m_currentStateName]);

		// use smart ptr conversion
		return std::tr1::dynamic_pointer_cast<DRIVED_STATE_CLASS, MyState>(m_currentState);
	}
};
