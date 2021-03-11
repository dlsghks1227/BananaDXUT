#pragma once
#include "header.hpp"
#include "IScene.hpp"

// �� ��ȯ
// https://thatgamesguy.co.uk/cpp-game-dev-6/

class SceneStateMachine
{
public:
	SceneStateMachine();
	~SceneStateMachine() = default;

	SceneStateMachine(SceneStateMachine&&) = default;
	SceneStateMachine& operator = (SceneStateMachine&&) = default;

	SceneStateMachine(SceneStateMachine const&) = delete;
	SceneStateMachine& operator = (SceneStateMachine const&) = delete;

	void		OnUpdate(float fElapsedTime);
	void		OnLateUpdate(float fElapsedTime);

	void		OnRender(float fElapsedTime);

	void		OnResetDevice();
	void		OnLostDevice();

	void		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void		OnMouse(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);

	LRESULT		MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);

	void Add(std::wstring const& name, std::shared_ptr<IScene> scene);
	void SwitchTo(std::wstring name);

private:
	std::unordered_map<std::wstring, std::shared_ptr<IScene>>	m_scenes;
	std::shared_ptr<IScene>										m_currentScene;
};