///////////////////////////////////////////////////////////////////////////////
/// File:    CDirectDrawGame.h
/// Purpose: Declaration of CDirectDrawGame Class
///          This class represents the DirectX components required to construct
///          a simple DirectX based game..
///////////////////////////////////////////////////////////////////////////////
/// Configuation Management
/// 
/// Who         When          Description
/// ===========================================================================
///
///
///////////////////////////////////////////////////////////////////////////////

#ifndef CDIRECTDRAWGAME_H_
#define CDIRECTDRAWGAME_H_

/// HEADER DEFINES ////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN
#define INITGUID


/// HEADER FILE INCLUDES //////////////////////////////////////////////////////
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>


/// TYPE / CLASS DECLARATIONS /////////////////////////////////////////////////
class CDirectDrawGame
{
private:

   // initialization flags
   bool m_init_dd_fg;
   bool m_init_di_fg;
   bool m_init_ds_fg;
   
   // DirectDraw member variables
   LPDIRECTDRAW7        m_lpdd7;
   LPDIRECTDRAWSURFACE7 m_lpdds_primary;
   LPDIRECTDRAWSURFACE7 m_lpdds_back;

   HWND m_main_hwnd;
   
   int m_back_buffer_cnt;
   
   DWORD m_screen_width;
   DWORD m_screen_height;
   DWORD m_screen_bpp;
   
   // private member functions
   bool InitializeDirectDraw();
   bool InitializeDirectInput();
   bool InitializeDirectSound();

public:

   // constructors
   CDirectDrawGame();
   
   // destructors
    virtual ~CDirectDrawGame();
   
   
   // member functions
   void SetInitializationProperties(const bool p_init_dd_fg, const bool p_init_di_fg, const bool p_init_ds_fg);

   virtual bool GameInitialize();
   virtual bool GameShutdown();
   virtual bool GameMain();
   
   // DirectDraw member functions
   bool DrawRectangle(const RECT p_rectangle, const DWORD p_color);
   bool DrawText(const RECT p_rectangle, const char* p_text);
   void SetBackBufferCount(const int p_back_buffer_cnt);
   void SetScreenProperties(const DWORD p_screen_width, const DWORD p_screen_height, const DWORD p_screen_bpp);
   void SetWindowHandle(const HWND p_hwnd);
};

#endif   
