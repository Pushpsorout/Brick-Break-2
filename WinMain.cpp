///////////////////////////////////////////////////////////////////////////////
/// File:    WinMain.cpp
/// Purpose: Application entry point and main processing loop
///////////////////////////////////////////////////////////////////////////////
/// Configuation Management
/// 
/// Who         When          Description
/// ===========================================================================
/// R. Walter   28-Dec-2003   Initial Version/Release
///
///////////////////////////////////////////////////////////////////////////////
/// Copyright 2003: Robert Walter   All rights reserved
///////////////////////////////////////////////////////////////////////////////

/// APPLICATION DEFINES ///////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN /** no MFC **/
#define INITGUID


/// HEADER FILE INCLUDES //////////////////////////////////////////////////////
#include <windows.h>
#include <windowsx.h>

#include "CSuperBrickBreaker.h"



/// CONSTANTS /////////////////////////////////////////////////////////////////
const char* WIN_CLASS_NM = "WINCLASSNAME";
const char* WINDOW_NM    = "WINDOWNAME";

const DWORD SCREEN_HEIGHT = 600;
const DWORD SCREEN_WIDTH  = 800;
const DWORD SCREEN_BPP    = 16;
const DWORD FRAME_RATE    = 20;

const int FAILED_REG_CLASS  = 1;
const int FAILED_WIN_CREATE = 2;
const int FAILED_DD_INIT    = 3;
const int FAILED_DI_INIT    = 4;
const int FAILED_DS_INIT    = 5;
const int FAILED_GAME_INIT  = 6;
const int FAILED_GAME_MAIN  = 7;


/// TYPE DEFINITIONS //////////////////////////////////////////////////////////



/// FUNCTION PROTOTYPES ///////////////////////////////////////////////////////
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


/// GLOBAL VARIABLES //////////////////////////////////////////////////////////
HWND gbl_main_hwnd;



/// APPLICATION ENTRY POINT ///////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // initialize and register main window class
    WNDCLASSEX l_winclass;

    l_winclass.cbClsExtra = 0;
    l_winclass.cbSize = sizeof(WNDCLASSEX);
    l_winclass.cbWndExtra = 0;
    l_winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    l_winclass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
    l_winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    l_winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    l_winclass.hInstance = hInstance;
    l_winclass.lpfnWndProc = MainWndProc;
    l_winclass.lpszClassName = WIN_CLASS_NM;
    l_winclass.lpszMenuName = NULL;
    l_winclass.style = CS_OWNDC;

    if (!RegisterClassEx(&l_winclass))
    {
        return(FAILED_REG_CLASS);
    }

    // create main window based on registered class
    gbl_main_hwnd = CreateWindowEx
                    (
                        NULL,                  // dwExStyle    -- extended window style
                        WIN_CLASS_NM,          // lpClassName  -- pointer to registered class name
                        WINDOW_NM,             // lpWindowName -- pointer to window name (caption)
                        WS_POPUP | WS_VISIBLE, // dwStyle      -- window style
                        0,                     // x            -- x position of window on screen
                        0,                     // y            -- y position of window on screen
                        SCREEN_WIDTH,          // nWidth       -- window width
                        SCREEN_HEIGHT,         // nHeight      -- window height
                        NULL,                  // hWndParent   -- handle to parent window
                        NULL,                  // hMenu        -- handle to window menu
                        hInstance,             // hInstance    -- handle to this application instance
                        NULL                   // lpParam      -- pointer to window creation data
                    );
    if (!gbl_main_hwnd)
    {
        return(FAILED_WIN_CREATE);
    }

    /// declare main game class to be used for this application ///////////////
    CSuperBrickBreaker l_game;

	/// initialize DirectDraw /////////////////////////////////////////////////

	// set the screen properties
	l_game.SetScreenProperties
	(
	    /* screen width */  SCREEN_WIDTH,
		/* screen height */ SCREEN_HEIGHT,
		/* screen bpp */    SCREEN_BPP
	);

	// set the frame rate for the game
	l_game.SetFrameRate(/* frame rate */ 10);

	// set the application instance
	l_game.SetApplicationInstance(/* app instance */ hInstance);

	// set the main window handle
	l_game.SetWindowHandle(/* window handle */ gbl_main_hwnd);

	ShowCursor(FALSE);

	// initialize DirectDraw
	if (!l_game.InitializeDirectDraw())
	{
		return(FAILED_DD_INIT);
	}

	/// initialize DirectInput ////////////////////////////////////////////
    if (!l_game.InitializeDirectInput())
	{
		return(FAILED_DI_INIT);
	}

	/// initialize game objects////////////////////////////////////////////
	if (!l_game.GameInitialize())
	{
	    return(FAILED_GAME_INIT);
	}

	/// main windows message loop /////////////////////////////////////////
	MSG msg;

	while (true)
	{
		// capture the start of this frame
		l_game.FrameRateStart();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// process the next frame in the game
		if (!l_game.GameMain())
		{
			return(FAILED_GAME_MAIN);
		}

		// lock the frame rate
		l_game.FrameRateEnd();
	}

	/// shutdown game objects//////////////////////////////////////////////////
	l_game.GameShutdown();

	ShowCursor(TRUE);

    return(msg.wParam);
}



/// FUNCTION DEFINITIONS //////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Function: MainWndProc
/// Purpose:  Message handling function for the main window
///////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch(msg)
    {
    case WM_CREATE:
        {
            // tell windows we handled the message
            // simply by returning zero
            return(0);
        } break;

    case WM_PAINT:
        {
            // tell windows we handled the message
            // by validating the window
            PAINTSTRUCT ps;
            HDC         hdc;

            hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);

            return(0);
        } break;

    case WM_DESTROY:
        {
            // send quit message to application
            PostQuitMessage(0);
            return(0);
        } break;

    default: return DefWindowProc(hwnd, msg, wparam, lparam);

    };
}

/// END OF FILE ///////////////////////////////////////////////////////////////
