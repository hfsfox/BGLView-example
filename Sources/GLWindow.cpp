/*
 * GLWindow.cpp
 * Copyright 2024 HFS.Fox. All rights reserved.
 * Distributed under the terms of the MIT License.
*/

#include "GLWindow.h"
#include <assert.h>

#include <stdio.h>

#include <Catalog.h>
#include <LayoutBuilder.h>
#include <Menu.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <Message.h>
#include <Point.h>
#include <Screen.h>

#include <private/interface/AboutWindow.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "GLWindow"

BMenuBar*
MainWindow::_BuildMenuBar()
{
	BMenuBar* fMenuBar = new BMenuBar("menu");

	BMenu* fileMenu = new BMenu("File");
	fileMenu->AddItem(new BMenuItem(B_TRANSLATE("Quit"), new BMessage(B_QUIT_REQUESTED), 'Q'));

	BMenu* helpMenu = new BMenu(B_TRANSLATE("Help"));
	helpMenu->AddItem(new BMenuItem(B_TRANSLATE("About"), new BMessage(B_ABOUT_REQUESTED)));
	
	fMenuBar->AddItem(fileMenu);
	fMenuBar->AddItem(helpMenu);
	
	SetKeyMenuBar(fMenuBar);
	
	return fMenuBar;
}

MainWindow::MainWindow(BRect frame, const char* title)
	:
	BWindow(frame, title, B_TITLED_WINDOW,B_ASYNCHRONOUS_CONTROLS | B_AUTO_UPDATE_SIZE_LIMITS, B_CURRENT_WORKSPACE)
{
	BMessenger msgr(NULL, this);
	GLView* fGLView = new GLView(Bounds(), "gl_view", B_FOLLOW_ALL_SIDES, B_WILL_DRAW, BGL_RGB);

	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.Add(_BuildMenuBar())
		.Add(fGLView)
	.End();
	SetPulseRate(1000000);
	CenterOnScreen();
}

MainWindow::~MainWindow()
{
}

void
MainWindow::SetTitle(const char* title)
{
}

bool
MainWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}

void
MainWindow::AboutRequested()
{
	BAboutWindow* about = new BAboutWindow("GLView", "application/x-vnd.hfsfox-bglview");
	about->AddCopyright(2024, B_TRANSLATE("HFS.Fox"));
	about->AddExtraInfo(B_TRANSLATE("Simple native OpenGL view"));
	about->Show();
}

void
MainWindow::MessageReceived(BMessage* message) 
{
	
		switch (message->what) {
			case B_REFS_RECEIVED:{
				case B_SIMPLE_DATA:{
					status_t status = B_MESSAGE_NOT_UNDERSTOOD;
					}
				message->PrintToStream();
			}
			break;
			case B_ABOUT_REQUESTED:
				AboutRequested();
				break;
			default:
				BWindow::MessageReceived(message);
		}
	}


void
MainWindow::RefsReceived(BMessage* message)
{
}

GLView::GLView(BRect r, char *name, ulong resizingMode, ulong options, uint32 type)
 	:
 	BGLView(r, "GLView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW, type)
{
	LockGL();
	r = Bounds();
	glViewport(0, 0, r.Width(), r.Height());
	clearScreen();
	UnlockGL();
	FrameResized(r.Width(), r.Height());
	
	assert(glGetError() == GL_NO_ERROR);
}

void
GLView::AttachedToWindow()
{
	LockGL();
	BRect	r = Bounds();
	GLint	size = r.Height() + 1;
	GLint	offs = (r.Width() + 1 - size) / 2;
	glEnable(GL_DEPTH_TEST);
	glViewport(offs, 0, r.Width(), r.Height());
	clearScreen();
	
	UnlockGL();
	
	assert(glGetError() == GL_NO_ERROR);
}

void
GLView::FrameResized(float Width, float Height)
{
	LockGL();
	glLoadIdentity();
	BGLView::FrameResized(Width, Height);
	BRect rect = Bounds();
	glViewport(0, 0, rect.Width(), rect.Height());
	clearScreen();
	drawTriangle(rect.Width(), rect.Height());
	glLoadIdentity();
	UnlockGL();
	
	assert(glGetError() == GL_NO_ERROR);
}

void
GLView::clearScreen()
{
	glLoadIdentity();
	glClearColor(0.165,0.165,0.165,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawBuffer(GL_BACK);
	glCullFace(GL_BACK);
	glLoadIdentity();
	
	assert(glGetError() == GL_NO_ERROR);
}

void
GLView::drawTriangle(float Width, float Height)
{
	glBegin(GL_POLYGON);

	//triangle
	glColor3f( 1, 0, 0 ); // red
	glVertex2f( -0.8, -0.8 );
	glColor3f( 0, 1, 0 ); // green
	glVertex2f( 0.8, -0.8 );
	glColor3f( 0, 0, 1 ); // blue
	glVertex2f( 0, 0.9 );
	
	glEnd();
	
	assert(glGetError() == GL_NO_ERROR);
}

