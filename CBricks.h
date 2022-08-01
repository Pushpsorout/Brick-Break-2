///////////////////////////////////////////////////////////////////////////////
/// File:    CBricks.h
/// Purpose: Declaration of CBricks Class
///          This class represents the bricks for the game.
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

#ifndef CBRICKS_H_
#define CBRICKS_H_

/// HEADER DEFINES ////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN


/// HEADER FILE INCLUDES //////////////////////////////////////////////////////
#include <windows.h>
#include <windowsx.h>
#include <fstream>

using std::ofstream;

/// CONSTANTS /////////////////////////////////////////////////////////////////
const int DEFAULT_BRICK_START_X   = 28;
const int DEFAULT_BRICK_START_Y   = 79;
const int DEFAULT_BRICK_WIDTH     = 60;
const int DEFAULT_BRICK_HEIGHT    = 25;
const int DEFAULT_BRICK_HOR_SPACE = 2;
const int DEFAULT_BRICK_VER_SPACE = 2;
const int DEFAULT_BRICK_ROWS      = 8;
const int DEFAULT_BRICK_COLS      = 12;

enum EBrickState {BS_NORMAL, BS_HIT, BS_SKIP};

/// TYPE / CLASS DECLARATIONS /////////////////////////////////////////////////
struct TBrick
{
    DWORD       color;
    RECT        rect;
    EBrickState state;
	int         point_value;
	int         reflect_vel;
	int         row;
	int         col;
};

class CBricks
{
private:

    int m_start_x;          /** x coordinate of top-left corner of first brick **/
    int m_start_y;          /** y coordinate of top-left corner of first brick **/

    int m_brick_width;      /** width (in pixels) of each brick **/
    int m_brick_height;     /** height (in pixels) of each brick **/
    int m_brick_hor_space;  /** horizontal space (in pixels) between brick rows **/
    int m_brick_ver_space;  /** vertical space (in pixels) between brick cols **/
	int m_brick_bottom;     /** y coordinate of last row of bricks **/

    int m_num_rows;         /** number of brick rows **/
    int m_num_cols;         /** number of brick columns per row **/
	DWORD* m_row_colors;    /** dynamic array of colors for rows **/
	int*   m_row_points;    /** dynamic array of points for rows **/
	int*   m_row_vel;       /** dynamic array of reflection velocity for rows **/

    TBrick* m_bricks;       /** dynamically allocated array of bricks **/

	int m_brick_cnt;
    int m_bricks_remaining; /** number of bricks left to be hit **/

	

public:

    // constructor
    CBricks();

    // destructor
    ~CBricks();    

    // member functions
	TBrick GetBrick(const int p_brick_no);
	int  GetBrickCount();
	int  GetBricksRemaining();
	void SetBrickProperties(const int p_width, const int p_height, const int p_h_space, const int p_v_space);
	void SetBrickState(const int p_row, const int p_col, const EBrickState p_state);
	void SetRowColProperties(const int p_rows, const int p_cols, DWORD* p_row_colors, int* p_row_points, int* p_row_vel);
    void SetTopLeftPosition(const int p_x, const int p_y);
	
	bool IsBrickAtPosition(const int p_x, const int p_y, TBrick* p_brick);
	void InitializeBricks();


};

#endif
