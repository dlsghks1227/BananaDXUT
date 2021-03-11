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
	// map insert ��Ȯ�ϰ� ����ϱ�
	// https://yonmy.com/archives/9
	auto inserted = m_scenes.insert({ name, scene });
	if (inserted.second == false)
	{
#ifdef _DEBUG
		std::wcout << "[Scene] �ߺ��� ���Դϴ�.\n";
#endif
		inserted.first->second = scene;
	}
}

void SceneStateMachine::SwitchTo(std::wstring name)
{
	// map Ű �� �˻�
	// https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key

	// ������ map ����
	// http://www.vishalchovatiya.com/using-std-map-wisely-with-modern-cpp/#stdmapcontainsC20

	// C++20 ���� �ڵ�
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

	// C++20 ��� ���� �ڵ�
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