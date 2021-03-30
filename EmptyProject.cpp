 //--------------------------------------------------------------------------------------
// File: EmptyProject.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"

#include "resource.h"

// ---- 1. Setting 이후 ----
#include "header.hpp"
#include "Event.hpp"

// ---- 2. Input & Object 이후 ----
#include "Game.hpp"
#include "InputManager.hpp"

#include "SceneStateMachine.hpp"

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
CDXUTDialogResourceManager	g_dialogResourceManager;
D3DXMATRIXA16               g_matrix;

LPD3DXSPRITE                g_sprite;
LPD3DXLINE                  g_pLine;

namespace
{
    std::unique_ptr<Game>       g_game;
}

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}

//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    HRESULT hr = S_OK;
    V_RETURN(g_dialogResourceManager.OnD3D9CreateDevice(pd3dDevice));

    V_RETURN(D3DXCreateSprite(pd3dDevice, &g_sprite));
    V_RETURN(D3DXCreateLine(pd3dDevice, &g_pLine));

    g_game->OnCreateDevice();
    g_inputManager->Initialize();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    HRESULT hr;

    V_RETURN(g_dialogResourceManager.OnD3D9ResetDevice());

    g_sprite->OnResetDevice();
    g_pLine->OnResetDevice();

    g_game->OnResetDevice();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
    g_game->OnUpdate(fElapsedTime);
    g_game->OnLateUpdate(fElapsedTime);

    g_inputManager->KeyBoardUpdate();
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 96, 155, 125 ), 1.0f, 0 ) );
    float windowWidth = static_cast<float>(DXUTGetWindowWidth());
    float windowHeight = static_cast<float>(DXUTGetWindowHeight());

    D3DXMATRIX worldMatrix;
    D3DXVECTOR2 transfrom(0.0f, 0.0f);
    D3DXVECTOR2 scale(1.0f, 1.0f);
    D3DXMatrixIdentity(&worldMatrix);
    D3DXMatrixTransformation2D(&worldMatrix, nullptr, 0.0f, &scale, nullptr, 0.0f, &transfrom);

    D3DXMatrixIdentity(&g_matrix);
    D3DXMatrixOrthoLH(&g_matrix, windowWidth, windowHeight * -1.0f, -1.0f, 1.0f);
    g_matrix = worldMatrix * g_matrix;

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        g_sprite->SetTransform(&worldMatrix);
        g_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

        g_pLine->SetAntialias(false);
        g_pLine->SetWidth(1.0f);

        //g_createTexture->Draw();
        // ------- Game -------
        g_game->OnRender(fElapsedTime);
        // --------------------

        g_sprite->End();

        g_game->OnUIRender(fElapsedTime);

        V( pd3dDevice->EndScene() );
    }
}

void CALLBACK MouseProc(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
    g_inputManager->OnMouseMove(D3DXVECTOR2(
        static_cast<float>(xPos),
        static_cast<float>(yPos)
    ));
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
    *pbNoFurtherProcessing = g_dialogResourceManager.MsgProc(hWnd, uMsg, wParam, lParam);
    if (*pbNoFurtherProcessing)
        return 0;

    // ------- Game -------
    g_game->MsgProc(hWnd, uMsg, wParam, lParam, pbNoFurtherProcessing, pUserContext);
    // --------------------

    // g_camera.HandleMessages(hWnd, uMsg, wParam, lParam);

    return 0;
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
    g_dialogResourceManager.OnD3D9LostDevice();

    g_sprite->OnLostDevice();

    // ------- Game -------
    g_game->OnLostDevice();
    // --------------------

    g_pLine->OnLostDevice();
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
    g_dialogResourceManager.OnD3D9DestroyDevice();

    g_game->OnDestoryDevice();

    SAFE_RELEASE(g_sprite);
    SAFE_RELEASE(g_pLine);
}

void CALLBACK OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContexts)
{
    switch (static_cast<UI_CONTROL_ID>(nControlID)) {
    case UI_CONTROL_ID::IDC_GAMESTART_BUTTON:
        g_game->ChangeScene(L"MainScene");
        break;
    case UI_CONTROL_ID::IDC_MENU_BUTTON:
        g_game->ChangeScene(L"MenuScene");
        break;
    case UI_CONTROL_ID::IDC_EXIT_BUTTON:
        DXUTShutdown();
        break;
    }
}

//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int ){
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
    // Set the callback functions
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackMouse( MouseProc, true );

    // TODO: Perform any application-level initialization here
    g_game = std::make_unique<Game>();

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
    DXUTInit( true, true ); // Parse the command line and show msgboxes
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"EmptyProject" );
    DXUTCreateDevice( false, 1920, 1080 );

    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here

    return DXUTGetExitCode();
}