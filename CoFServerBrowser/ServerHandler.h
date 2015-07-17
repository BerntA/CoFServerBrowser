//=========      Copyright © 2015, Bernt Andreas Eide, All rights reserved      ============//
//
// Purpose: Handle internal stuff in the application such as UI accessing from external areas, handling of the server browser object, etc.
//
//=========================================================================================//

#include "steam_api.h"

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H
#ifdef _WIN32
#pragma once
#endif

class CServerHandler : public ISteamMatchmakingServerListResponse
{
public:
	CServerHandler();
	virtual ~CServerHandler();

	// Server Response
	void ServerResponded(HServerListRequest hRequest, int iServer);
	void ServerFailedToRespond(HServerListRequest hRequest, int iServer);
	void RefreshComplete(HServerListRequest hRequest, EMatchMakingServerResponse response);
	bool RefreshInternetServers(void);

	bool IsBusy() { return m_bIsSearching; }

private:
	HServerListRequest pServerRequest;
	int m_iServersFound;
	bool m_bIsSearching;
};

#endif // SERVER_HANDLER_H