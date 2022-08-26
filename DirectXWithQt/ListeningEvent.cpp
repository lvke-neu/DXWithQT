#include "ListeningEvent.h"




void ListeningEventManager::registerListeningEvent(ListeningEvent* listeningEvent)
{
	m_listeningEvents.push_back(listeningEvent);
}

void ListeningEventManager::notifyAll(const std::string& msg)
{
	for (auto& listeningEvent : m_listeningEvents)
	{
		listeningEvent->callBack(msg);
	}
}

void ListeningEventManager::unregisterListeningEvent(ListeningEvent* listeningEvent)
{
	for (auto it = m_listeningEvents.begin(); it != m_listeningEvents.end(); it++)
	{
		if (*it == listeningEvent)
			m_listeningEvents.erase(it);
	}
}

void ListeningEventManager::messaegeBox(const std::string& msg)
{
	//for (auto& chapDockWidget : m_chapDockWidgets)
	//{
	//	chapDockWidget->messaegeBox(msg);
	//}
}

void ListeningEventManager::stopTimer()
{
	//for (auto& chapDockWidget : m_chapDockWidgets)
	//{
	//	chapDockWidget->stopTimer();
	//}
}

void ListeningEventManager::startTimer()
{
	//for (auto& chapDockWidget : m_chapDockWidgets)
	//{
	//	chapDockWidget->startTimer();
	//}
}
