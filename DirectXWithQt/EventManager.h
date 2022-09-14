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

/*选中某个GameObject事件*/
class GameObject;
class PickEvent
{
public:
	virtual void onMouseLocateGo(const std::string& msg) = 0;
	virtual void onPickGameObject(GameObject& go) = 0;
};

/*帧移动事件*/
class FrameMoveEvent
{
public:
	virtual void onFrameMove(float deltaTime) = 0;
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

	void registerPickEveent(PickEvent* pickEveent);
	void unregisterPickEveent(PickEvent* pickEveent);
	void onMouseLocateGo(const std::string& msg);
	void onPickGameObject(GameObject& go);

	void registerFrameMoveEvent(FrameMoveEvent* frameMoveEvent);
	void unregisterFrameMoveEvent(FrameMoveEvent* frameMoveEvent);
	void onFrameMove(float deltaTime);
private:
	std::vector<CameraMoveEvent*> m_cameraMoveEvents;
	std::vector<PickEvent*> m_pickEvents;
	std::vector<FrameMoveEvent*> m_frameMoveEvents;
};