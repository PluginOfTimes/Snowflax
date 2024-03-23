#include "EventDispatcher.h"



void Snowflax::Infrastructure::Events::EventDispatcher::operator-=(IEventHandler& _handler)
{
	Unregister(_handler);
	m_EventsToListen.erase(_handler.GetEventType());
	UpdateListenedEvents();
}

void Snowflax::Infrastructure::Events::EventDispatcher::operator+=(IEventHandler& _handler)
{
	Register(_handler);
	UpdateListenedEvents();
}

void Snowflax::Infrastructure::Events::EventDispatcher::OnEvent(Event& _event)
{
	auto pos = std::find(m_EventsToListen.begin(), m_EventsToListen.end(), _event.GetEventType());
	if (pos != m_EventsToListen.end()) {
		Dispatch(_event);
	}
}

void Snowflax::Infrastructure::Events::EventDispatcher::Dispatch(Event& _event)
{
	typename std::vector<IEventHandler*>::iterator it;
	for (it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
		auto handler = *it;
		if (handler->GetEventType() == _event.GetEventType()) handler->Handle(_event);
	}
}

void Snowflax::Infrastructure::Events::EventDispatcher::Register(IEventHandler& _handler)
{
	if (std::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), &_handler) == m_RegisteredHandlers.end()) {
		m_RegisteredHandlers.push_back(&_handler);
	}
}

void Snowflax::Infrastructure::Events::EventDispatcher::Unregister(IEventHandler& _handler)
{
	auto pos = std::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), &_handler);
	if (pos != m_RegisteredHandlers.end()) {
		m_RegisteredHandlers.erase(pos);
	}
}

void Snowflax::Infrastructure::Events::EventDispatcher::operator()(Event& _event)
{
	Dispatch(_event);
}

void Snowflax::Infrastructure::Events::EventDispatcher::UpdateListenedEvents()
{
	typename std::vector<IEventHandler*>::iterator it;
	for (it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
		m_EventsToListen.insert((*it)->GetEventType());
	}
}

