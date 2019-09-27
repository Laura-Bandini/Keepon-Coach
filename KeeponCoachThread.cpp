// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C)2019  Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 *
 * Revision: Dario Pasquali
 * email: dario.pasquali@iit.it
 *
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

/**
 * @file KeeponFamilyDayThread.cpp
 * @brief Implementation of KeeponFamilyDayThread.h.
 */

#include <KeeponCoachThread.h>


using namespace yarp::dev;
using namespace yarp::os;
using namespace yarp::sig;
using namespace std;


KeeponCoachThread::KeeponCoachThread() :Thread() {
}

KeeponCoachThread::KeeponCoachThread(yarp::os::ResourceFinder &_rf):Thread(){
	rf = _rf;
}

KeeponCoachThread::~KeeponCoachThread() {
    // do nothing
}

bool KeeponCoachThread::threadInit() 
{
    //    ptime time_start(microsec_clock::local_time());
    yInfo("KeeponCoachThread::threadInit: initialization in the method");
		
	//bool ok = connectToKeeponPorts();
    bool ok1 = connectToKeyboard();
    //bool ok2 = connectToGame();
	//bool ok3 = connectToTobii();

	//yInfo("Idle the behaviour");
	//idle = true;
	currentState = LOOKGAME;
	previousState = LOOKGAME;

	yInfo("Thread correctly initialised \n");
    return ok1;
}

bool KeeponCoachThread::connectToKeeponPorts() {

	yInfo("OPEN PORTS to MyKeepon");

	yInfo("Open Output Port");
	if (!keeponCommandPort.open(getName("/cmd:o").c_str())) {
		yError(": unable to open port ");
		return false;  // unable to open; let RFModule know so that it won't run
	}

	yInfo("Open input Port");
	if (!keeponEventsPort.open(getName("/events:i").c_str())) {
		yError(": unable to open port to send unmasked events ");
		return false;  // unable to open; let RFModule know so that it won't run
	}

	Network yarp;
	//yInfo("Open RPC Port");
	//keeponRPC.setRpcMode(true);
	//keeponRPC.open(getName("/cmd/rpc:o"));

	yarp.connect(getName("/cmd:o"), "/kInterface/cmd:i");

	yInfo("CHECK AND WAIT FOR CONNECTIONS");

	//yDebug("Waiting for Keepon Commands");
	//while (!Network::isConnected(getName("/cmd:o"), "/kInterface/cmd:i", true));
	//yDebug("Keepon Commands Connected");
	
	//yDebug("Connect Keepon RPC Port");
	//while (!Network::isConnected(getName("/cmd/rpc:o"), "/kInterface", true));
	yDebug("Keepon Output Connected");

	yarp.connect("/kInterface/message:o", getName("/events:i"));

	yDebug("Waiting for Keepon Events");
	while (!Network::isConnected("/kInterface/message:o", getName("/events:i"), true));
	yDebug("Keepon Events Connected");

	return true;
}

bool KeeponCoachThread::connectToKeyboard() {

	yInfo("OPEN PORT to Keyboard");

	yInfo("Open input Port");
	if (!KeyboardEventsPort.open(getName("/keyboard/events:i").c_str())) {
		yError(": unable to open port to send unmasked events ");
		return false;  // unable to open; let RFModule know so that it won't run
	}
	else {
		yError("able to open port to send unmasked events ");
	}
	
	
	Network yarp;
	
	bool res = yarp.connect("/tetris/key:o", getName("/keyboard/events:i"));
	if (res) {
		yInfo("connection done: from /tetris/key:o to /keyboard/events:i ");
	}
	else {		
		yInfo("connection error: from /tetris/key:o to /keyboard/events:i ");
	}
	
	

	return true;
}

bool KeeponCoachThread::connectToGame() {

    yInfo("OPEN PORT to Game");
    
    yInfo("Open input Port");
    if (!MetricsPort.open(getName("/metrics/events:i").c_str())) {
		yError(": unable to open port to send unmasked events ");
		return false;  // unable to open; let RFModule know so that it won't run
	}

	Network yarp;

	yarp.connect("/tetris/metrics:o", getName("/metrics/events:i"));

	yDebug("Metric connected");

	return true;
}

bool KeeponCoachThread::connectToTobii() {

	yInfo("OPEN PORT to Tobii");

	yInfo("Open input Port");
	if (!TobiiPort.open(getName("/tobii/events:i").c_str())) {
		yError(": unable to open port to send unmasked events ");
		return false;  // unable to open; let RFModule know so that it won't run
	}

	Network yarp;

	yarp.connect("/Tobii/message:o", getName("/tobii/events:i"));

	yDebug("Waiting for Tobii Events");

	return true;
}

