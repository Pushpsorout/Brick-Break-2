///////////////////////////////////////////////////////////////////////////////
/// File:    CBall.h
/// Purpose: Declaration of CBalls Class
///          This class represents the balls (free and captive) during the
///          life of the game
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

#ifndef CBALL_H_
#define CBALL_H_

/// HEADER DEFINES ////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

/// CONSTANTS /////////////////////////////////////////////////////////////////
const int BALL_WIDTH  = 10;
const int BALL_HEIGHT = 10;


/// TYPE / CLASS DECLARATIONS /////////////////////////////////////////////////
enum EBallState {IDLE, FREE, CAPTIVE, LOST};

class CBall
{

private:


    int  m_x_pos;     /// current X position of the top left corner of the ball
    int  m_y_pos;     /// current Y position of the top left corner of the ball
    int  m_x_vel;     /// number of pixels ball will travel in X direction each frame
    int  m_y_vel;     /// number of pixels ball will travel in Y direction each frame
	int  m_vel_multi; /// velocity multiplier

	RECT m_captive_rect; /// only set for ball with m_state = CAPTIVE

	EBallState m_state;  /// current state of the ball

public:

    // constructor
	CBall();

    // destructor
	~CBall();

    // member functions
	int GetXPos();
	int GetYPos();
	int GetXVel();
	int GetYVel();
	int GetVelMultiplier();
	RECT  GetCaptiveRect();
	RECT  GetBallRect();
	EBallState GetState();

	void SetXPos(const int p_x);
	void SetYPos(const int p_y);
	void SetXYPos(const int p_x, const int p_y);
	void SetXVel(const int p_x_vel);
	void SetYVel(const int p_y_vel);
	void SetState(const EBallState p_state);
	void SetVelMultiplier(const int p_vel_multi);
	void SetCaptiveRect(const RECT p_rect);

	void ReflectX();
	void ReflectY();

};

#endif
