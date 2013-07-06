#include "Note.h"
#include "Form_RandomTest.h"
#include <stdio.h>
#include <iostream>
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>
#include <Windows.h>
#include <fmod.h>
#include <stdlib.h>
#include <list>

#define OUTPUTRATE          48000
#define SPECTRUMSIZE        8192
#define SPECTRUMRANGE       ((float)OUTPUTRATE / 2.0f)      /* 0 to nyquist */

#define BINSIZE      (SPECTRUMRANGE / (float)SPECTRUMSIZE)

#include <math.h>




#include "FMODEx\fmod.h"

Note::Note()
{

}

Note::Note(int _id, string _nom,string _nom_2, int _octave, float _frequence, string _image, string _image_2)
{
	id = _id;
	nom = _nom;
	nom_2 = _nom_2;
	octave = _octave;
	frequence = _frequence;

	image = _image;
	image_2 = _image_2;
}

Note::~Note (void)
{

}

int Note::GetId()
{
	return id;
}

string Note::GetNom()
{
	return nom;
}

string Note::GetNom_2()
{
	return nom_2;
}

int Note::GetOctave()
{
	return octave;
}

float Note::GetFrequence()
{
	return frequence;
}

string Note::GetImage()
{
	return image;
}

void Note::SetId(int _id)
{
	id = _id;
}

void Note::SetNom(string _nom)
{
	nom = _nom;
}

void Note::SetNom_2(string _nom_2)
{
	nom_2 = _nom_2;
}

void Note::SetOctave(int _octave)
{
	octave = _octave;
}

void Note::SetFrequence(float _frequence)
{
	frequence = _frequence;
}

void Note::SetImage(string _image)
{
	image = _image;
}

void Note::GetSong()
{
	//Joue la note courante
}

bool Note::IsSong(float _frequence)
{
	//TO DO : Appliquer une marge
	if (frequence == _frequence)
		return true;
	else
		return false;

}

Note Note::getNoteByFrequence(float _frequence)
{
	Note old;
	Note best;
	int i = 0;
	float current_result_up = NULL;
	float current_result_down = NULL;
	float best_result = 100;

	cout <<_frequence;

	for (list<Note>::iterator n = Notes.begin(); n != Notes.end(); n++)
	{
		Note current = *n;

		current_result_up = current.GetFrequence() - _frequence;
		current_result_down = _frequence - current.GetFrequence();

		if (n != Notes.begin())
			current_result_down = _frequence - old.GetFrequence();

		if (current_result_up < best_result)
			best = current;
		else if (current_result_down < best_result)
			best = old;
		
		old = *n;

	}

	return best;
	
	for (Note n : Notes)
	{   
		/*cout << n.GetFrequence();
		if (i < 1)
		{	
			if (_frequence == n.GetFrequence())
				return n;
		}
		else 
		{
			if ((_frequence > old.GetFrequence() && _frequence < n.GetFrequence()) ||(_frequence < old.GetFrequence() && _frequence > n.GetFrequence()))
			{ 
				result_old = _frequence - old.GetFrequence();
				result_n = n.GetFrequence() - _frequence;
				if (result_old<result_n)
					return old;
				else 
					return n;
			}
		}*/
		

		

	}

}

Note Note::getNoteById(int _id)
{
	for (Note n : Notes)
	{
		if (_id == n.GetId())
			return n;
	}
}

 
void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

//float Note::Play()
//{
//	FMOD::System    *system;
//    FMOD::Channel   *channel = 0;
//    FMOD::DSP       *dsp = 0;
//    FMOD_RESULT      result;
//    int              key = 0;
//    unsigned int     version;
//
//	  /*
//        Create a System object and initialize.
//    */
//    result = FMOD::System_Create(&system);
//    ERRCHECK(result);
//
//    result = system->getVersion(&version);
//    ERRCHECK(result);
//
//    if (version < FMOD_VERSION)
//    {
//        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
//        return 0;
//    }
//
//    result = system->init(32, FMOD_INIT_NORMAL, NULL);
//    ERRCHECK(result);
//
//    /*
//        Create an oscillator DSP units for the tone.
//    */
//    result = system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &dsp);
//    ERRCHECK(result);
//	//result = dsp->setParameter(FMOD_DSP_OSCILLATOR_RATE, 440.0f);       /* musical note 'A' */
//	result = dsp->setParameter(FMOD_DSP_OSCILLATOR_RATE, frequence);  /*Note courante */
//    ERRCHECK(result);
//
//	/*Frequence*/
//
//
//	 system->update();
//
//	  
//			float frequency = frequence, volume = 0, pan = 0;
//			result = system->playDSP(FMOD_CHANNEL_REUSE, dsp, true, &channel);
//            channel->setVolume(0.9f);
//            result = dsp->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 0);
//            ERRCHECK(result);
//            channel->setPaused(false);
//
//            bool playing = true;
//			 
//          
//            if (channel)
//            {
//                channel->getFrequency(&frequency);
//                channel->getVolume(&volume);
//                channel->getPan(&pan);
//                channel->isPlaying(&playing);
//            }
//
//    //printf("Channel %s : Frequency %.1f Volume %.1f Pan %.1f  \r", playing ? "playing" : "stopped", frequency, volume, pan);
//        
//}

