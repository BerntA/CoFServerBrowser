//=========      Copyright © 2015, Bernt Andreas Eide, All rights reserved      ============//
//
// Purpose: Handle internal stuff in the application such as UI accessing from external areas, handling of the server browser object, etc. (player details per server)
//
//=========================================================================================//

#include "stdafx.h"
#include "PlayerInfoHandler.h"
#include "ServerBrowserForm.h"
#include "PlayerInfoForm.h"

using namespace CoFServerBrowser;

CPlayerInfoHandler::CPlayerInfoHandler()
{
	pPlayerInfoRequest = NULL;
	m_iPlayersFound = 0;
}

CPlayerInfoHandler::~CPlayerInfoHandler()
{
	// Free us master... Free us...
	if (pPlayerInfoRequest)
	{
		SteamMatchmakingServers()->CancelServerQuery(pPlayerInfoRequest);
		pPlayerInfoRequest = NULL;
	}
}

void CPlayerInfoHandler::AddPlayerToList(const char *pchName, int nScore, float flTimePlayed)
{
	m_iPlayersFound++;
	PlayerInfoForm::playerInfoForm->AddPlayerInfo(pchName, nScore, flTimePlayed);
}

void CPlayerInfoHandler::PlayersFailedToRespond()
{
}

void CPlayerInfoHandler::PlayersRefreshComplete()
{
	if (m_iPlayersFound == 0)
		PlayerInfoForm::playerInfoForm->Text = "Player Info - No players active!";
	else if (m_iPlayersFound == 1)
		PlayerInfoForm::playerInfoForm->Text = "Player Info - 1 player active!";
	else
	{
		char szPlayers[80];
		_snprintf_s(szPlayers, 80, "Player Info - %i players active!", m_iPlayersFound);
		System::String ^playersActive = gcnew String(szPlayers);
		PlayerInfoForm::playerInfoForm->Text = playersActive;
	}
}

void CPlayerInfoHandler::RefreshPlayerInfo(uint32 ip, uint16 port)
{
	if (pPlayerInfoRequest)
	{
		SteamMatchmakingServers()->CancelServerQuery(pPlayerInfoRequest);
		pPlayerInfoRequest = NULL;
	}

	m_iPlayersFound = 0;
	PlayerInfoForm::playerInfoForm->Text = "Player Info - Searching...";

	pPlayerInfoRequest = SteamMatchmakingServers()->PlayerDetails(ip, port, this);
}