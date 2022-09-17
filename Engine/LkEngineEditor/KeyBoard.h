#pragma once

#include <map>

class KeyBoard
{
public:

	void pressKey(int key)
	{
		m_keyIspress[key] = true;
	}

	void releaseKey(int key)
	{
		m_keyIspress[key] = false;
	}

	bool isKeyPress(int key)
	{
		if (m_keyIspress.find(key) != m_keyIspress.end())
			return m_keyIspress[key];
		return false;
	}
	static KeyBoard& getInstance()
	{
		return s_keyboard;
	}
private:
	std::map<int, bool> m_keyIspress;
private:
	static KeyBoard s_keyboard;

};

