
#include "StdAfx.h"
#include "MyState.h"

void MyState::enterState(void)
{
}

void MyState::leaveState(void)
{
}

void MyStateChart::addState(const std::string & name, MyStatePtr state)
{
	// the specified name state must not be in the map
	_ASSERT(m_stateMap.end() == m_stateMap.find(name));

	// insert this state to map
	m_stateMap[name] = state;
}

void MyStateChart::setCurrentState(const std::string & name)
{
	// the specified name state must be in the map
	_ASSERT(m_stateMap.end() != m_stateMap.find(name));

	// leave previous state
	if(m_currentState)
	{
		m_currentState->leaveState();
	}

	// set current state
	m_currentState = m_stateMap[name];

	// enter current state
	m_currentState->enterState();
}
