
#include "StdAfx.h"
#include "MyState.h"

MyState::MyState(void)
{
}

MyState::~MyState(void)
{
}

void MyState::enterState(void)
{
}

void MyState::leaveState(void)
{
}

MyStateChart::MyStateChart(void)
{
}

MyStateChart::~MyStateChart(void)
{
}

void MyStateChart::setCurrentState(const std::basic_string<charT> & name)
{
	// the specified name state must be in the map
	_ASSERT(m_stateMap.end() != m_stateMap.find(name));

	// leave previous state
	if(m_currentState)
	{
		m_currentState->leaveState();
	}

	// set current state name
	m_currentStateName = name;

	// set current state
	m_currentState = m_stateMap[name];

	// enter current state
	m_currentState->enterState();
}
