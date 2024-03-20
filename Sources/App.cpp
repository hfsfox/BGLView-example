/*
 * App.cpp
 * Copyright 2024 HFS.Fox. All rights reserved.
 * Distributed under the terms of the MIT License.
*/

#include "App.h"
#include "GLWindow.h"

#include <Catalog.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "App"

void
App::ArgvReceived(int32 argc, char **argv)
{
	
}

void
App::AboutRequested()
{

}

bool
App::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}

void
App::MessageReceived(BMessage* message)
{
	switch (message->what) {
		default:
		BApplication::MessageReceived(message);
		break;
	}
}

App::App()
	:
	BApplication("application/x-vnd.hfsfox-bglview")
{
	BRect frame(0, 0, 320, 310);
	const char *title = B_TRANSLATE_SYSTEM_NAME("GLView");
	MainWindow* fMainWindow = new MainWindow(frame, title);
	fMainWindow->Show();
}

App::~App()
{
}

int
main(int argc, char** argv)
{
	App app;
	return app.Run();
}
