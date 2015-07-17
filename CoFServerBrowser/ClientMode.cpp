//=========      Copyright © 2015, Bernt Andreas Eide, All rights reserved      ============//
//
// Purpose: Handle internal stuff in the application such as UI accessing from external areas, handling of the server browser object, etc.
//
//=========================================================================================//

#include "stdafx.h"
#include "IClientMode.h"
#include "ServerHandler.h"
#include "PlayerInfoHandler.h"

// Form Includes
#include "ServerBrowserForm.h"
#include "MainForm.h"
#include "PlayerInfoForm.h"

struct RatioToAspectMode_t
{
	int anamorphic;
	float aspectRatio;
};

RatioToAspectMode_t g_RatioToAspectModes[] =
{
	{ 0, 4.0f / 3.0f },
	{ 1, 16.0f / 9.0f },
	{ 2, 16.0f / 10.0f },
	{ 2, 1.0f },
};

using namespace CoFServerBrowser;

class CClientMode : public IClientMode
{
public:

	// Base
	void Init(void);
	void Shutdown(void);
	void ExitApplication(void);
	void RunProgram(const char *ip = NULL);
	void StartMainForm(bool bValue);
	bool IsWideScreen(long wide, long tall);

	// Server Browser Definitions:
	void RequestServerList(void);
	void RequestPlayerInfo(uint32 ip, uint16 port);

private:

	CServerHandler *pServerBrowser;
	CPlayerInfoHandler *pPlayerBrowser;
};

static CClientMode g_ClientMode;
IClientMode *ClientMode = (IClientMode *)&g_ClientMode;

void CClientMode::Init()
{
	// Our server browser object which listens / receives from Steam!
	pServerBrowser = new CServerHandler();
	// Our player info object which checks for players per server.
	pPlayerBrowser = new CPlayerInfoHandler();

	// Init our main form
	ServerBrowserForm::mainForm = gcnew ServerBrowserForm();
	PlayerInfoForm::playerInfoForm = gcnew PlayerInfoForm();

	// Store the application startup path:
	char szTempPath[200];

	wchar_t result[200];
	HMODULE hModule = GetModuleHandleW(NULL);
	GetModuleFileName(hModule, result, 200);

	sprintf_s(szTempPath, "%ws", result);

	for (int i = 0; i < 200; i++)
	{
		if (szTempPath[i] == '\\')
			szTempPath[i] = '/';
	}

	memcpy(szStartupPath, szTempPath, (strlen(szTempPath) - 21));
}

void CClientMode::Shutdown(void)
{
	if (pServerBrowser)
		delete pServerBrowser;

	if (pPlayerBrowser)
		delete pPlayerBrowser;

	SteamAPI_Shutdown();
}

void CClientMode::ExitApplication(void)
{
	MainForm::baseForm->Close();
}

void CClientMode::RunProgram(const char *ip)
{
	if (!SteamApps()->BIsAppInstalled(SteamUtils()->GetAppID()))
	{
		MessageBox::Show("Cry of Fear has to be installed!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	}

	char szDirInst[256];
	SteamApps()->GetAppInstallDir(SteamUtils()->GetAppID(), szDirInst, 256);
	System::String ^directory = gcnew String(szDirInst);

	if (!Directory::Exists(directory))
	{
		MessageBox::Show("Unable to find directory\n\"" + directory + "\"\nHave you renamed or moved the original directory? If so you should move it back then reinstall CoF through Steam! (will only install missing stuff)", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	}

	if (!File::Exists(directory + "\\cof.exe"))
	{
		MessageBox::Show("Couldn't find \"" + directory + "\\cof.exe\"!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	}

	char szFile[256];
	_snprintf_s(szFile, 256, "%s/settings.txt", ClientMode->GetStartupPath());
	System::String ^filePath = gcnew String(szFile);

	StreamReader ^reader = File::OpenText(filePath);

	// Default Arguments (must be in)
	System::String ^arguments = "-basedir cryoffear -game cryoffear -hw -heapsize 1536000 ";

	// Custom Arguments (set -no3dmenu, w, h, etc)
	while (!reader->EndOfStream)
		arguments += (reader->ReadLine() + " ");

	reader->Close();

	// We want to join a server.
	// We copy the connection string to the clipboard in case the user wants to use it or send it to his friends. 
	// You will auto connect to the server you're trying to join.
	System::String ^ipAddress;
	if (ip)
	{
		ipAddress = gcnew String(ip);
		Clipboard::SetDataObject(("connect " + ipAddress), true);

		// Check if we're already running CoF, if so we can use the steam://connect/<ip:port> to tell the game to connect to the server!
		bool bIsRunning = false;
		for (int i = 0; i < Process::GetProcesses()->Length; i++)
		{
			if (Process::GetProcesses()[i]->ProcessName == "cof")
				bIsRunning = true;
		}

		// Connect to the server right away.
		if (bIsRunning)
		{
			Process::Start("steam://connect/" + ipAddress);
			return;
		}
	}

	// Run CoF
	Process ^mainProcess = gcnew Process();
	mainProcess->StartInfo->WindowStyle = ProcessWindowStyle::Hidden;
	mainProcess->StartInfo->CreateNoWindow = true;
	mainProcess->StartInfo->UseShellExecute = false;
	mainProcess->StartInfo->RedirectStandardOutput = true;
	mainProcess->StartInfo->WorkingDirectory = directory;
	mainProcess->StartInfo->FileName = directory + "\\cof.exe";
	mainProcess->StartInfo->Arguments = arguments;
	mainProcess->Start();

	System::Threading::Thread::Sleep(2000); // we wait 2 sec before we tell steam to connect to the desired server, so the game get some time to launch properly. If we do it right away we won't be able to override CoF's loading of the main menu.

	// Try to connect to the server a little after launching the game.
	if (ip)
		Process::Start("steam://connect/" + ipAddress);
}

void CClientMode::StartMainForm(bool bValue)
{
	ServerBrowserForm::mainForm->Visible = bValue;

	if (bValue)
		RequestServerList();
}

bool CClientMode::IsWideScreen(long wide, long tall)
{
	// Widescreen res?
	float aspectRatio = ((float)wide / (float)tall);

	float closestAspectRatioDist = 99999.0f;
	int closestAnamorphic = 0;
	for (int i = 0; i < ARRAYSIZE(g_RatioToAspectModes); i++)
	{
		float dist = fabs(g_RatioToAspectModes[i].aspectRatio - aspectRatio);
		if (dist < closestAspectRatioDist)
		{
			closestAspectRatioDist = dist;
			closestAnamorphic = g_RatioToAspectModes[i].anamorphic;
		}
	}

	return ((closestAnamorphic == 1) || (closestAnamorphic == 2));
}

void CClientMode::RequestServerList(void)
{
	if (pServerBrowser)
	{
		if (!pServerBrowser->RefreshInternetServers())
			MessageBox::Show("You're currently searching for servers, please wait a moment!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
}

void CClientMode::RequestPlayerInfo(uint32 ip, uint16 port)
{
	if (pPlayerBrowser)
		pPlayerBrowser->RefreshPlayerInfo(ip, port);
}