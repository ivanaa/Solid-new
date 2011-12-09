#include "DepthVisualizerInput.h"
#include "testApp.h"

const int useKinect = true;

bool DepthVisualizerInput::usingKinect(){
	return useKinect;
}
//---------------------------------------------------------------------------------
void DepthVisualizerInput::setup(ofxControlPanel& panel){
	
	
	
//	mySound1.loadSound("1.wav");
//	mySound2.loadSound("2.wav");
//	mySound3.loadSound("3.wav");
	
	
	slow = 6;
	fast = 4;
	fastest = 2;
	
	s1x = -100;
	s1y = 0;
	s1z = 400;
	s2x = -100;
	s2y = -200;
	s2z = 700;
	s3x = 100;
	s3y = 200;
	s3z = 100;
	s4x =270;
	s4y = 30;
	s4z = 850;
	
	
//	radius1 = r1active;
//	radius2 = r2active;
//	radius3 = r3active;
//	radius4 = r4active;
//	radius5 = r5active;
	
	
	
	foundUser = false;
	counter = 0;
	radius = 200 + 10 * sin(counter);
	
	int numReadings; 
	
	int readings[numReadings]; 
	int index = 0; 
	int total = 0; 
	int average = 0; 
	
		
	
	
	
	//---------------------------------------------------------------------------------------------+++++++++++++++++++-arduino
	//---------------------------------------------------------------------------------------------+++++++++++++++++++-arduino
	//---------------------------------------------------------------------------------------------+++++++++++++++++++-arduino
	//---------------------------------------------------------------------------------------------+++++++++++++++++++-arduino

	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	
	
//	font.loadFont("FranklinGothic.otf", 20);
	
//	ard.connect("/dev/tty.usbmodemfa141", 57600);
	
//	bSetupArduino	= false;
	
	
	//---------------------------------------------------------------------------------

	
	
mySound1.loadSound("1.mp3");
	mySound2.loadSound("2.wav");
	mySound3.loadSound("3.wav");
	//mySound4.loadSound("br1.mp3");

	
	
	
	
	
	
	ofSetCircleResolution(50);
	//ofBackground(255,255,255);
	bSmooth = false;
	
	
	this->panel = &panel;
	
	camWidth = 640;
	camHeight = 480;
	
	depthImage.allocate(camWidth, camHeight);
	
	if(useKinect) {
		
		isLive		= true;
		isTracking	= true;
		isRecording = false;
		isCloud		= false;
		isCPBkgnd	= false;
		isMasking   = false;
		
		setupRecording();
		
		// this is setting the raw data conversion range
		// we assume that 100 to 300 CM (1 - 3 meters) is good for tracking a person in space
		rawNearThreshold = 20;
		rawFarThreshold = 300;
		///kinect.getCalibration().setClippingInCentimeters(rawNearThreshold, rawFarThreshold);
		
		handHistoryDepth = 10; //store the last 10 hand poistions, newest first
		//playDelay = 10; 
		//lastPlay = 0; 
		
		
	} else {
		rawNearThreshold = 100;
		rawFarThreshold = 300;
		animation.load("kinectScan");
		cout << "Animation length is " << animation.size() << " frames." << endl;
	}
	
	for(int y = 0; y < camHeight; y++) {
		for(int x = 0; x < camWidth; x++) {
			pointGrid[y][x].set(0, 0, 0);
		}
	}
}


// should return in meters, returns x, y, and z 
ofxPoint3f DepthVisualizerInput::getWorldCoordinateFor(float x, float y){
	int xi = ofClamp((int) x, 0, 640);
	int yi = ofClamp((int) y, 0, 480);
	
	
	ofxPoint3f result;
	
	xn::DepthGenerator dg = recordDepth.getXnDepthGenerator(); 
	
	const XnDepthPixel* pDepthMap = dg.GetDepthMap(); 
	
	// Populating the small array to be converted to real world measurements 
	XnPoint3D proj[1]; 
	proj[0].X = xi; 
	proj[0].Y = yi;
	proj[0].Z = pDepthMap[yi * 640 + xi]; 
	
	// Array to store real world values into 
	XnPoint3D realworld[1];
	dg.ConvertProjectiveToRealWorld(1, proj, realworld); 
	
	float millimetersToMeters = 1.0 / 1000.0;
	result.x =  realworld[0].X * millimetersToMeters;
	result.y = -realworld[0].Y * millimetersToMeters; // OpenNI uses inverted y axis now (y is up)
	result.z =  realworld[0].Z * millimetersToMeters;
	
	return result;
	
	
	
}