float Note::Listen()
{
	FMOD::System          *system  = 0;
    FMOD::Sound           *sound   = 0;
    FMOD::Channel         *channel = 0;
    FMOD_RESULT            result;
    FMOD_CREATESOUNDEXINFO exinfo;
    int                    key, driver, recorddriver, numdrivers, count, bin;
    unsigned int           version;    

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }

    /* 
        System initialization
    */

    
    result = system->setOutput(FMOD_OUTPUTTYPE_DSOUND);
  
    ERRCHECK(result);
    
    /*
        Enumerate playback devices
    */

    result = system->getNumDrivers(&numdrivers);
    ERRCHECK(result);

 
    for (count=0; count < numdrivers; count++)
    {
        char name[256];

        result = system->getDriverInfo(count, name, 256, 0);
        ERRCHECK(result);

        printf("%d : %s\n", count + 1, name);
    }


    driver = 0;

    result = system->setDriver(driver);
    ERRCHECK(result);

    /*
        Enumerate record devices
    */

    result = system->getRecordNumDrivers(&numdrivers);
    ERRCHECK(result);

  
    for (count=0; count < numdrivers; count++)
    {
        char name[256];

        result = system->getRecordDriverInfo(count, name, 256, 0);
        ERRCHECK(result);

        printf("%d : %s\n", count + 1, name);
    }


    recorddriver = 0;


    printf("\n");
 
    result = system->setSoftwareFormat(OUTPUTRATE, FMOD_SOUND_FORMAT_PCM16, 1, 0, FMOD_DSP_RESAMPLER_LINEAR);
    ERRCHECK(result);

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    /*
        Create a sound to record to.
    */
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));

    exinfo.cbsize           = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.numchannels      = 1;
    exinfo.format           = FMOD_SOUND_FORMAT_PCM16;
    exinfo.defaultfrequency = OUTPUTRATE;
    exinfo.length           = exinfo.defaultfrequency * sizeof(short) * exinfo.numchannels * 5;
    
    result = system->createSound(0, FMOD_2D | FMOD_SOFTWARE | FMOD_LOOP_NORMAL | FMOD_OPENUSER, &exinfo, &sound);
    ERRCHECK(result);


    result = system->recordStart(recorddriver, sound, true);
    ERRCHECK(result);
    
    Sleep(200);      /* Give it some time to record something */
    
    result = system->playSound(FMOD_CHANNEL_REUSE, sound, false, &channel);
    ERRCHECK(result);

    /* Dont hear what is being recorded otherwise it will feedback.  Spectrum analysis is done before volume scaling in the DSP chain */
    result = channel->setVolume(0);
    ERRCHECK(result);

    bin = 0;

    /*
        Main loop.
    */
    do
    {
        static float spectrum[SPECTRUMSIZE];
        float        dominanthz = 0;
        float        max;
        Note          dominantnote;
        float        binsize = BINSIZE;

        result = channel->getSpectrum(spectrum, SPECTRUMSIZE, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE);
        ERRCHECK(result);

        max = 0;

        for (count = 0; count < SPECTRUMSIZE; count++)
        {
            if (spectrum[count] > 0.01f && spectrum[count] > max)
            {
                max = spectrum[count];
                bin = count;
            }
        }        

        dominanthz  = (float)bin * BINSIZE;       /* dominant frequency min */

		//for (list<Note>::iterator i(Notes.begin()); i != Notes.end(); i++)
		//{
		//	Note n_courant = *i;
		//	//Note n_suivant = *i++;
		//	if (dominanthz >= (n_courant.frequence - 50.0) && dominanthz < (n_courant.frequence + 50.0))
		//	{
		//		if (fabs(dominanthz - (n_courant.frequence - 50.0)) < fabs(dominanthz - (n_courant.frequence + 50.0)))
		//			dominantnote = n_courant;
		//		
		//	}
		//}
		//
		//if (this == &dominantnote)
		//	return true;
		//else 
		//	return false;
		
		
        //printf("Detected rate : %7.1f -> %7.1f hz.  Detected musical note. %-3s (%7.1f hz)\r", dominanthz, ((float)bin + 0.99f) * BINSIZE, note[dominantnote], notefreq[dominantnote]);

        system->update();

        Sleep(10);

    } while (key != 27);
	

}

	




