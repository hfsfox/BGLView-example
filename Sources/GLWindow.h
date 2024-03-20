/*
 * GLWindow.h
 * Copyright 2024 HFS.Fox. All rights reserved.
 * Distributed under the terms of the MIT License.
*/

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <GL/glew.h>

#include <Window.h>
#include <Application.h>
#include <GLView.h>

class BMenuBar;
class BPoint;

class MainWindow : public BWindow {
public:
								MainWindow(BRect frame, const char* title);
								~MainWindow();

	virtual	bool				QuitRequested();
	virtual	void				MessageReceived(BMessage* message);
	virtual void				RefsReceived(BMessage* message);
	virtual void				AboutRequested();
	void						SetTitle(const char* title);

private:
			BMenuBar*			_BuildMenuBar(void);

private:
			BMenuBar*			fMenuBar;
};

class GLView : public BGLView
{
	public:
			GLView(BRect r, char *name, ulong resizingMode, ulong options, uint32 type);
	void	AttachedToWindow();
	void	FrameResized(float Width, float Height);
	void	clearScreen();
	void	drawTriangle(float Width, float Height);
};

#endif //_MAINWINDOW_H
