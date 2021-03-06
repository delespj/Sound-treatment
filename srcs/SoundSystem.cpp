#include <iostream>
#include "fmod_errors.h"
#include "SoundSystem.hh"

// Function for handling FMOD errors
inline void fmod_errorcheck(const FMOD_RESULT result) {
	if(result != FMOD_OK) {
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
	}
}

SoundSystem::SoundSystem(const char *song_name) {
	// Init FMOD
	fmod_errorcheck(FMOD_System_Create(&fmod_system));
	fmod_errorcheck(FMOD_System_SetSoftwareFormat(fmod_system, OUTPUTRATE, FMOD_SOUND_FORMAT_PCM16, 2, 0, FMOD_DSP_RESAMPLER_LINEAR));
	fmod_errorcheck(FMOD_System_Init(fmod_system, 32, FMOD_INIT_NORMAL, 0));
	// Init song
	fmod_errorcheck(FMOD_System_CreateStream(fmod_system, song_name, FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE | FMOD_UNIQUE, 0, &music));
}

SoundSystem::~SoundSystem() {
	fmod_errorcheck(FMOD_Sound_Release(music));
	fmod_errorcheck(FMOD_System_Close(fmod_system));
	fmod_errorcheck(FMOD_System_Release(fmod_system));
}

void SoundSystem::play_music() {
	fmod_errorcheck(FMOD_System_PlaySound(fmod_system, FMOD_CHANNEL_FREE, music, false, &channel));
}

//This analyzes the spectrum of the music FMODs own features
void SoundSystem::get_spectrum(float *spectrumL, float *spectrumR) const {
	fmod_errorcheck(FMOD_Channel_GetSpectrum(channel, spectrumL, SPECTRUMSIZE, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE));
	fmod_errorcheck(FMOD_Channel_GetSpectrum(channel, spectrumR, SPECTRUMSIZE, 1, FMOD_DSP_FFT_WINDOW_TRIANGLE));
}

void SoundSystem::update() const {
	fmod_errorcheck(FMOD_System_Update(fmod_system));
}
