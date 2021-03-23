#pragma once
#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "dinput8.lib")

#include <wrl.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <stdexcept>
#include <tchar.h>
#include <cstdio>
#include <exception>
#include <vector>
#include <map>
#include <set>
#include <stack>

#include <queue>
#include <unordered_map>

#ifdef _DEBUG
#include <iostream>
#endif

#define DIRECTINPUT_VERSION 0x8000
#include <dinput.h>

// 콘솔창 출력
#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#include <dxgidebug.h>
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#define Assert(b) do {if (!(b)) { OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif // DEBUG || _DEBUG
#endif

// 예외처리
namespace DX
{
	// https://github.com/Microsoft/DirectXTK/wiki/ThrowIfFailed
	// Helper class for COM exceptions

	class com_exception : public std::exception
	{
	public:
		com_exception(HRESULT hr) : result(hr) {}

		const char* what() const override
		{
			static char s_str[64] = {};
			sprintf_s(s_str, "Failure with HRESULT of %08X",
				static_cast<unsigned int>(result));
			return s_str;
		}

	private:
		HRESULT result;
	};

	// Helper utility converts D3D API failures into exceptions.
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw com_exception(hr);
		}
	}
}