//---------------------------------------------------------------------------------


void DepthVisualizerInput::setupRecording(string _filename) {
	
	if (!recordContext.isInitialized()) {
		
		recordContext.setup();
		recordContext.setupUsingXMLFile();
		recordDepth.setup(&recordContext);
		recordImage.setup(&recordContext);
		
		recordUser.setup(&recordContext, &recordDepth, &recordImage);
		
		recordDepth.toggleRegisterViewport(&recordImage);
		recordContext.toggleMirror();
		
		oniRecorder.setup(&recordContext, &recordDepth, &recordImage);	
		
	} else {
		
		currentFileName = _filename;
		cout << currentFileName << endl;
	}
	
}
//---------------------------------------------------------------------------------

void DepthVisualizerInput::setupPlayback(string _filename) {
	
	playContext.clear();
	playContext.setupUsingRecording(ofToDataPath(_filename));
	playDepth.setup(&playContext);
	playImage.setup(&playContext);
	playUser.setup(&playContext, &playDepth, &playImage);
	
	
	playDepth.toggleRegisterViewport(&playImage);
	playContext.toggleMirror();
	
}


bool DepthVisualizerInput::update(){
	
	
	
	
	
	
	//---------------------------------------------------------------------------------arduino
	
/*	
	if ( ard.isArduinoReady()){
		
		// 1st: setup the arduino if haven't already:
		if (bSetupArduino == false){
			setupArduino();
			bSetupArduino = true;	// only do this once
		}
		// 2nd do the update of the arduino
		updateArduino();
		
	}
	//---------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//---------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//---------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//---------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//---------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	

*/	
	
	
	counter1 = counter1 - 0.063f;

	counter = counter - 0.043f;

	
	bool isFrameNew = false;
	
	if(useKinect) {
		
		xn::DepthMetaData dmd;
		recordDepth.getXnDepthGenerator().GetMetaData(dmd);	
		const XnDepthPixel* depth = dmd.Data();
		
		int count = 0;
		
		
		for (int i = 0; i < 640*480; i++){
			cmDepth[count] = ((int)*depth) / 10.0f; // convert mm -> cm
			
			count++;
			depth++;
		}
		
		
		
		for (int i = 0; i < 640*480; i++){
			if (cmDepth[i] < rawNearThreshold || cmDepth[i] > rawFarThreshold) {
				depthConverted[i] = 0;
			} else {
				depthConverted[i] =  (unsigned char) ofMap(cmDepth[i], rawFarThreshold, rawNearThreshold, 0, 255, true);
			}
		}
		
		
		//temp.loadData(depthConverted, 640, 480, GL_LUMINANCE);
		
		if (isLive) {
			recordContext.update();
			if (isTracking) recordUser.update();
			
			for(int i = 0; i < recordUser.getTrackedUsers().size(); i++){
				ofxTrackedUser* tracked = recordUser.getTrackedUser(i);
				
				if(tracked!=NULL && tracked->left_upper_torso.found&& tracked->right_upper_torso.found){
					leftHand = tracked->left_upper_torso.end; 
					rightHand = tracked->right_upper_torso.end; 
					cout << "found torso" << endl; 
					break;
					
				}
			}
			
			//add hand positions to history
			if(leftHandHistory.size() <= handHistoryDepth) {
				leftHandHistory.insert(leftHandHistory.begin(), leftHand); 
			}
			
			if(rightHandHistory.size() <= handHistoryDepth){
				rightHandHistory.insert(rightHandHistory.begin(), rightHand); 
			}
			
			if(leftHandHistory.size() > handHistoryDepth){
				leftHandHistory.pop_back(); 
			}
			
			if(rightHandHistory.size() > handHistoryDepth){
				rightHandHistory.pop_back(); 
			}
			
			
			
			
			
		} else {
			playContext.update();
			if (isTracking) playUser.update();
			for(int i = 0; i < recordUser.getTrackedUsers().size(); i++){
				ofxTrackedUser* tracked = recordUser.getTrackedUser(i);
				
				if(tracked!=NULL && tracked->left_lower_torso.found&& tracked->right_lower_torso.found){
					leftHand = tracked->left_lower_torso.end; 
					rightHand = tracked->right_lower_torso.end; 
					cout << "found torso" << endl; 
					break;
					
				}
			}
			
			//add hand positions to history
			if(leftHandHistory.size() <= handHistoryDepth) {
				leftHandHistory.insert(leftHandHistory.begin(), leftHand); 
			}
			
			if(rightHandHistory.size() <= handHistoryDepth){
				rightHandHistory.insert(rightHandHistory.begin(), rightHand); 
			}
			
			if(leftHandHistory.size() > handHistoryDepth){
				leftHandHistory.pop_back(); 
			}
			
			if(rightHandHistory.size() > handHistoryDepth){
				rightHandHistory.pop_back(); 
			}
		}
		
		
		
		
		if(true) {  // is there an openNI is frame new function?
			isFrameNew = true;
			depthImage.setFromPixels(depthConverted, camWidth, camHeight);
			depthImage.flagImageChanged();
		}
		
	} else {
		
		/*
		 
		 if(panel->getValueB("playbackPause")) {
		 animation.setPlaySpeed(0);
		 } else {
		 animation.setPlaySpeed(panel->getValueF("playSpeed"));
		 }
		 
		 if(animation.isFrameNew()) {
		 isFrameNew = true;
		 ofImage& cur = animation.getAlpha();
		 depthImage.setFromPixels(cur.getPixels(), cur.getWidth(), cur.getHeight());
		 depthImage.flagImageChanged();
		 }
		 */
	}
	
	if(isFrameNew) {
		thresholdDepthImage();
		buildPointCloud();
	}
	
	
	return isFrameNew;
}
//---------------------------------------------------------------------------------

