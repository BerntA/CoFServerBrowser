//=========      Copyright © 2015, Bernt Andreas Eide, All rights reserved      ============//
//
// Purpose: A simple FMOD wrapper to play and stop sounds.
//
//=========================================================================================//

#include "fmod_manager.h"
#include "IClientMode.h"

using namespace FMOD;

FMOD::System	*pSystem;
FMOD::Sound			*pSound;
FMOD::SoundGroup		*pSoundGroup;
FMOD::Channel			*pChannel;
FMOD::ChannelGroup	*pChannelGroup;
FMOD_RESULT		result;

CFMODManager gFMODMng;
CFMODManager* FMODManager()
{
	return &gFMODMng;
}

CFMODManager::CFMODManager()
{
}

CFMODManager::~CFMODManager()
{
}

void CFMODManager::InitFMOD(void)
{
	result = System_Create(&pSystem); // Create the main system object.

	if (result != FMOD_OK)
	{
		MessageBox(NULL, _T("Unable to create FMOD!"), _T("Error"), MB_OK | MB_SYSTEMMODAL);
		return;
	}

	result = pSystem->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD system.

	if (result != FMOD_OK)
		MessageBox(NULL, _T("Unable to init FMOD!"), _T("Error"), MB_OK | MB_SYSTEMMODAL);

	m_flVolume = 1.0f;
}

void CFMODManager::ExitFMOD(void)
{
	result = pSystem->release();

	if (result != FMOD_OK)
		MessageBox(NULL, _T("FMOD was unable to shutdown!"), _T("Error"), MB_OK | MB_SYSTEMMODAL);
}

void CFMODManager::PlaySound(const char *szSoundPath)
{
	char soundPath[MAX_SOUND_PATH];
	_snprintf_s(soundPath, MAX_SOUND_PATH, "%s/%s", ClientMode->GetStartupPath(), szSoundPath);

	result = pSystem->createStream(soundPath, FMOD_DEFAULT, 0, &pSound);

	if (result != FMOD_OK)
	{
		MessageBox(NULL, _T("FMOD was unable to play the desired sound!"), _T("Error"), MB_OK | MB_SYSTEMMODAL);
		return;
	}

	result = pSystem->playSound(FMOD_CHANNEL_REUSE, pSound, false, &pChannel);

	if (result != FMOD_OK)
	{
		MessageBox(NULL, _T("FMOD was unable to play the desired sound!"), _T("Error"), MB_OK | MB_SYSTEMMODAL);
		return;
	}

	pChannel->setVolume(m_flVolume);
}

void CFMODManager::StopSound(void)
{
	if (pChannel)
		pChannel->setVolume(0.0f);
}