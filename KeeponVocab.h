// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
  * Copyright (C)2015  Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
  * Author: Dario Pasquali
  * email: dario.pasquali@iit.it
  * Permission is granted to copy, distribute, and/or modify this program
  * under the terms of the GNU General Public License, version 2 or any
  * later version published by the Free Software Foundation.
  *
  * A copy of the license can be found at
  * http://www.robotcub.org/icub/license/gpl.txt
  *
  * This program is distributed in the hope that it will be useful, but
  * WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
  * Public License for more details
*/

#ifndef _KEEPON_VOCAB_INTERFACE_H_
#define _KEEPON_VOCAB_INTERFACE_H_

#include <iostream>
#include <string>
#include <map>

#include <yarp/sig/all.h>
#include <yarp/os/all.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/Network.h>
#include <yarp/os/Thread.h>
#include <yarp/os/Log.h>

using namespace yarp::os;
using namespace yarp::sig;
using namespace std;

// Generic Commands
#define VOCAB_STOP     	createVocab('S','T','O','P')
#define VOCAB_ECHO     	createVocab('E','C','H','O')
#define VOCAB_HELP		createVocab('H','E','L','P')
#define VOCAB_OK		createVocab('o','k', 0, 0)
#define VOCAB_FAILED	 createVocab('F','A','I','L')

// Setting Commands
#define VOCAB_SENSE     createVocab('S','E','N','S')
#define VOCAB_SPEED    	createVocab('S','P','E','E')
#define VOCAB_ON   		createVocab('O','N', 0, 0)
#define VOCAB_OFF    	createVocab('O','F','F', 0)

// Body Parts Commands
#define VOCAB_PAN    	createVocab('P','A','N',0)
#define VOCAB_PON    	createVocab('P','O','N',0)
#define VOCAB_SIDE     	createVocab('S','I','D','E')
#define VOCAB_TILT     	createVocab('T','I','L','T')

// Movements
#define VOCAB_MOVE     	createVocab('M','O','V','E')
// Pon
#define VOCAB_UP     	createVocab('U','P', 0, 0)
#define VOCAB_DOWN     	createVocab('D','O','W','N')
#define VOCAB_HALFDOWN 	createVocab('H','A','L','D')
#define VOCAB_HALFUP   	createVocab('H','A','L','U')
// Side
#define VOCAB_CYCLE    	createVocab('C','Y','C','L')
#define VOCAB_CEFL     	createVocab('C','E','F','L')
#define VOCAB_RIGHT    	createVocab('R','I','G','H')
#define VOCAB_CEFR     	createVocab('C','E','F','R')
#define VOCAB_LEFT     	createVocab('L','E','F','T')

// Audio Commands
#define VOCAB_SOUND    	createVocab('S','O','U','N')
#define VOCAB_PLAY     	createVocab('P','L','A','Y')
#define VOCAB_DELAY    	createVocab('D','E','L','A')
#define VOCAB_REPEAT   	createVocab('R','E','P','E')

// Sensing Commands
#define VOCAB_EMF    	createVocab('E','M','F',0)
#define VOCAB_BUTTON   	createVocab('B','U','T','T')
#define VOCAB_AUDIO    	createVocab('A','U','D','I')
#define VOCAB_POSITION 	createVocab('P','O','S','I')
#define VOCAB_ENCODER  	createVocab('E','N','C','O')
#define VOCAB_MOTOR    	createVocab('B','U','T','T')
#define VOCAB_RANGE 	createVocab('R','A','N','G')
#define VOCAB_ENVELOPE 	createVocab('E','N','V','E')
#define VOCAB_BPM    	createVocab('B','P','M',0)

// Mode Commands
#define VOCAB_MODE    	createVocab('M','O','D','E')
#define VOCAB_DANCE   	createVocab('D','A','N','C')
#define VOCAB_TOUCH   	createVocab('T','O','U','C')
#define VOCAB_TEMPO   	createVocab('T','E','M','P')
#define VOCAB_SLEEP   	createVocab('S','L','E','E')

#define VOCAB_SEP      createVocab(' ', 0, 0, 0)
#define VOCAB_END      string("")

// =============================================================================

// Generic Commands
#define COMMAND_STOP    string("STOP")
#define COMMAND_ECHO    string("ECHO")
#define COMMAND_HELP    string("HELP")
#define COMMAND_OK      string("OK")
#define COMMAND_FAILED  string("FAIL")

// Setting Commands
#define COMMAND_SENSE   string("SENSE")
#define COMMAND_SPEED   string("SPEED")
#define COMMAND_ON   	string("ON")
#define COMMAND_OFF    	string("OFF")

// Body Parts Commands
#define COMMAND_PAN    	string("PAN")
#define COMMAND_PON    	string("PON")
#define COMMAND_SIDE    string("SIDE")
#define COMMAND_TILT    string("TILT")

// Movements
#define COMMAND_MOVE    string("MOVE")
// Pon
#define COMMAND_UP     	    string("UP")
#define COMMAND_DOWN        string("DOWN")
#define COMMAND_HALFDOWN 	string("HALFDOWN")
#define COMMAND_HALFUP   	string("HALFUP")
// Side
#define COMMAND_CYCLE    	string("CYCLE")
#define COMMAND_CEFL     	string("CEFL")
#define COMMAND_RIGHT    	string("RIGHT")
#define COMMAND_CEFR     	string("CEFR")
#define COMMAND_LEFT     	string("LEFT")