void DepthVisualizerInput::thresholdDepthImage() {
	// do processing here on depthImage
	// getting rid of (setting depth = 0) on pixels we don't care about
	// for example, background, etc. 
	
	
	unsigned char* depthPixels = depthImage.getPixels();
	int nearThresh = panel->getValueF("nearThreshold");
	int farThresh = panel->getValueF("farThreshold");
	
	for(int y = 0; y < camHeight; y++) {
		for(int x = 0; x < camWidth; x++) {
			int i = y * camWidth + x;
			if (depthPixels[i] <  farThresh  || depthPixels[i] > nearThresh){
				depthPixels[i] = 0;
			}
		}
	}
}
//---------------------------------------------------------------------------------

void DepthVisualizerInput::buildPointCloud() {	
	unsigned char* depthPixels = depthImage.getPixels();
	
	// generate the point cloud
	if(useKinect) {
		xn::DepthGenerator dg = recordDepth.getXnDepthGenerator(); 
		const XnDepthPixel* pDepthMap = dg.GetDepthMap(); 
		
		int i = 0;
		int j = 0;
		for(int y = 0; y < camHeight; y++) {
			for(int x = 0; x < camWidth; x++) {
				if(depthPixels[i] != 0) {
					projective[j].X = x;
					projective[j].Y = y;
					projective[j].Z = pDepthMap[i];
					j++;
				}
				i++;
			}
		}
		
		dg.ConvertProjectiveToRealWorld(j, projective, realworld);
		
		pointCloud.resize(j);
		
		i = 0;
		j = 0;
		for(int y = 0; y < camHeight; y++) {
			for(int x = 0; x < camWidth; x++) {
				
				if(depthPixels[i] != 0) {
					pointCloud[j].x =  realworld[j].X;
					pointCloud[j].y = -realworld[j].Y; // OpenNI uses inverted y axis now (y is up)
					pointCloud[j].z =  realworld[j].Z;
					
					pointGrid[y][x].set(pointCloud[j]);
					
					j++;
				} else {
					pointGrid[y][x].set(0, 0, 0); // start as 0
				}
				i++;
			}
		}
			}
	}
