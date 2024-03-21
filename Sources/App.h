/*
 * App.h
 * Copyright 2024 HFS.Fox. All rights reserved.
 * Distributed under the terms of the MIT License.
*/

#include <Application.h>

class App : public BApplication {
	public:
		App();
		~App();
		virtual	void				MessageReceived(BMessage* message);
		virtual void				ArgvReceived(int32 argc, char **argv);
		virtual	bool				QuitRequested();
};
