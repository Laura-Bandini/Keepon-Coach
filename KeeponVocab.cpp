#include <KeeponVocab.h>


// Generate Vocab Sequence
std::vector<int> playSoundV(int soundID){

	vector<int> vocab;
	vocab.push_back(VOCAB_SOUND);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_PLAY);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(soundID);

    //string vocab = VOCAB_SOUND + VOCAB_SEP + VOCAB_PLAY + VOCAB_SEP + to_string(soundID);
    return vocab;
}

std::vector<int> delaySoundV(int soundID){
    //string vocab = VOCAB_SOUND + VOCAB_SEP + VOCAB_DELAY + VOCAB_SEP + to_string(soundID);

	vector<int> vocab;
	vocab.push_back(VOCAB_SOUND);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_DELAY);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(soundID);

    return vocab;
}

std::vector<int> repeatSoundV(int soundID){
    //string vocab = VOCAB_SOUND + VOCAB_SEP + VOCAB_REPEAT + VOCAB_SEP + to_string(soundID);

	vector<int> vocab;
	vocab.push_back(VOCAB_SOUND);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_REPEAT);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(soundID);
    return vocab;
}

std::vector<int> stopSoundV(){
    //string vocab = VOCAB_SOUND + string(" ") + VOCAB_STOP;

	vector<int> vocab;
	vocab.push_back(VOCAB_SOUND);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_STOP);

    return vocab;
}


std::vector<int> setSpeedPanV(int speed){
    //string vocab = VOCAB_SPEED + VOCAB_SEP + VOCAB_PAN + VOCAB_SEP + to_string(speed);

	vector<int> vocab;
	vocab.push_back(VOCAB_SPEED);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_PAN);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(speed);

    return vocab;
}
std::vector<int> setSpeedTiltV(int speed){
    //string vocab = VOCAB_SPEED + VOCAB_SEP + VOCAB_TILT + VOCAB_SEP + to_string(speed);

	vector<int> vocab;
	vocab.push_back(VOCAB_SPEED);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_TILT);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(speed);
    return vocab;
}
std::vector<int> setSpeedSideV(int speed){
    //string vocab = VOCAB_SPEED + VOCAB_SEP + VOCAB_SIDE + VOCAB_SEP + to_string(speed);

	vector<int> vocab;
	vocab.push_back(VOCAB_SPEED);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_PON);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(speed);

    return vocab;
}

std::vector<int> movePanV(int position){
    //string vocab = VOCAB_MOVE + VOCAB_SEP + VOCAB_PAN + VOCAB_SEP + to_string(position);

	vector<int> vocab;
	vocab.push_back(VOCAB_MOVE);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_PAN);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(position);

    return vocab;
}
std::vector<int> moveTiltV(int position){
    //string vocab = VOCAB_MOVE + VOCAB_SEP + VOCAB_TILT + VOCAB_SEP + to_string(position);

	vector<int> vocab;
	vocab.push_back(VOCAB_MOVE);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_TILT);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(position);

    return vocab;
}
std::vector<int> movePonV(PonPos position){
    //string vocab =  VOCAB_MOVE + VOCAB_SEP + VOCAB_PON + VOCAB_SEP + ponPosToVocab(position);

	vector<int> vocab;
	vocab.push_back(VOCAB_MOVE);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_PON);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(ponPosToVocab(position));

    return vocab;
}

std::vector<int> moveSideV(PonPos position) {
	//string vocab =  VOCAB_MOVE + VOCAB_SEP + VOCAB_PON + VOCAB_SEP + ponPosToVocab(position);

	vector<int> vocab;
	vocab.push_back(VOCAB_MOVE);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_SIDE);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(ponPosToVocab(position));

	return vocab;
}

std::vector<int> moveStopV(){
    //string vocab = VOCAB_MOVE + VOCAB_SEP + VOCAB_STOP;

	vector<int> vocab;
	vocab.push_back(VOCAB_MOVE);
	//vocab.push_back(VOCAB_SEP);
	vocab.push_back(VOCAB_STOP);

    return vocab;
}

//string echoV(char* singleWord){
//    string vocab = VOCAB_ECHO + VOCAB_SEP + string(singleWord);
//    return vocab;
//}

std::vector<int> senseV(bool state){
    //string vocab = VOCAB_SENSE + VOCAB_SEP;


	vector<int> vocab;
	vocab.push_back(VOCAB_SENSE);
	//vocab.push_back(VOCAB_SEP);

	if (state)
		vocab.push_back(VOCAB_ON);
	else
		vocab.push_back(VOCAB_OFF);


    return vocab;
}

