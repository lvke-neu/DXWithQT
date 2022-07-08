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
    static void setDelta(const Delta& delta)
    {
        m_delta.m_x = delta.m_x;
        m_delta.m_y = delta.m_x;
    }

    static float getDeltaX()
    {
        return m_delta.m_x;
    }
    static float getDeltaY()
    {
        return m_delta.m_y;
    }
private:
    static Delta m_delta;
};

