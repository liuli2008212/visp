/****************************************************************************
 *
 * $Id: vpDisplayWin32.h,v 1.22 2008-12-03 10:25:11 nmelchio Exp $
 *
 * Copyright (C) 1998-2006 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE included in the packaging of this file.
 *
 * Licensees holding valid ViSP Professional Edition licenses may
 * use this file in accordance with the ViSP Commercial License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact visp@irisa.fr if any conditions of this licensing are
 * not clear to you.
 *
 * Description:
 * Windows 32 display base class
 *
 * Authors:
 * Bruno Renier
 *
 *****************************************************************************/

#include <visp/vpConfig.h>

#if ( defined(WIN32) )

#ifndef vpDisplayWin32_hh
#define vpDisplayWin32_hh

#include <visp/vpImage.h>
#include <visp/vpDisplay.h>
#include <windows.h>
#include <visp/vpWin32Window.h>
#include <visp/vpWin32Renderer.h>
#include <visp/vpRect.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*!
  Used to pass parameters to the window's thread.
*/
struct threadParam
{
  //! Pointer to the display associated with the window.
  vpDisplayWin32 * vpDisp;

  //! X position of the window.
  int x;

  //! Y position of the window.
  int y;

  //! Width of the window's client area.
  unsigned int w;

  //! Height of the window's client area.
  unsigned int h;

  //! Title of the window.
  char * title;
};
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/*!
  \class vpDisplayWin32

  \brief Base abstract class for Windows 32 displays.
  Implements the window creation in a separate thread
  and the associated event handling functions for
  Windows 32 displays.
  Uses calls to a renderer to do some display.
  (i.e. all display methods are implemented in the renderer)

  \author Bruno Renier
*/
class VISP_EXPORT vpDisplayWin32 : public vpDisplay
{
 protected:
  //! Maximum delay for window initialization
  static const int MAX_INIT_DELAY;

  //! Handle of the window's thread.
  HANDLE hThread;

  //! Id of the window's thread.
  DWORD threadId;

  //! Initialization status.
  bool iStatus;

  //! The window.
  vpWin32Window window;

  //! Function used to launch the window in a thread.
  friend void vpCreateWindow(threadParam * param);

 public:

  vpDisplayWin32(vpWin32Renderer * rend = NULL);

  vpDisplayWin32(vpImage<vpRGBa> &I,
		 int winx=-1, int winy=-1,
		 const char *title=NULL);

  vpDisplayWin32(vpImage<unsigned char> &I,
		 int winx=-1, int winy=-1,
		 const char *title=NULL);

  virtual ~vpDisplayWin32();

  //! Clears the whole window
  void clearDisplay(vpColor::vpColorType c=vpColor::white);
  //! Closes the display
  void closeDisplay();
  //! Displays a 8bits image
  void displayImage(const vpImage<vpRGBa> &I);
  //! Displays a 32 bits image
  void displayImage(const vpImage<unsigned char> &I);

  //! Flush the Display
  void flushDisplay();
  // Changes the window's title
  void setTitle(const char *windowtitle);
  //Sets the font used while displaying a text in an image
  void setFont( const char *fontname );
  //! Gets the window pixmap and put it in vpRGBa image
  void getImage(vpImage<vpRGBa> &I);


  //! Initialization function
  void init(vpImage<unsigned char> &I,
	    int winx=-1, int winy=-1,
	    const char *title=NULL)  ;

  //! Initialization function
  void init(vpImage<vpRGBa> &I,
	    int winx=-1, int winy=-1,
	    const char *title=NULL)  ;

  //! Initialization function
  void init(unsigned int width, unsigned int height,
	    int winx=-1, int winy=-1 ,
	    const char *title=NULL) ;

  //! Sets the window's position
  void setWindowPosition(int winx, int winy);

 protected:

  //! Display an arrow from coordinates (i1,j1) to (i2,j2) in the display
  //! window
  void displayArrow(int i1, int j1, int i2, int j2,
		    vpColor::vpColorType col=vpColor::white,
		    unsigned int L=4,unsigned int l=2);
  void displayCharString(int i, int j,const char *s,
			 vpColor::vpColorType c=vpColor::green);
  //! Display a circle at coordinates (i,j) in the display window.
  void displayCircle(int i, int j, unsigned int r,
		     vpColor::vpColorType c);

  //! Display a cross at coordinates (i,j) in the display window
  void displayCross(int i, int j, unsigned int size,
		    vpColor::vpColorType col);
  //! Display a large cross at coordinates (i,j) in the display window
  void displayCrossLarge(int i, int j, unsigned int size,
			 vpColor::vpColorType col);
  //! Display a dotted line from coordinates (i1,j1) to (i2,j2) in the display
  //! window.
  void displayDotLine(int i1, int j1, int i2, int j2,
		      vpColor::vpColorType col, unsigned int e=1);

  //! Display a line from coordinates (i1,j1) to (i2,j2) in the display window.
  void displayLine(int i1, int j1, int i2, int j2,
		   vpColor::vpColorType col, unsigned int e=1);


  //! Display a point at coordinates (i,j) in the display window
  void displayPoint(int i, int j, vpColor::vpColorType col);

  void displayRectangle(int i, int j,
			unsigned int width, unsigned int height,
			vpColor::vpColorType col, bool fill = false,
			unsigned int e=1);
  void displayRectangle(const vpRect &rect,
			vpColor::vpColorType col, bool fill = false,
			unsigned int e=1);

  //! wait for a click
  bool getClick( bool blocking=true);

  bool getClick(unsigned int& i, unsigned int& j, bool blocking=true);

  //!  return true when button is pressed
  bool getClick(unsigned int& i, unsigned int& j,
		vpMouseButton::vpMouseButtonType& button, bool blocking=true);

  //! return true when  button is released
  bool getClickUp(unsigned int& i, unsigned int& j,
		  vpMouseButton::vpMouseButtonType& button,
		  bool blocking=true);


  //! Used to wait for the window to be initialized
  void waitForInit();

 public:
  /*!
    @name Deprecated functions
  */
  //! Changes the window's title
  void flushTitle(const char *string);
};
#endif
#endif