//---------------------------------------------------------------------------------

void DepthVisualizerInput::drawOrthographic() {
	;  // this needs to be done, from the depth image. 
}
//---------------------------------------------------------------------------------

void DepthVisualizerInput::drawPerspectiveandUser() {
	//getWorldCoordinatesFor();
	glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, sizeof(ofxVec3f), &(pointCloud[0][0]));++++++++++++++++++++++++++++++++++++++POINT CLOUD BEIGN DRAWN
	glDrawArrays(GL_POINTS, 0, pointCloud.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	
	
	mySound1.play(); //Plays sound
	//-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
	//-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
	//-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino

/*	

		
		if (!ard.isArduinoReady()){
			cout<<"not ready"<<endl;
			
		} else {
			
			
			int mapVal = ofMap(float(ard.getAnalog(0)), 0,1023,0,500 );
			
							
			{
			
				
				ofCircle(300, 300, mapVal);			
				cout<< "val is " << mapVal << endl; 																			 
																 
			
	
	//------------------------------------------------------------------------------------------Arduino	
	//-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
    //-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
			
}
 
 */
}
	

//---------------------------------------------------------------------------------

void DepthVisualizerInput::drawDebug(){
	
	//ofTranslate((ofGetWidth() - camWidth) / 2, 0, 0);
	ofSetColor(255, 255, 255);
	depthImage.draw(0, 0);
	
	ofPushMatrix();
	
	ofTranslate(camWidth/2.0, ofGetHeight()*0.85, -500);
	ofRotateY(panel->getValueF("rotateY"));
	if (panel->getValueB("autoRotate")){
		ofRotateY(ofGetElapsedTimef()*5);
	}
	ofScale(2,2,2);
	
	
	// need something here....
	drawPerspectiveandUser();
	
	ofPopMatrix();
	
}


//--------------------------------------------------------------
void DepthVisualizerInput::exit() {
	if(useKinect) {
		//kinect.close();
	}
}

/*

//--------------------------------------------------------------
void DepthVisualizerInput::setupArduino(){
	
	
	
	// this is where you setup all the pins and pin modes, etc
	for (int i = 0; i < 13; i++){
		ard.sendDigitalPinMode(i, ARD_OUTPUT);
	}
	
	ard.sendDigitalPinMode(13, ARD_OUTPUT);
	ard.sendAnalogPinReporting(0, ARD_ANALOG);	// AB: report data
	ard.sendDigitalPinMode(11, ARD_PWM);		// on diecimelia: 11 pwm?
	
	
}



//--------------------------------------------------------------


void DepthVisualizerInput::updateArduino(){
	
	// update the arduino, get any data or messages:
	ard.update();
	ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));  // pwm...
	
}

*/
//--------------------------------------------------------------

void  DepthVisualizerInput::rotateToNormal(ofxVec3f normalVec) {
	normalVec.normalize();
	
	float rotationAmount;
	ofxVec3f rotationAngle;
	ofxQuaternion rotation;
	
	ofxVec3f xaxis(0, 0, 1);
	rotation.makeRotate(xaxis, normalVec);
	rotation.getRotate(rotationAmount, rotationAngle);
	ofRotate(ofRadToDeg(rotationAmount), rotationAngle.x, rotationAngle.y, rotationAngle.z);
}

//--------------------------------------------------------------


float DepthVisualizerInput::determineFactor(long t){
	
	float factor;
	
	if(t > slow && t < fastest){
		factor = 1; 
	}
	if( t > fast && t < fastest){
		factor = 2; 
	}
	if( t > fastest) {
		factor = 1; 
	}
	
	return factor; 
	
	/*
	 radc = radc + 0.033f; 
	 ofSetColor(255, 130, 0); 
	 ofFill(); 
	 float radius = 50 + 10 * sin(radc)*factor;  
	 ofCircle(200, 200, radius);  */
	
}
	

//--------------------------------------------------------------


long DepthVisualizerInput::timePassed(){
	
	currentTime = ofGetElapsedTimeMillis(); 
	
	time = currentTime - passedTime; 
	
	passedTime = currentTime; 
	
	
} 
