#pragma once

#include "ofMain.h"
#include "ofxAutoControlPanel.h"
#include "ofxOpenCv.h"
//#include "ofxKinect.h"

#include "ofxOpenNI.h"
#include "scanDataPlayer.h"
#include "ofx3dGraphics.h"


class DepthVisualizerInput {
	
public: 
	
	
	
	ofSoundPlayer     mySound1, mySound2,mySound3;

	
	long timePassed(); 
	float determineFactor(long t);
	
	
		
	
	long time; 
	long passedTime;
	long currentTime; 
	long averageBreath; 
	
	int count;
	float mapVal; 
	//float avgBreath; 
	int radc;
	long lastFlicker; 
	long inBetween; 
	long lastBlink; 
	int counterPos;
	int currentPos; 
    int difference;
	long breaths[4];
	int factor; 
	long fast; 
	long fastest; 
	long slow; 
	int sensorThreshold; 
	bool reset;
	bool firstBreath;
	int threshold; 
	int breathFreq; 
	int pos;
	//float radius;
	float counter1; 
	int fact; 
	
	
	
	
	
	
	
	
	
	
	void Sphere1Passive();
	void Sphere1Active();
	void Sphere2Passive();
	void Sphere2Active();
	void Sphere3Passive();
	void Sphere3Active();
	void Sphere4Passive();
	void Sphere4Active();
	void Sphere5Passive();
	void Sphere5Active();
	
	float s1x;
	float s1y;
	float s1z;
	float s2x;
	float s2y;
	float s2z;
	float s3x;
	float s3y;
	float s3z;
	float s4x;
	float s4y;
	float s4z;
	float r1active;
	float r2active;
	float r3active;
	float r4active;
	float r5active;
	float r1passive;
	float r2passive;
	float r3passive;
	float r4passive;
	float r5passive;
	float radius1;
	float radius2;
	float radius3;
	float radius4;
	float radius5;
	float radius;
	
	
	
	
	vector<ofPoint> myLine;
	bool foundUser;
	void rotateToNormal(ofxVec3f normalVec);
	
	//ofTrueTypeFont   font;
	
	

	
	
	
	
	
	// you can get three things from this class
	
	// 1) grayscale depth image
	ofxCvGrayscaleImage depthImage;
	
	// 2) point cloud of projected points
	vector<ofxVec3f> pointCloud;
	
	// 3) same as above, but structured as a grid
	//    empty points are (0,0,0)
	ofxVec3f pointGrid[480][640];
	
	int camWidth, camHeight;
	float rawFarThreshold, rawNearThreshold;
	
	
	scanDataPlayer animation;
	
	ofxControlPanel* panel;
	void setup(ofxControlPanel& panel);
	bool update(); // returns true if this is a new frame
	void drawDebug();
	void drawOrthographic();
	void drawPerspectiveandUser();
	void drawUser();
	
	bool usingKinect();
	void exit();
	
	
	ofxPoint3f getWorldCoordinateFor(float x, float y);
	
	
	// this is from the openNI example
	
	void	setupRecording(string _filename = "");
	void	setupPlayback(string _filename);
	string	generateFileName();
	int mapArray[10]; 
	
	
	float cmDepth [ 640*480 ];
	unsigned char depthConverted[640*480];
	ofTexture temp;
	
	unsigned char grayPixels[640*480];
	
	// this is used by openni to do conversion of coordinates
	XnPoint3D projective[640 * 480];
	XnPoint3D realworld[640 * 480];
	
	bool				isLive, isTracking, isRecording, isCloud, isCPBkgnd, isMasking;
	
	string				currentFileName;
	
	ofxOpenNIContext	recordContext, playContext;
	ofxDepthGenerator	recordDepth, playDepth;
	ofxImageGenerator	recordImage, playImage;
	ofxUserGenerator	recordUser, playUser;
	ofxOpenNIRecorder	oniRecorder;
	
	
	//added these variables based on Eric Mika's Air Accordian 
	
	int handHistoryDepth; 
	vector<ofPoint> leftHandHistory; 
	vector<ofPoint> rightHandHistory; 
	
	ofPoint leftHand; 
	ofPoint rightHand; 
	
	int playDelay; 
	int lastPlay; 
	float 	counter;
	bool	bSmooth;
	bool breathingObject;
	
	int readings[10]; 
	int index; 
	int total; 
	int average;
	
	
	
	
	
protected:
	
	void thresholdDepthImage();
	void buildPointCloud();
	
};