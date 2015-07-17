//=========      Copyright © 2015, Bernt Andreas Eide, All rights reserved      ============//
//
// Purpose: Handle internal stuff in the application such as UI accessing from external areas, handling of the server browser object, etc. (player details per server)
//
//=========================================================================================//

#include "steam_api.h"

#ifndef PLAYER_INFO_HANDLER_H
#define PLAYER_INFO_HANDLER_H
#ifdef _WIN32
#pragma once
#endif

class CPlayerInfoHandler : public ISteamMatchmakingPlayersResponse
{
public:
	CPlayerInfoHandler();
	virtual ~CPlayerInfoHandler();

	void AddPlayerToList(const char *pchName, int nScore, float flTimePlayed);
	void PlayersFailedToRespond();
	void PlayersRefreshComplete();
	void RefreshPlayerInfo(uint32 ip, uint16 port);

private:
	HServerQuery pPlayerInfoRequest;
	int m_iPlayersFound;
};

#endif // PLAYER_INFO_HANDLER_H