///////////////////////////////////////////////////////////////////////////////
/// File:    CBricks.cpp
/// Purpose: Definition of CBricks Class Members
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


/// HEADER FILE INCLUDES //////////////////////////////////////////////////////
#include "CBricks.h"


///////////////////////////////////////////////////////////////////////////////
/// Method:  CBricks --> default constructor
/// Purpose: Initialize member variables
///////////////////////////////////////////////////////////////////////////////
/// Receives: nothing
/// Returns:  nothing
///////////////////////////////////////////////////////////////////////////////
CBricks::CBricks()
{
	m_start_x = 0;
	m_start_y = 0;

	m_brick_width = 0;
	m_brick_height = 0;
	m_brick_hor_space = 0;
	m_brick_ver_space = 0;

	m_num_rows = 0;
	m_num_cols = 0;

	m_bricks_remaining = 0;

	m_row_colors = NULL;
	m_row_points = NULL;
	m_row_vel = NULL;
	m_bricks = NULL;

	return;
}

///////////////////////////////////////////////////////////////////////////////
/// Method:  ~CBricks --> default destructor
/// Purpose: Deallocate member variables
///////////////////////////////////////////////////////////////////////////////
/// Receives: nothing
/// Returns:  nothing
///////////////////////////////////////////////////////////////////////////////
CBricks::~CBricks()
{
	delete[] m_row_colors;
	delete[] m_row_points;
	delete[] m_row_vel;
	delete[] m_bricks;

	return;
}

///////////////////////////////////////////////////////////////////////////////
/// Method:  GetBrick
/// Purpose: Retrieve the specified brick
///////////////////////////////////////////////////////////////////////////////
/// Receives: Brick Number (row * col) + col
/// Returns:  Brick struct
///////////////////////////////////////////////////////////////////////////////
TBrick CBricks::GetBrick(const int p_brick_no)
{
	return(m_bricks[p_brick_no]);
}

///////////////////////////////////////////////////////////////////////////////
/// Method:  GetBrickCount
/// Purpose: Retrieve the total number of bricks in the array
///////////////////////////////////////////////////////////////////////////////
/// Receives: nothing
/// Returns:  count of bricks
///////////////////////////////////////////////////////////////////////////////
int CBricks::GetBrickCount()
{
	return(m_brick_cnt);
}

///////////////////////////////////////////////////////////////////////////////
/// Method:  GetBricksRemaining
/// Purpose: Retrieve the count of bricks still in play (state == BS NORMAL)
///////////////////////////////////////////////////////////////////////////////
/// Receives: nothing
/// Returns:  count of brick remaining
///////////////////////////////////////////////////////////////////////////////
int CBricks::GetBricksRemaining()
{
	return(m_bricks_remaining);
}

///////////////////////////////////////////////////////////////////////////////
/// Method:  InitializeBricks
/// Purpose: Based on the brick properties, intialize each structure in the
///          bricks array.
///////////////////////////////////////////////////////////////////////////////
/// Receives: nothing
/// Returns:  nothing
///////////////////////////////////////////////////////////////////////////////
void CBricks::InitializeBricks()
{
	m_brick_cnt = m_num_rows * m_num_cols;
	m_bricks_remaining = m_brick_cnt;

	m_brick_bottom = m_start_y + (m_num_rows * (m_brick_height + m_brick_ver_space));

	if (m_bricks)
	{
		delete[] m_bricks;
	}
	m_bricks = new TBrick[m_bricks_remaining];

	for (int r = 0; r < m_num_rows; r++)
	{
		for (int c = 0; c < m_num_cols; c++)
		{
			int l_brick = ((r * m_num_cols) + c);

			m_bricks[l_brick].color = m_row_colors[r];

			m_bricks[l_brick].point_value = m_row_points[r];

			m_bricks[l_brick].reflect_vel = m_row_vel[r];

			m_bricks[l_brick].rect.left = m_start_x + (c * (m_brick_width + m_brick_ver_space));
			m_bricks[l_brick].rect.top = m_start_y + (r * (m_brick_height + m_brick_ver_space));
			m_bricks[l_brick].rect.right = m_bricks[l_brick].rect.left + m_brick_width;
			m_bricks[l_brick].rect.bottom = m_bricks[l_brick].rect.top + m_brick_height; 
            m_bricks[l_brick].row = r + 1;
			m_bricks[l_brick].col = c + 1;

			m_bricks[l_brick].state = BS_NORMAL;
		}
	}

	return;
}

