// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
  * Copyright (C)2019  Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
  * 
  * Author: Dario Pasquali
  * email: dario.pasquali@iit.it
  * 
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
 * @file KeeponFamilyDayModule.cpp
 * @brief Implementation of the KeeponFamilyDayModule to control Blinking with Serial.
 */

#include "KeeponCoachModule.h"

using namespace yarp::os;
using namespace yarp::sig;
using namespace std;

/* 
 * Configure method. Receive a previously initialized
 * resource finder object. Use it to configure your module.
 * If you are migrating from the old Module, this is the 
 *  equivalent of the "open" method.
 */

KeeponCoachModule::KeeponCoachModule() {
    //do nothing       
}

KeeponCoachModule::~KeeponCoachModule() {
    // do nothing
}

bool KeeponCoachModule::configure(yarp::os::ResourceFinder &rf) {
    /* Process all parameters from both command-line and .ini file */

    /* get the module name which will form the stem of all module port names */

    moduleName = rf.check("name", Value("/keeponCoach"), "module name (string)").asString();
	
    /*
    * before continuing, set the module name before getting any other parameters, 
    * specifically the port names which are dependent on the module name
    */
    setName(moduleName.c_str());
   
    /*
    * attach a port of the same name as the module (prefixed with a /) to the module
    * so that messages received from the port are redirected to the respond method
    */
    handlerPortName =  "";
    handlerPortName += getName();         // use getName() rather than a literal

    if (!handlerPort.open(handlerPortName.c_str())) {           
        cout << getName() << ": Unable to open port " << handlerPortName << endl;  
        return false;
    }

    attach(handlerPort);                  // attach to port
    if (rf.check("config")) {
        configFile=rf.findFile(rf.find("config").asString().c_str());
        if (configFile=="") {
            return false;
        }
    }
    else {
        configFile.clear();
    }
	
    /* create the thread and pass pointers to the module parameters */
    thread = new KeeponCoachThread(rf);
    thread->setName(getName().c_str());
    
    /* now start the thread to do the work */
    thread->start(); // this calls threadInit() and it if returns true, it then calls run()

    return true ;       // let the RFModule know everything went well
                        // so that it will then run the module
}

bool KeeponCoachModule::interruptModule() {
    handlerPort.interrupt();
    return true;
}

bool KeeponCoachModule::close() {
    /* stop the thread */
    yDebug("stopping the thread ");
    thread->stop();
	handlerPort.interrupt();
	handlerPort.close();
    return true;
}

bool KeeponCoachModule::respond(const Bottle& command, Bottle& reply) {
        
    reply.clear();

	bool ok = false;
	bool rec = false; // is the command recognised?


    if (command.get(0).asString()=="quit") {
        reply.addString("quitting");
        return false;     
    }
    else if (command.get(0).asString()=="help") {

		reply.addVocab(Vocab::encode("many"));
		reply.addString("One addString for each line");
		return true;
    }
	
	mutex.wait();
	switch (command.get(0).asVocab()) {
	case CMD_START: {
}
		rec = true;
		{
			thread->startBehaviour();
			ok = true;
		}
		break;

	case CMD_STOP:
		thread->stopBehaviour();
		break;
	}
	reply.addVocab(REPLY_OK);
	mutex.post();

	if (!rec) {
		ok = RFModule::respond(command, reply);
	}

	if (!ok) {
		reply.clear();
	}

	return ok;
}

/* Called periodically every getPeriod() seconds */
bool KeeponCoachModule::updateModule()
{
    return true;
}

double KeeponCoachModule::getPeriod()
{
    /* module periodicity (seconds), called implicitly by myModule */
    return 1;
}

