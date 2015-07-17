//=========      Copyright © 2015, Bernt Andreas Eide, All rights reserved      ============//
//
// Purpose: Main Entry Point of this app.
//
//=========================================================================================//

#include "MainForm.h"
#include "stdafx.h"
#include "steam_api.h"
#include "IClientMode.h"

using namespace CoFServerBrowser;

[STAThreadAttribute]
int main()
{
	bool bInit = false;

	if (SteamAPI_Init())
	{
		if (SteamUtils()->GetAppID() != (AppId_t)223710)
		{
			MessageBox::Show("This program supports Cry of Fear only! (AppID 223710).\nThe source code is available at GitHub if you want to make a new version for a third party mod/game!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return 0;
		}

		bInit = true;

		ClientMode->Init();
		FMODManager()->InitFMOD();

		// start us up!
		MainForm::baseForm = gcnew MainForm();
		MainForm::baseForm->ShowDialog();
	}
	else
		MessageBox::Show("Unable to init Steam API!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);

	if (bInit)
	{
		ClientMode->Shutdown();
		FMODManager()->ExitFMOD();
	}

	return 0;
}