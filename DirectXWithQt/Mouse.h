#pragma once

enum MouseButton 
{
    NoButton = 0x00000000,
    LeftButton = 0x00000001,
    RightButton = 0x00000002,
};

struct Delta
{
public:
    Delta() = default;
    Delta(float x, float y)
    {
        m_x = x;
        m_y = y;
    }
    float m_x;
    float m_y;
};
class Mouse
{
public:
    static Delta m_delta;
	static MouseButton m_whichButton;
    static float x;
    static float y;
};

