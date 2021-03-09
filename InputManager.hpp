#pragma once
#include "DXUT.h"
#include "header.hpp"

class KeyState
{
public:
	KeyState() noexcept : m_press(false), m_push(false), m_release(false) {}

	void SetPress(bool press)		{ m_press = press; }
	void SetPush(bool push)			{ m_push = push; }
	void SetRelease(bool release)	{ m_release = release; }

	bool GetPress()					{ return m_press; }
	bool GetPush()					{ return m_push; }
	bool GetRelease()				{ return m_release; }

private:
	bool		m_press;
	bool		m_push;
	bool		m_release;
};

class InputManager
{
public:
	InputManager() noexcept;
	~InputManager() = default;

	void			Initialize();
	void			KeyBoardUpdate();

	void			OnLeftMousePressed(D3DXVECTOR2 const& pos);
	void			OnLeftMouseReleased(D3DXVECTOR2 const& pos);

	void			OnRightMousePressed(D3DXVECTOR2 const& pos);
	void			OnRightMouseReleased(D3DXVECTOR2 const& pos);

	void			OnMouseMove(D3DXVECTOR2 const& pos);
	D3DXVECTOR2		GetMousePos()			{ return m_mousePos; }

	bool			GetLeftMouseDown()		{ return m_leftMouseDown; }
	bool			GetRightMouseDown()		{ return m_rightMouseDown; }

	bool			GetKeyPressed(int vkey) { return m_keyState[vkey].GetPress(); }
	bool			GetKeyPush(int vkey)	{ return m_keyState[vkey].GetPush(); }
	bool			GetKeyRelease(int vkey) { return m_keyState[vkey].GetRelease(); }


public:
	Microsoft::WRL::ComPtr<IDirectInput8W>			m_directInput;
	Microsoft::WRL::ComPtr<IDirectInputDevice8W>	m_keyboard;
	BYTE											m_key[256];
	KeyState										m_keyState[256];

	bool											m_leftMouseDown;
	bool											m_rightMouseDown;
	D3DXVECTOR2										m_mousePos;

};

extern std::unique_ptr<InputManager>				g_inputManager;