///////////////////////////////////////////////////////////////////////////////
/// Method:  IsBrickAtPosition
/// Purpose: Determine if a brick is at the specified X,Y position
///////////////////////////////////////////////////////////////////////////////
/// Receives: X coordinate of search
///           Y coordinate of search
///           pointer to brick structure (to hold brick data if found at position)
/// Returns:  true if brick exists at specified X,Y location, otherwise false
///////////////////////////////////////////////////////////////////////////////
bool CBricks::IsBrickAtPosition(const int p_x, const int p_y, TBrick* p_brick)
{
	///////////////////////////////////////////////////////////////////////////
	/// immediately return false is y coordinate is above or below
	/// the entire set of bricks
	///////////////////////////////////////////////////////////////////////////
	if ( (p_y < m_start_y) || (p_y > m_brick_bottom) )
	{
		return(false);
	}

	///////////////////////////////////////////////////////////////////////////
	/// calculate the row and (including the vertical and horizontal
	/// space between the bricks) for the specified position
	///////////////////////////////////////////////////////////////////////////
	int l_row = 0;
    int l_col = 0;
	l_row = (p_y - m_start_y) / (m_brick_height + m_brick_ver_space);
	l_col = (p_x - m_start_x) / (m_brick_width + m_brick_hor_space);

	///////////////////////////////////////////////////////////////////////////
	/// if the calculated column and row is valid (ie. it should exist) then
	/// set the brick byref return values
	///////////////////////////////////////////////////////////////////////////
	if (( (l_row < m_num_rows) && (l_row >= 0) )
	&&  ( (l_col < m_num_cols) && (l_col >= 0) ))
	{
		int l_brick_num = ((l_row * m_num_cols) + l_col);
		*p_brick = m_bricks[l_brick_num];

		return(true);
	}

	return(false);
}



///////////////////////////////////////////////////////////////////////////////
/// Method:  SetTopLeftPosition
/// Purpose: Initialize the starting point of the bricks in the 
///          playing area
///////////////////////////////////////////////////////////////////////////////
/// Receives: - X coordinate (in pixels) of top left corner of starting brick
///           - Y coordinate (in pixels) of top left corner of starting brick
/// Returns:  nothing
///////////////////////////////////////////////////////////////////////////////
void CBricks::SetTopLeftPosition(const int p_x, const int p_y)
{
	m_start_x = p_x;
	m_start_y = p_y;

	return;
}

///////////////////////////////////////////////////////////////////////////////
/// Method:  SetBrickProperties
/// Purpose: Initialize the properties that describe the size of each brick
///////////////////////////////////////////////////////////////////////////////
/// Receives: - width (in pixels) of each brick
///           - height (in pixels) of each brick
///           - horizontal space (in pixels) between each column of bricks
///           - vertical space (in pixels) between each row of bricks
/// Returns:  nothing
///////////////////////////////////////////////////////////////////////////////
void CBricks::SetBrickProperties(const int p_width, const int p_height, const int p_h_space, const int p_v_space)
{
    m_brick_width = p_width;
	m_brick_height = p_height;
	m_brick_hor_space = p_h_space;
	m_brick_ver_space = p_v_space;

	return;
}

///////////////////////////////////////////////////////////////////////////////
/// Method:  SetBrickState
/// Purpose: Set the state of the passed brick
///////////////////////////////////////////////////////////////////////////////
/// Receives: - ???
/// Returns:  nothing
///////////////////////////////////////////////////////////////////////////////
void CBricks::SetBrickState(const int p_row, const int p_col, const EBrickState p_state)
{
	int l_brick = ((p_row - 1) * m_num_cols) + (p_col - 1);

	m_bricks[l_brick].state = p_state;

	if ((p_state == BS_HIT) || (p_state == BS_SKIP))
	{
		m_bricks_remaining--;
	}

    return;
}

///////////////////////////////////////////////////////////////////////////////
/// Method:  SetRowColProperties
/// Purpose: Initialize the number of rows and columns.  Also set the colors
///          for each row
///////////////////////////////////////////////////////////////////////////////
/// Receives: - number of rows of bricks to create
///           - number of columns of bricks to create
///           - DWORD pointer containing the colors for each row of bricks
/// Returns:  nothing
///////////////////////////////////////////////////////////////////////////////
void CBricks::SetRowColProperties(const int p_rows, const int p_cols, DWORD* p_row_colors, int* p_row_points, int* p_row_vel)
{
	m_num_rows = p_rows;
	m_num_cols = p_cols;

	if (m_row_colors)
	{
		delete[] m_row_colors;
	}

	if (m_row_points)
	{
		delete[] m_row_points;
	}

	if (m_row_vel)
	{
		delete[] m_row_vel;
	}

	m_row_colors = new DWORD[p_rows];
	m_row_points = new int[p_rows];
	m_row_vel    = new int[p_rows];

	for (int i = 0; i < p_rows; i++)
	{
		m_row_colors[i] = p_row_colors[i];
		m_row_points[i] = p_row_points[i];
		m_row_vel[i]    = p_row_vel[i];
	}

	return;
}

/// END OF FILE ///////////////////////////////////////////////////////////////