//=========      Copyright © 2015, Bernt Andreas Eide, All rights reserved      ============//
//
// Purpose: Handle internal stuff in the application such as UI accessing from external areas, handling of the server browser object, etc.
//
//=========================================================================================//

#include "stdafx.h"
#include "ServerHandler.h"
#include "ServerBrowserForm.h"

using namespace CoFServerBrowser;

CServerHandler::CServerHandler()
{
	pServerRequest = NULL;
	m_iServersFound = 0;
	m_bIsSearching = false;
}

CServerHandler::~CServerHandler()
{
	// Free us master... Free us...
	if (pServerRequest)
	{
		SteamMatchmakingServers()->ReleaseRequest(pServerRequest);
		pServerRequest = NULL;
	}
}

void CServerHandler::ServerResponded(HServerListRequest hRequest, int iServer)
{
	gameserveritem_t *pServer = SteamMatchmakingServers()->GetServerDetails(pServerRequest, iServer);
	if (pServer)
	{
		// Filter out servers that don't match our appid here (might get these in LAN calls since we can't put more filters on it)
		if (pServer->m_nAppID == SteamUtils()->GetAppID())
		{
			m_iServersFound++;

			char szPlayers[16];
			char szPing[16];

			_snprintf_s(szPlayers, 16, "%i/%i", pServer->m_nPlayers, pServer->m_nMaxPlayers);
			_snprintf_s(szPing, 16, "%i", pServer->m_nPing);

			ServerBrowserForm::mainForm->AddServerItem(pServer->m_bPassword, pServer->GetName(), pServer->m_szMap, szPlayers, szPing, pServer->m_NetAdr.GetConnectionAddressString(), pServer->m_NetAdr.GetIP(), pServer->m_NetAdr.GetConnectionPort());
		}
	}
}

void CServerHandler::ServerFailedToRespond(HServerListRequest hRequest, int iServer)
{
}

void CServerHandler::RefreshComplete(HServerListRequest hRequest, EMatchMakingServerResponse response)
{
	m_bIsSearching = false;

	// Release our request.
	if (pServerRequest)
	{
		SteamMatchmakingServers()->CancelQuery(pServerRequest);
		SteamMatchmakingServers()->ReleaseRequest(pServerRequest);
		pServerRequest = NULL;
	}

	if (m_iServersFound <= 0)
		ServerBrowserForm::mainForm->Text = "CoF Server Browser - No Servers Available";
	else if (m_iServersFound == 1)
		ServerBrowserForm::mainForm->Text = "CoF Server Browser - One Server Available";
	else
	{
		char szServers[64];
		_snprintf_s(szServers, 64, "CoF Server Browser - %i Servers Available", m_iServersFound);
		System::String ^serversFound = gcnew String(szServers);
		ServerBrowserForm::mainForm->Text = serversFound;
	}
}

bool CServerHandler::RefreshInternetServers(void)
{
	if (m_bIsSearching)
		return false;

	m_bIsSearching = true;

	ServerBrowserForm::mainForm->RefreshServerList();
	ServerBrowserForm::mainForm->Text = "CoF Server Browser - Searching for Servers";
	m_iServersFound = 0;

	// Make sure we filtrate so we only get cof related servers, without these filters you basically search through all the servers on steam = it will take some time to fetch any results.
	MatchMakingKeyValuePair_t pFilters[1];
	MatchMakingKeyValuePair_t *pFilter = pFilters;

	strncpy_s(pFilters[0].m_szKey, "gamedir", sizeof(pFilters[0].m_szKey));
	strncpy_s(pFilters[0].m_szValue, "cryoffear", sizeof(pFilters[0].m_szValue));

	pServerRequest = SteamMatchmakingServers()->RequestInternetServerList(SteamUtils()->GetAppID(), &pFilter, ARRAYSIZE(pFilters), this);

	return true;
}