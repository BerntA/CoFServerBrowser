//=========      Copyright © 2015, Bernt Andreas Eide, All rights reserved      ============//
//
// Purpose: Handle internal stuff in the application such as UI accessing from external areas, handling of the server browser object, etc.
//
//=========================================================================================//

#include "steam_api.h"
#include "fmod_manager.h"

#ifndef CLIENT_MODE_H
#define CLIENT_MODE_H
#ifdef _WIN32
#pragma once
#endif

class IClientMode
{
public:

	// Base
	virtual void Init(void) = 0;
	virtual void Shutdown(void) = 0;
	virtual void ExitApplication(void) = 0;
	virtual void RunProgram(const char *ip = NULL) = 0;
	virtual void StartMainForm(bool bValue) = 0;
	virtual bool IsWideScreen(long wide, long tall) = 0;

	// Server Browser Definitions:
	virtual void RequestServerList(void) = 0;
	virtual void RequestPlayerInfo(uint32 ip, uint16 port) = 0;

	char *GetStartupPath() { return szStartupPath; }

protected:
	char szStartupPath[200];
};

extern IClientMode *ClientMode;

#endif // CLIENT_MODE_H