#pragma once

#include "ofMain.h"

#include "ofxAutoControlPanel.h"
#include "DepthVisualizerInput.h"

#include "ofxOpenNI.h"
//#include "Particle.h"
//#include "ParticleEmitter.h"


class testApp : public ofBaseApp {
	
	public:

		void setup();
		void update();
		void draw();
		void exit();
	
	
	
	void resetAverage();
	
	
	
	
	
	
	
	bool		bSendSerialMessage;			// a flag for sending serial
	char		bytesRead[3];				// data from serial, we will be trying to read 3
	char		bytesReadString[4];			// a string needs a null terminator, so we need 3 + 1 bytes
	int			nBytesRead;					// how much did we read?
	int			nTimesRead;					// how many times did we read?
	float		readTime;					// when did we last rea
	

	ofSerial	serial;

	
	
	
	
	
	
	
	
	void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		ofxAutoControlPanel panel;
	
		DepthVisualizerInput input;
	DepthVisualizerInput  isTracking;
	
	int handHistoryDepth;
	vector<ofPoint> leftHandHistory;
	vector<ofPoint> rightHandHistory;	
	
	ofPoint leftHand;
	ofPoint rightHand;
	ofxVec3f summedGrid[480][640];
	unsigned int summedCount[480][640];
	ofxVec3f averagedGrid[480][640];
	
	bool interaction4;
	ofPoint   cur;
	bool hit;
	
//	void setupArduino();
//	void updateArduino();
	
//	ofArduino  ard;
//	bool bSetupArduino;
	//ofTrueTypeFont   font;
	float mapVal; 

	
	
	ofVideoGrabber 		vidGrabber;
	unsigned char * 	videoInverted;
	ofTexture			videoTexture;
	int 				camWidth;
	int 				camHeight;
	
	
	
};
