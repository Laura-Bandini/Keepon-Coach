// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
  * Copyright (C)2019  Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
  * Author:Dario Pasquali
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

/**
 * @file KeeponFamilyDayThread.h
 * @brief Definition of a thread to control the eyelids of iCub in the Head_Upgrade setup
 */


#ifndef _KEEPON_COACH_THREAD_H_
#define _KEEPON_COACH_THREAD_H_

#include <algorithm>
#include <string>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <time.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include <yarp/dev/SerialInterfaces.h>
#include <yarp/dev/PolyDriver.h>

#include "KeeponVocab.h"

#define SOUND_SLEEP_UP		63
#define SOUND_SLEEP_DOWN	21
#define SOUND_SLEEP_HUG		20
#define SOUND_SLEEP_HUG2	56
#define SOUND_BTN_PRESSURE	60
#define SOUND_BTN_PRESSURE_ERROR	42
#define SOUND_BTN_PRESSURE_ERROR2	44
#define SOUND_BOING	60

#define LINE			createVocab('l','i','n','e')
#define PERC			createVocab('d','r','o','p')
#define GAZE			createVocab('d','a','t','a')
#define BEGIN_FIX		createVocab('b','e','g', 0)
#define FIX				createVocab('f','i','x', 0)
#define END_FIX			createVocab('e','n','d', 0)
#define KEY_RIGHT		createVocab('r', 0, 0, 0)
#define KEY_LEFT		createVocab('l', 0, 0, 0)
#define KEY_SPACE		createVocab('s', 0, 0, 0)
#define KEY_DOWN		createVocab('d', 0, 0, 0)

class KeeponCoachThread : public yarp::os::Thread {

	yarp::os::Semaphore mutex;

private:

	enum KeeponState {LOOKGAME, LOOKGAMEPOS, LOOKSUBUNF, LOOKSUBHELP, LOOKKEY};
	
	yarp::os::ResourceFinder rf;

	//Receive Button Events from MyKeepon
	yarp::os::BufferedPort<yarp::os::Bottle> keeponEventsPort;
    //Riceve da tastiera
    yarp::os::BufferedPort<yarp::os::Bottle> KeyboardEventsPort;
    //Riceve la metrica dal gioco
    yarp::os::BufferedPort<yarp::os::Bottle> MetricsPort;
	//Riceve dal Tobii
	yarp::os::BufferedPort<yarp::os::Bottle> TobiiPort;
	//Send Commands to MyKeepon Architecture in the COMMAND format
	yarp::os::BufferedPort<yarp::os::Bottle> keeponCommandPort;

	// RPC kInterface
	yarp::os::RpcClient keeponRPC;
   
	std::string name;		//rootname of all the ports opened by this thread

	bool idle;
	KeeponState currentState;
	KeeponState previousState;

	int rightSpot;
	int leftSpot;

	int counter;
	double freqgioco;
	int vel;
	int valueline;
	bool lineexpl;
	int perchigh;
	int xvalue;
	int yvalue;
	int xvaluefix;
	int yvaluefix;
	int interTresholdKey = 4;	//intero di confronto con il valore di frequenza di gioco => frequenza di utilizzo tastiera.
	int interTresholdEyex1 = 1; //valori di confronto con le x e y derivanti e registrate dall'eyetracker. 
	int interTresholdEyex2 = 2;
	int interTresholdEyex3 = 1;
	int interTresholdEyey1 = 3;
	int interTresholdEyey2 = 4;

public:

	KeeponCoachThread(); // constructor default
	KeeponCoachThread(yarp::os::ResourceFinder &rf); // constructor  @param robotname name of the robot
    ~KeeponCoachThread();

	// ======= Generich Thread Methods ===========

	bool threadInit();
	void threadRelease();
	void updateSpots(std::vector<int> vocabs);
	void run();
    void onStop(); // function in charge of correctly closing the thread
	void close();

    void setName(std::string str);
	std::string getName(const char* p);

	bool connectToKeeponPorts();
    bool connectToKeyboard();
    bool connectToGame();
	bool connectToTobii();
	void sendCommand(std::string cmd);

	void sendCommandRPC(std::vector<int> vocabs);

	// ======= Project Specific Methods ===========

	/*Keepon sleeps and wait for the pressure of any button*/

	void startBehaviour();
	void stopBehaviour();

	//std::vector<std::vector<int>> generateRandomWalk(int steps);

	void hug();

	int checkForButtonPressure();
    int checkForKeyboardPressure();
    int checkForMetrics();
	int checkForTobii();

};

#endif  //_KEEPON_COACH_THREAD_H_

//----- end-of-file --- ( next line intentionally left blank ) ------------------

