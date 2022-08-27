/***************************************************************************************
Author: lvke
Date:2022/7/18 22:28
Description:
监听事件接口，当场景中的相机变换（scale、rotation、position）时,通知右边的dockwidget
兼顾连接dx与qt的桥梁
modified by lvke， 将事件拆分成多种不同的事件，由事件管理器进行注册、注销、回调
****************************************************************************************/

#pragma once
#include <vector>
#include <string>


/*相机移动事件*/
class CameraMoveEvent
{
public:
	virtual void onCameraMove(const std::string& msg) = 0;
};



class EventManager
{
private:
	EventManager() = default;

public:
	static EventManager& getInstance()
	{
		static EventManager instance;
		return instance;
	}
public:
	void registerCameraMoveEvent(CameraMoveEvent* listeningEvent);
	void unregisterCameraMoveEvent(CameraMoveEvent* listeningEvent);
	void onCameraMove(const std::string& msg);
	void messaegeBox(const std::string& msg);
	void stopTimer();
	void startTimer();
private:
	std::vector<CameraMoveEvent*> m_cameraMoveEvents;
	
};