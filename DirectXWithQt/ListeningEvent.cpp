#include "ListeningEvent.h"
#include "ChapterDockWidget.h"

void ListeningEvent::registerListeningEvent(ChapterDockWidget* chapterDockWidget)
{
	m_chapDockWidgets.push_back(chapterDockWidget);
}

void ListeningEvent::notifyAll(const std::string& msg)
{
	for (auto& chapDockWidget : m_chapDockWidgets)
	{
		chapDockWidget->callback(msg);
	}
}

void ListeningEvent::unregisterListeningEvent(ChapterDockWidget* chapterDockWidget)
{
	for (auto it = m_chapDockWidgets.begin(); it != m_chapDockWidgets.end(); it++)
	{
		if (*it == chapterDockWidget)
			m_chapDockWidgets.erase(it); 
	}
}

void ListeningEvent::messaegeBox(const std::string& msg)
{
	for (auto& chapDockWidget : m_chapDockWidgets)
	{
		chapDockWidget->messaegeBox(msg);
	}
}