// Generate Command Sequence
string playSoundC(int soundID){
    string cmd = COMMAND_SOUND + COMMAND_SEP + COMMAND_PLAY + " " + to_string(soundID) + COMMAND_END;
    return cmd;
}
string delaySoundC(int soundID){
    string cmd = COMMAND_SOUND + COMMAND_SEP + COMMAND_DELAY + " " + to_string(soundID) + COMMAND_END;
    return cmd;
}
string repeatSoundC(int soundID) {
    string cmd = COMMAND_SOUND + COMMAND_SEP + COMMAND_REPEAT + " " + to_string(soundID) + COMMAND_END;
    return cmd;
}
string stopSoundC(){
    string cmd = COMMAND_SOUND + COMMAND_SEP + COMMAND_STOP + COMMAND_END;
    return cmd;
}

string setSpeedPanC(int speed){
    string cmd = COMMAND_SPEED + COMMAND_SEP + COMMAND_PAN + " " + to_string(speed) + COMMAND_END;
    return cmd;
}
string setSpeedTiltC(int speed){
    string cmd = COMMAND_SPEED + COMMAND_SEP + COMMAND_TILT + " " + to_string(speed) + COMMAND_END;
    return cmd;
}
string setSpeedSideC(int speed){
    string cmd = COMMAND_SPEED + COMMAND_SEP + COMMAND_SIDE + " " + to_string(speed) + COMMAND_END;
    return cmd;
}

string movePanC(int position){
    string cmd = COMMAND_MOVE + COMMAND_SEP + COMMAND_PAN + " " + to_string(position) + COMMAND_END;
    return cmd;
}
string moveTiltC(int position){
    string cmd = "";
    cmd += COMMAND_MOVE + COMMAND_SEP + COMMAND_TILT + " " + to_string(position) + COMMAND_END;
    return cmd;
}
string movePonC(PonPos position){
    string cmd = COMMAND_MOVE + COMMAND_SEP + COMMAND_PON + " " + ponPosToCommand(position) + COMMAND_END;
    return cmd;
}
string moveStopC(){
    string cmd = COMMAND_MOVE + COMMAND_SEP + COMMAND_STOP + COMMAND_END;
    return cmd;
}

string echoC(char* singleWord){
    string cmd = COMMAND_ECHO + COMMAND_SEP + " " + string(singleWord) + COMMAND_END;
    return cmd;
}
string senseC(bool state){
    string cmd = COMMAND_SENSE + COMMAND_SEP;
    if(state)
        cmd += "ON";
    else
        cmd += "OFF";

    return cmd;
}

int ponPosToVocab(PonPos pos) {
	switch (pos) {
	case UP: return VOCAB_UP;
	case HALFDOWN: return VOCAB_DOWN;
	case DOWN: return VOCAB_HALFDOWN;
	case HALFUP: return VOCAB_HALFUP;
	case CYCLE: return VOCAB_CYCLE;
	case CENTERFROMLEFT: return VOCAB_CEFL;
	case RIGHT: return VOCAB_RIGHT;
	case CENTERFROMRIGHT: return VOCAB_CEFR;
	case LEFT: return VOCAB_LEFT;
	}
}

string ponPosToCommand(PonPos pos) {
	switch (pos) {
	case UP: return COMMAND_UP;
	case HALFDOWN: return COMMAND_DOWN;
	case DOWN: return COMMAND_HALFDOWN;
	case HALFUP: return COMMAND_HALFUP;
	case CYCLE: return COMMAND_CYCLE;
	case CENTERFROMLEFT: return COMMAND_CEFL;
	case RIGHT: return COMMAND_RIGHT;
	case CENTERFROMRIGHT: return COMMAND_CEFR;
	case LEFT: return COMMAND_LEFT;
	}
}

/*
int main(int argc, char * argv[])
{
	
	printf("%s\n", playSoundV(100));
	printf("%s\n", delaySoundV(100));
	printf("%s\n", repeatSoundV(100));
	printf("%s\n", stopSoundV());
	printf("%s\n", setSpeedPanV(100));
	printf("%s\n", setSpeedTiltV(100));
	printf("%s\n", setSpeedSideV(100));
	printf("%s\n", movePanV(100));
	printf("%s\n", moveTiltV(100));
	printf("%s\n", movePonV(PonPos::CENTERFROMLEFT));
	printf("%s\n", moveStopV());
	printf("%s\n", echoV("ciao"));
	printf("%s\n", senseV(true));
	
	printf("%s\n", "=================");
	
	printf("%s\n", playSoundC(100));
	printf("%s\n", delaySoundC(100));
	printf("%s\n", repeatSoundC(100));
	printf("%s\n", stopSoundC());
	printf("%s\n", setSpeedPanC(100));
	printf("%s\n", setSpeedTiltC(100));
	printf("%s\n", setSpeedSideC(100));
	printf("%s\n", movePanC(100));
	printf("%s\n", moveTiltC(100));
	printf("%s\n", movePonC(PonPos::CENTERFROMLEFT));
	printf("%s\n", moveStopC());
	printf("%s\n", echoC("ciao"));
	printf("%s\n", senseC(true));
	

	return 0;
}
*/