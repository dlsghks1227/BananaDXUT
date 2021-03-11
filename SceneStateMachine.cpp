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