// Audio Commands
#define COMMAND_SOUND    	string("SOUND")
#define COMMAND_PLAY     	string("PLAY")
#define COMMAND_DELAY    	string("DELAY")
#define COMMAND_REPEAT   	string("REPEAT")

// Sensing Commands
#define COMMAND_EMF    	    string("EMF")
#define COMMAND_BUTTON   	string("BUTTON")
#define COMMAND_AUDIO    	string("AUDIO")
#define COMMAND_POSITION 	string("POSITION")
#define COMMAND_ENCODER  	string("ENCODER")
#define COMMAND_MOTOR    	string("MOTOR")
#define COMMAND_RANGE 	    string("RANGE")
#define COMMAND_ENVELOPE 	string("ENVELOPE")
#define COMMAND_BPM    	    string("BPM")

// Mode Commands
#define COMMAND_MODE    	string("MODE")
#define COMMAND_DANCE   	string("DANCE")
#define COMMAND_TOUCH   	string("TOUCH")
#define COMMAND_TEMPO   	string("TEMPO")
#define COMMAND_SLEEP   	string("SLEEP")

#define COMMAND_SEP      string("_")
#define COMMAND_END      string(";")

// Convertions
// Vocab --> Command
// Command --> Vocab

enum PonPos {
  UP,
  HALFDOWN,
  DOWN,
  HALFUP,
  CYCLE,
  CENTERFROMLEFT,
  RIGHT,
  CENTERFROMRIGHT,
  LEFT
};


/*
KEEPON COMMANDS - useful for reference
		Allowable commands (the closing semicolon is required):
		SOUND PLAY <0...63>;
		SOUND REPEAT <0...63>;
		SOUND DELAY <msec>;
		SOUND STOP;
		SPEED [PAN, TILT, PONSIDE] <0...255>;
		MOVE PAN <-100...100>;
		MOVE TILT <-100...100>;
		MOVE SIDE [CYCLE, CENTERFROMLEFT, RIGHT, CENTERFROMRIGHT, LEFT];
		MOVE PON [UP, HALFDOWN, DOWN, HALFUP];
		MOVE STOP;
		MODE [DANCE, TOUCH];
		MODE TEMPO;
		MODE SLEEP;
		SENSE [ON, OFF];

		Strings that the Arduino can send back to you:
		BUTTON [DANCE, TOUCH] [OFF, ON]
		BUTTON [HEAD, FRONT, BACK, RIGHT, LEFT] [OFF, ON]
		MOTOR [PAN, TILT, SIDE, PON] FINISHED
		MOTOR [PAN, TILT, SIDE, PON] STALLED
		ENCODER TILT [NOREACH, FORWARD, BACK, UP]
		ENCODER PON [HALFDOWN, UP, DOWN, HALFUP]
		ENCODER SIDE [CENTER, RIGHT, LEFT]
		ENCODER PAN [BACK, RIGHT, LEFT, CENTER]
		EMF [PAN, TILT, PONSIDE] [-127...127]
		POSITION [PAN, TILT, PONSIDE] [VAL]
		AUDIO TEMPO [67, 80, 100, 133, 200] (if BPM cannot be detected, this is estimated from power spectral density response)
		AUDIO MEAN [0...64] (the mean of the envelope over a 1.28sec window, max around 64 for very loud music, not updated when motors are moving)
		AUDIO RANGE [0...64] (dynamic range, max 64 for shouting, not updated when motors moving)
		AUDIO ENVELOPE [0...127] (near instantaneous log of the audio amplitude; commented out in code for reduction of data transfer)
		AUDIO BPM [VAL] (estimated beat interval in multiples of 5msec)
*/


// Generate Vocab Sequence
std::vector<int> playSoundV(int soundID);
std::vector<int> delaySoundV(int soundID);
std::vector<int> repeatSoundV(int soundID);
std::vector<int> stopSoundV();

std::vector<int> setSpeedPanV(int speed);
std::vector<int> setSpeedTiltV(int speed);
std::vector<int> setSpeedSideV(int speed);

std::vector<int> movePanV(int position);
std::vector<int> moveTiltV(int position);
std::vector<int> movePonV(PonPos position);
std::vector<int> moveSideV(PonPos position);
std::vector<int> moveStopV();

//std::vector<int> echoV(char* singleWord);
std::vector<int> senseV(bool state);

// ==================================================================

// Generate Command Sequence
string playSoundC(int soundID);
string delaySoundC(int soundID);
string repeatSoundC(int soundID);
string stopSoundC();

string setSpeedPanC(int speed);
string setSpeedTiltC(int speed);
string setSpeedSideC(int speed);

string movePanC(int position);
string moveTiltC(int position);
string movePonC(PonPos position);
string moveStopC();

string echoC(char* singleWord);
string senseC(bool state);

int ponPosToVocab(PonPos pos);
string ponPosToCommand(PonPos pos);

#endif