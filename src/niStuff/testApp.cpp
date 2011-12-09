#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
	
	
	
	isLive		= true;
	isTracking	= false;
	isRecording = false;
	isCloud		= false;
	isCPBkgnd	= true;
	isMasking   = true;
	
	//TM.setup();	

	ofBackground(0, 0, 0);
	
	temp.allocate(640,480, GL_LUMINANCE);
	setupRecording();
		
}

void testApp::setupRecording(string _filename) {
	
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

void testApp::setupPlayback(string _filename) {
	
	playContext.clear();
	playContext.setupUsingRecording(ofToDataPath(_filename));
	playDepth.setup(&playContext);
	playImage.setup(&playContext);
	playUser.setup(&playContext, &playDepth, &playImage);
	
	
	playDepth.toggleRegisterViewport(&playImage);
	playContext.toggleMirror();
	
}



//--------------------------------------------------------------
void testApp::update(){
	

	
	xn::DepthMetaData dmd;
	recordDepth.getXnDepthGenerator().GetMetaData(dmd);	
	const XnDepthPixel* depth = dmd.Data();
	
	int count = 0;
	for (XnUInt16 y = dmd.YOffset(); y < dmd.YRes() + dmd.YOffset(); y++) {
		for (XnUInt16 x = 0; x < dmd.XRes(); x++){
			cmDepth[count] = ((int)*depth) / 10.0f;
			
			count++;
			depth++;
		}
	}
	
	for (int i = 0; i < 640*480; i++){
		
		
		grayPixels[i] = (recordImage.image_pixels[(i*3)] +recordImage.image_pixels[(i*3)+1] +recordImage.image_pixels[(i*3)+2])/3 ;
	}
	
		
	for (int i = 0; i < 640*480; i++){
		if (cmDepth[i] < 4) {
			depthConverted[i] = 0;
		} else {
			depthConverted[i] =  (int)ofMap(cmDepth[i], 200,60, 0,255, true);
		}
	}
	
		
	temp.loadData(depthConverted, 640, 480, GL_LUMINANCE);
		
	if (isLive) {
		recordContext.update();
		if (isTracking) recordUser.update();
	} else {
		playContext.update();
		if (isTracking) playUser.update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	
	
	
	ofEnableAlphaBlending();
	
	ofSetColor(255, 255, 255);
	
	temp.draw(0,0,640,480);
	//recordDepth.draw(0,0,640,480);
	
	ofSetColor(255, 255, 255, mouseX);
	
	recordImage.draw(0, 0, 640, 480);
				

	ofSetColor(255,255,255);	
	
	ofSetColor(255,0,0);
	ofBeginShape();
	ofNoFill();
	
	
	
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

string testApp::generateFileName() {
	
	string _root = "kinectRecord";
	
	string _timestamp = ofToString(ofGetDay()) + 
						ofToString(ofGetMonth()) +
						ofToString(ofGetYear()) +
						ofToString(ofGetHours()) +
						ofToString(ofGetMinutes()) +
						ofToString(ofGetSeconds());
	
	string _filename = (_root + _timestamp + ".oni");
	
	return _filename;
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
	if (isLive && isCloud) {
		recordUser.setPointCloudRotation(x);
	} else if (!isLive && isCloud) {
		playUser.setPointCloudRotation(x);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

