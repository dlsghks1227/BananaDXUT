#include "DXUT.h"
#include "SceneStateMachine.hpp"


SceneStateMachine::SceneStateMachine() :
	m_scenes(),
	m_currentScene()
{
}

void SceneStateMachine::OnUpdate(float fElapsedTime)
{
	if (m_currentScene)
	{
		m_currentScene->OnUpdate(fElapsedTime);
	}
}

void SceneStateMachine::OnLateUpdate(float fElapsedTime)
{
	if (m_currentScene)
	{
		m_currentScene->OnLateUpdate(fElapsedTime);
	}
}

void SceneStateMachine::OnRender(float fElapsedTime)
{
	if (m_currentScene)
	{
		m_currentScene->OnRender(fElapsedTime);
	}
}

void SceneStateMachine::OnResetDevice()
{
	if (m_currentScene)
	{
		m_currentScene->OnResetDevice();
	}
}

void SceneStateMachine::OnLostDevice()
{
	if (m_currentScene)
	{
		m_currentScene->OnLostDevice();
	}
}

void SceneStateMachine::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	if (m_currentScene)
	{
		m_currentScene->OnKeyboard(nChar, bKeyDown, bAltDown, pUserContext);
	}
}

void SceneStateMachine::OnMouse(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	if (m_currentScene)
	{
		m_currentScene->OnMouse(bLeftButtonDown, bRightButtonDown, bMiddleButtonDown, bSideButton1Down, bSideButton2Down, nMouseWheelDelta, xPos, yPos, pUserContext);
	}
}

LRESULT SceneStateMachine::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	if (m_currentScene)
	{
		return m_currentScene->MsgProc(hWnd, uMsg, wParam, lParam, pbNoFurtherProcessing, pUserContext);
	}
	return 0;
}

void SceneStateMachine::Add(std::wstring const& name, std::shared_ptr<IScene> scene)
{
	// map insert 정확하게 사용하기
	// https://yonmy.com/archives/9
	auto inserted = m_scenes.insert({ name, scene });
	if (inserted.second == false)
	{
#ifdef _DEBUG
		std::wcout << "[Scene] 중복된 씬입니다.\n";
#endif
		inserted.first->second = scene;
	}
}

void SceneStateMachine::SwitchTo(std::wstring name)
{
	// map 키 값 검색
	// https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key

	// 괜찮은 map 설명
	// http://www.vishalchovatiya.com/using-std-map-wisely-with-modern-cpp/#stdmapcontainsC20

	// C++20 이전 코드
	auto itr = m_scenes.find(name);
	if (itr != m_scenes.end())
	{
		if (m_currentScene)
		{
			m_currentScene->OnExitScene();
		}

		m_currentScene = itr->second;

		m_currentScene->OnEnterScene();
	}

	// C++20 사용 가능 코드
	//if (m_scenes.contains(name) == true)
	//{
	//	if (m_currentScene)
	//	{
	//		m_currentScene->OnExitScene();
	//	}

	//	m_currentScene = m_scenes[name];

	//	m_currentScene->OnEnterScene();
	//}
}