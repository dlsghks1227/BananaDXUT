#include "DXUT.h"
#include "InputManager.hpp"

std::unique_ptr<InputManager> g_inputManager = std::make_unique<InputManager>();

InputManager::InputManager() noexcept :
	m_mousePos(D3DXVECTOR2(0.0f, 0.0f)),
	m_key{ 0 }
{
}

void InputManager::Initialize()
{
	DX::ThrowIfFailed(DirectInput8Create(
		DXUTGetHINSTANCE(), 
		DIRECTINPUT_HEADER_VERSION, 
		IID_IDirectInput8W, 
		reinterpret_cast<void**>(m_directInput.ReleaseAndGetAddressOf()), 
		nullptr
	));

	DX::ThrowIfFailed(m_directInput->CreateDevice(
		GUID_SysKeyboard,
		m_keyboard.ReleaseAndGetAddressOf(),
		nullptr
	));

	DX::ThrowIfFailed(m_keyboard->SetDataFormat(&c_dfDIKeyboard));

	DX::ThrowIfFailed(m_keyboard->Acquire());
}

void InputManager::KeyBoardUpdate()
{
	HRESULT hr = E_FAIL;
	hr = m_keyboard->GetDeviceState(256, static_cast<LPVOID>(&m_key));

	if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
	{
		m_keyboard->Acquire();
	}

	for (unsigned int vkey = 0; vkey < 256; vkey++)
	{
		if ((m_key[vkey] & 0x80))
		{
			if (m_keyState[vkey].GetPress() == false && m_keyState[vkey].GetPush() == false)
			{
				m_keyState[vkey].SetPress(true);
				m_keyState[vkey].SetPush(true);
			}
			else
			{
				m_keyState[vkey].SetPress(false);
			}
		}
		else if (m_keyState[vkey].GetPress() == true || m_keyState[vkey].GetPush() == true)
		{
			m_keyState[vkey].SetPress(false);
			m_keyState[vkey].SetPush(false);
			m_keyState[vkey].SetRelease(true);
		}
		else if (m_keyState[vkey].GetRelease() == true)
		{
			m_keyState[vkey].SetRelease(false);
		}
	}
}