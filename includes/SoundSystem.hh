#ifndef SOUND_SYSTEM_HH__
#define SOUND_SYSTEM_HH__

#include "fmod.h"

#define OUTPUTRATE 48000
#define SPECTRUMSIZE 4096 //Defines the accuracy of the analyzed spectrum

/*
 *	The class for initializing FMOD and playing and analyzing music
 */
class SoundSystem {
	private:
		FMOD_SYSTEM		*fmod_system;
		FMOD_SOUND		*music;
		FMOD_CHANNEL	*channel;

	public:
		SoundSystem(const char *song_name);
		~SoundSystem();
		void play_music();
		void get_spectrum(float *spectrumL, float *spectrumR) const;
		void update() const;

	private:
		SoundSystem(const SoundSystem& obj); //Copy constructor
		SoundSystem&   operator =(const SoundSystem &obj); //Assign operator
};

#endif