void KeeponCoachThread::startBehaviour() {

	yInfo("START BEHAVIOUR");

	//sendCommandRPC(senseV(true));
	//Time::delay(1.0);
    yWarning("ENABLE SENSING1");
	idle = false; 
}
void KeeponCoachThread::stopBehaviour() {

	yWarning("DISABLE SENSING");
	//sendCommandRPC(senseV(false));

}

void KeeponCoachThread::sendCommand(std::string cmd) {

	Bottle& b = keeponCommandPort.prepare();
	b.clear();
	b.addString(cmd);
	keeponCommandPort.write();
}

void KeeponCoachThread::sendCommandRPC(std::vector<int> vocabs) {
	
	//yInfo("SENDING ==> %s", cmd.c_str());

	Bottle message;
	Bottle response;

	message.clear();
	response.clear();

	for (int i = 0; i < vocabs.size(); i++)
		message.addVocab(vocabs[i]);

	keeponRPC.write(message, response);
	//yInfo("RECEIVED ==> %s", response.get(0).asString().c_str());
}

int KeeponCoachThread::checkForKeyboardPressure() {
	Bottle* input;
	input = NULL;
	string message;
	if (KeyboardEventsPort.getInputCount()) {
		yDebug("In the checkForKeyboardPressure");
		//Legge un evento da tastiera
		input = KeyboardEventsPort.read(true);
		message = input->toString();
		yInfo("Messaggio %s", message.c_str());
		yDebug("after read in checkForKeyboardPressure");
	}
	if (input == NULL) {
		return false;
	}

	if (!input->isNull()) {

		//mutex.wait();
		switch (input->get(0).asVocab()) {

			case KEY_RIGHT: 
				freqgioco = freqgioco + 1.0;
				yInfo("Messaggio %f", message.c_str());
				//yInfo("Frequenza: %f", freqgioco);
			
			break;
		
			case KEY_LEFT: 
				freqgioco = freqgioco + 1.0;
				yInfo("Messaggio %f", message.c_str());
				//yInfo("Frequenza: %f", freqgioco);
			
			break;

			case KEY_SPACE: 
				freqgioco = freqgioco + 1.0;
				yInfo("Messaggio %f", message.c_str());
				//yInfo("Frequenza: %f", freqgioco);
				
			break;

			case KEY_DOWN: 
				vel = vel + 1;
				yInfo("Messaggio %s", message.c_str());
				//yInfo("Vel %d", vel);
				
			break;
		
		}

		//freqgioco = freqgioco - 0.1;

		yInfo("Frequenza: %f", freqgioco);
		yInfo("Velocita: %d", vel);
		//mutex.post();

	}

	freqgioco = freqgioco - 0.1;
	yInfo("Frequenza: %f", freqgioco);	

	yInfo("Ricezione dati");
	return 0;
}

int KeeponCoachThread::checkForMetrics() {

    //Legge un evento dal gioco 
	yDebug("In checkForMetrics");
    Bottle* input = MetricsPort.read();

    if (!input->isNull()) {

		string message = input->get(0).toString();
		yInfo("Messaggio %s", message.c_str());

		//mutex.wait();
		switch (input->get(0).asVocab()) {
		case LINE:
			valueline = input->get(1).asVocab();
			lineexpl = true;
			break;

		case PERC:
			perchigh = input->get(1).asVocab();
			yInfo("Perchigh: %d", perchigh);
			break;
		}
		//mutex.post();
	
    }

	return 0;

}

int KeeponCoachThread::checkForTobii() {

	//Legge eventi dall'Eye Tracker
	Bottle* input = TobiiPort.read(false);

	if (input != NULL) {
		//mutex.wait();
		switch (input->get(0).asVocab()) {
		case GAZE:
			xvalue = input->get(2).asVocab();
			yvalue = input->get(3).asVocab();

			yInfo("x value: %d", xvalue);
			yInfo("y value: %d", yvalue);

			break;

		case FIX:
			xvaluefix = input->get(2).asVocab();
			yvaluefix = input->get(3).asVocab();

			yInfo("x valuefix: %d", xvaluefix);
			yInfo("y valuefix: %d", xvaluefix);
			break;
		}
		//mutex.post();
		yInfo("Received");
	}

	return 0;

}

void KeeponCoachThread::hug() {

	yInfo("HUUUUUUUUUG");

	sendCommandRPC(playSoundV(SOUND_SLEEP_HUG2));
	Time::delay(1.0);
	for (int i = 0; i < 5; i++) {
		sendCommandRPC(movePonV(PonPos::DOWN));
		Time::delay(0.25);
		sendCommandRPC(playSoundV(SOUND_BOING));
		Time::delay(0.25);
	}
	sendCommandRPC(playSoundV(SOUND_SLEEP_HUG));
	Time::delay(0.4);
	sendCommandRPC(playSoundV(SOUND_SLEEP_HUG));
	Time::delay(1.0);
}

