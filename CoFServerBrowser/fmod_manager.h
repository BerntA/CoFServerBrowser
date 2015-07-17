//=========      Copyright © 2015, Bernt Andreas Eide, All rights reserved      ============//
//
// Purpose: A simple FMOD wrapper to play and stop sounds.
//
//=========================================================================================//

#ifndef FMOD_MANAGER_H
#define FMOD_MANAGER_H
#ifdef _WIN32
#pragma once
#endif

#include "stdafx.h"
#include "fmod.hpp"

#define MAX_SOUND_PATH 200

class CFMODManager
{
public:

	CFMODManager();
	~CFMODManager();

	void InitFMOD();
	void ExitFMOD();

	void SetVolume(float flVolume) { m_flVolume = flVolume; }
	float GetVolume(void) { return m_flVolume; }

	void PlaySound(const char *szSoundPath);
	void StopSound(void);

private:

	float m_flVolume;
};

extern CFMODManager *FMODManager();

#endif //FMOD_MANAGER_H