#include "pch.h"
#include "WindowHandle.h"

namespace Hazel {

	void Hazel::WindowHandle::OnDrag(int x, int y)
	{
		if ( m_Window.IsMaximized() ) {
			float preWidthFactor = (float)x / (float)m_Window.GetResolution().x;
			m_Window.Restore();
			vec2int cursorOnMonitor = m_Window.GetPosition() + vec2int( x, y );
			m_StartWindowPosition = cursorOnMonitor;
			m_StartCursorPosition = { (int)(preWidthFactor * (float)m_Window.GetResolution().x),y };
		}
		m_Difference += vec2int( x, y ) - m_StartCursorPosition; 
		vec2int result = m_StartWindowPosition + m_Difference;
		m_Window.SetPosition(result.x, result.y);
	}

	void WindowHandle::OnLeftPress(int x, int y)
	{
		m_IsDragging = true;
		m_Difference = { 0,0 };
		m_StartCursorPosition = { x,y };
		m_StartWindowPosition = m_Window.GetPosition();
	}

	void WindowHandle::OnLeftRelease(int x, int y)
	{
		if ( !m_Window.IsMaximized() ) {
			int cursorYOnMonitor = m_Window.GetPosition().y + y;
			if ( cursorYOnMonitor == 0 )
				m_Window.Maximize();
		}
		m_IsDragging = false;
	}

}