void KeeponCoachThread::run() {

	freqgioco = 0.0;
	vel = 0;

	yWarning("ENABLE SENSING");
	//sendCommandRPC(senseV(true));
	//Time::delay(1.0);

	yWarning("Set Speed");
	//sendCommandRPC(setSpeedPanV(100));
	//Time::delay(1.0);
	//sendCommandRPC(setSpeedSideV(255));
	//Time::delay(1.0);
	//sendCommandRPC(setSpeedTiltV(100));

	while (isRunning() && !isStopping()) {

		yDebug("In while");

			switch (currentState)
			{

			case KeeponCoachThread::LOOKGAME: {

				yDebug("Game");

				//checkForTobii();
				//checkForMetrics();
				checkForKeyboardPressure();

				yInfo("Esecuzione comandi Keepon");
				//sendCommandRPC(moveTiltV(80));
				//Time::delay(1.0);
				//sendCommandRPC(moveTiltV(-70));

				if (freqgioco <= interTresholdKey) {

					yInfo("Esecuzione del Keepon");
					//currentState = LOOKKEY;
					//previousState = LOOKGAME;
				}

				 // a seconda di come l'utente interagisce con il gioco ho diversi casi e comportamenti del Keepon

				 //movimenti a seconda del pezzo che arriva (si possono scrivere a priori come fosse il randomwalk conoscendo l'ordine dei pezzi?)

						/*if ( xvalue > interTresholdEyex3 || xalue < interTreshold1 || yvalue > interTresholdy2 ) {
							currentState = LOOKSUBUNF;
							previousState = LOOKGAME;
							}

						if (lineexpl) {
							currentState = LOOKGAMEPOS;
							previosuState = LOOKGAME;
							}

						if (interTresholdEyex1 < xvalue < interTresholdEyex2 && interTresholdy1 <yvalue > interTresholdy2) {
							currentState = LOOKSUBHELP;
							previousState = LOOKGAME;
							}*/

				break;
			}
			case KeeponCoachThread::LOOKGAMEPOS: {
				//Nel caso di buona riuscita del gioco

					/*sendCommandRPC(move..(saltini));
					sendCommandRPC(playSound...(positivi));

					if (!lineexpl) {
						currentState = LOOKGAME;
						previousState = LOOKGAMEPOS;
					} */

				break;
			}
			case KeeponCoachThread::LOOKSUBUNF: {
				//Look Subject unfocused: se il soggetto non guarda al gioco

					 /*sendCommandRPC(move....(in modo che si giri verso il soggetto));
					sendCommandRPC(move....(in modo che faccia movimenti "arrabbiati"));
					sendCommandRPC(playSound....(in modo che emetta un verso negativo));

					if (interTresholdEyex2 < xvalue < interTresholdEyex3 && interTresholdy1 <yvalue > interTresholdy2 ) {
						currentState = LOOKGAME;
						previousState = LOOKSUBUNF;
					} */

				break;
			}
			case KeeponCoachThread::LOOKSUBHELP: {
				//Look Subject for mutual gaze: se il soggetto guarda al Keepon per un aiuto

					/*sendCommandRPC(move....(in modo che si giri verso il soggetto));
					sendCommandRPC(move....(movimenti positivi));
					sendCommandRPC(playSound....(in modo che emetta un verso che tranquillizzi));

					if (interTresholdEyex2 < xvalue < interTresholdEyex3 && interTresholdy1 <yvalue > interTresholdy2 ) {
						currentState = LOOKGAME;
						previousState = LOOKSUBHELP;
						}*/

				break;
			}
			case KeeponCoachThread::LOOKKEY: {

				yInfo("Keyboard");
				//hug();
				//sendCommandRPC(playSoundV(SOUND_SLEEP_DOWN));

				/*if (freqgioco >= 2) {
					currentState = LOOKGAME;
					previousState = LOOKKEY;
				}*/
				//Nel caso in cui il soggetto non utilizzi la tastiera

					/*sendCommandRPC(move....(in modo che si giri verso la tastiera));
					sendCommandRPC(playSound....(suono arrabbiato));

					if (#rotazioni_pezzo > interTresholdKey) {
						currentState = GAME;
						previousState = KEYBOARD;
						} */
				break;
			}
			default:
				break;
			}
	}

		//Time::delay(0.05);
}

void KeeponCoachThread::onStop(){
	keeponCommandPort.interrupt();
	keeponCommandPort.close();

	keeponEventsPort.interrupt();
	keeponEventsPort.close();

	yDebug("Executing code in onStop");    
}

void KeeponCoachThread::threadRelease() {
    yDebug("Executing code in threadRelease");
}

void KeeponCoachThread::setName(string str) {
	this->name = str;
}

std::string KeeponCoachThread::getName(const char* p) {
	string str(name);
	str.append(p);
	return str;
}