#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);

	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;
	recording = false;
	playing = false;
	pause = false;
	recordTimer = 30;
	keys = "";

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles()
{

	//these are the attraction points used in the fourth demo
	attractPoints.clear();
	for (int i = 0; i < 4; i++)
	{
		attractPoints.push_back(glm::vec3(ofMap(i, 0, 4, 100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100), 0));
	}

	attractPointsWithMovement = attractPoints;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	if(playing)
	{
		if(keys.size() == 0){
			playing = false;
		}
		if(playTimer > 0){
			playTimer--;
		}
		else{
			playKey(keys[0]);
			keys = keys.substr(1);
			playTimer = 60 * 3;
		}
	}
	if(pause) return;
	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].update();
	}
	if (currentMode == PARTICLE_IS || currentMode == PARTICLE_DS)
	{ //vmmo
		currentMode = previousMode;
	}

	if (currentMode == PARTICLE_IV || currentMode == PARTICLE_DV)
	{ //vmmo
		currentMode = previousMode;
	}

	//lets add a bit of movement to the attract points
	for (unsigned int i = 0; i < attractPointsWithMovement.size(); i++)
	{
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient(ofColor(0, 149, 246), ofColor(0, 60, 136)); //Decidimos cambiar el background por ultima vez :) -vmmo

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].draw();
	}

	ofSetColor(190);
	if (currentMode == PARTICLE_MODE_NEAREST_POINTS)
	{
		for (unsigned int i = 0; i < attractPoints.size(); i++)
		{
			ofNoFill();
			ofDrawTriangle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode. \nOther keys: \nPause(A), \nSize Increase(I), \nSize Decrease(D), \nVelocity Increase(F), \nVelocity Decrease(S), \nRecord(R), \nReplay Recording(P), \nCancel Replay(C) " + "\nRecorded keys: " + keys, 10, 20);

	ofSetColor(255, 191, 0); // vmmo
	if (recording)
	{
		if (recordTimer > 0)
		{
			if (recordTimer > 15)
			{
				ofFill();
				ofDrawCircle(980, 40, 20);
			}
			recordTimer--;
		}
		else
		{
			recordTimer = 30;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (recording)
	{
		if (key == 'r')
		{
			recording = false;
			keys = "";
		}

		        else if (key == 'p')
        {
            playing = true;
            recording = false;
        }

		else
		{
			if(key == '1' || key == '2' || key == '3' || key == '4' || key == 'a' || key == 's' || key == 'f' || key == 'd' || key == 'i' || key == ' '){
				keys += key;
			}
		}
	}
	
    else if(!playing || key == 'c')
    {
        playKey(key);
    }
}


void ofApp::playKey(int key)
{
	if (key == '1')
	{
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	}

	if (key == '2')
	{
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
	}

	if (key == '3')
	{
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
	}

	if (key == '4')
	{
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
	}

	if( key == 'a'){//kiwi
		if(pause){
			pause = false;
		}
		else{
			pause = true;
		}
	}

	if (key == 'i')
	{
		previousMode = currentMode;
		currentMode = PARTICLE_IS;
	}

	if (key == 'd')
	{
		previousMode = currentMode;
		currentMode = PARTICLE_DS;
	}

	if (key == 'f')
	{ // vmmo
		previousMode = currentMode;
		currentMode = PARTICLE_IV;
	}

	if (key == 's')
	{ // vmmo
		previousMode = currentMode;
		currentMode = PARTICLE_DV;
	}

	if (key == 'r')
	{ // vmmo
		recording = true;
	}

	if (key == 'c'){
		playing = false;
		keys = "";
	}


	if (key == ' ')
	{
		resetParticles();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
