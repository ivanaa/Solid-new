#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	
	
	
//	camWidth 		= 640;	// try to grab at this size. 
//	camHeight 		= 480;
	
	//vidGrabber.setVerbose(true);
	//vidGrabber.initGrabber(camWidth,camHeight);
	
	//videoInverted 	= new unsigned char[camWidth*camHeight*3];
	//videoTexture.allocate(camWidth,camHeight, GL_RGB);

	
	//////////////////////////////////////////////////////////////
	
	
	
	ofSetVerticalSync(true);
	bSendSerialMessage = false;
	serial.enumerateDevices();
	serial.setup("/dev/tty.usbserial-A600ehcA", 9600); // mac osx example

	
	
	
	
	ofSetFrameRate(60);
    interaction4 = false;
	hit = false;
	
	
//	ard.connect("/dev/tty.usbmodemfa141", 9600);
	
//	bSetupArduino	= false;
	
	
	panel.setup("Control Panel", 1024-310, 5, 300, 600);
	
	panel.addPanel("Threshold and Scale");
	panel.addSlider("near threshold", "nearThreshold", 255, 0, 255, true);
	panel.addSlider("far threshold", "farThreshold", 0, 0, 255, true);
	
	panel.addPanel("Control");
	panel.addSlider("scale", "scale", 1, 0, 10);
	panel.addSlider("offset", "offset", -1000,  -2000, 2000);
	panel.addSlider("userOffset", "userOffset", -1000, -2000, 2000);
	panel.addSlider("userScale", "userScale", 3, 1, 25);
	panel.addSlider("rotate y axis", "rotateY", 0, -360, 360, false);	
	panel.addToggle("auto rotate", "autoRotate", false);
	panel.addToggle("draw debug", "drawDebug", false);
	
	panel.addToggle("draw scene bounding frustrum", "drawSceneBox", false);
		
	if (input.usingKinect() == false){
		panel.addSlider("playback speed", "playSpeed", 0.5, -1, 1, false);
		panel.addToggle("playbackPause", "playbackPause", false);
	}
	
	panel.addPanel("Mesh");
	panel.addSlider("vertexStep", "vertexStep", 2, 1, 10, true);
	
	
	input.setup(panel);  // < -- could pass in useKinnect here?
	
	input.isTracking = true; // start tracking people
	//resetAverage();

}




//--------------------------------------------------------------
void testApp::update() {
	
	//bool isFrameNew = input.update();
	
	
	
/*	if ( ard.isArduinoReady()){
		
		// 1st: setup the arduino if haven't already:
		if (bSetupArduino == false){
			setupArduino();
			bSetupArduino = true;	// only do this once
		}
		// 2nd do the update of the arduino
		updateArduino();
		
	}

*/	
	
	
/*	ofBackground(100,100,100);
	
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();
	//	for (int i = 0; i < totalPixels; i++){
//			videoInverted[i] = 255 - pixels[i];
		//}
		//videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
	}
	
	
*/	
	
	
	input.update();	

	////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	
	vector<ofxVec3f>& pointCloud = input.pointCloud;
		for(int i = 0; i < pointCloud.size(); i++) {
		ofPoint cur = pointCloud[i];
		
		//-----------------------------------------ME
		
		
		
		
		//BLUE//////-30
		
	if (cur.z >900 && cur.z<1100) {
			if(cur.x >-100 && cur.x <100) {
				if (cur.y >-100 && cur.y <100) {
					interaction4 =true;
					hit = true;

					
					
				}}}
	

	}
	////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		
		
	//}

		
	}

//--------------------------------------------------------------
void testApp::draw() {
	
	ofBackground(0, 0, 0);
	
		
//ofSetColor(0xffffff);
	
	
	if (bSendSerialMessage){
		
		//serial.available();
		// (1) write the letter "a" to serial:
		serial.writeByte('A');
		
		ofSetColor(0x000000);
		ofRect(10, 10, 50, 50);
		
		cout << "sending"<<endl;

		
	}
	
	
	
	
	else {
		serial.writeByte('b');
		ofSetColor(0xdddddd);
		cout << "stopping"<<endl;

		
	}
	
	
	
	bSendSerialMessage = false;
	

	
	
	
	
	
	
	
	
	//mySound1.play(); //Plays sound
	//-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
	//-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
	//-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
	
	
	
	
/*	if (!ard.isArduinoReady()){
		cout<<"not ready"<<endl;
		
	} else {
		
		
	//	int mapVal = ofMap(float(ard.getAnalog(0)), 0,1023,0,500 );
		
				
			
			if (interaction4 == true) {
			//	ard.sendDigital(13, ARD_HIGH, true);
				serial.writeByte('a');
				
			}
		else {
			//ard.sendDigital(13, ARD_LOW, false);
		//	cout<< "high " << mapVal << endl; 

		}

	*/		
																				 
			
			
			
		    //-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
			//-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
			//-----------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++-------Arduino
			
		//}
		
	
	
	// draw debug or non debug
	
	if (panel.getValueB("drawDebug")){
		input.drawDebug();
		
	} else {
		
		
		

		
		
		ofPushMatrix();
		
			// center everything
			ofTranslate(ofGetWidth()/2, ofGetWidth()/2, -500);
		
			
		
		
		
		
			ofSetColor(255, 255, 255);
			ofRotateY(180 + panel.getValueF("rotateY"));
			if (panel.getValueB("autoRotate")){
				ofRotateY(ofGetElapsedTimef()*5);
			}
			
			ofScale(1, 1, 1);
			float scale = panel.getValueF("scale");
			ofScale(scale, scale, scale);


		
		
		
			int w = input.camWidth;
			int h = input.camHeight;
			
			int vertexStep = 10;
			
			int xMax = w - vertexStep;
			int yMax = h - vertexStep;
			
		
			glEnable(GL_LIGHTING);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHT0);
			glEnable(GL_NORMALIZE);
		//ofNoFill();
			glBegin(GL_LINE_LOOP);
			ofxVec3f zero(0, 0, 0);
			for(int y = 0; y < yMax; y += vertexStep) {
				for(int x = 0; x < xMax; x += vertexStep) {
				
					ofxVec3f& nw = input.pointGrid[y][x];
					ofxVec3f& ne = input.pointGrid[y][x + vertexStep];
					ofxVec3f& se = input.pointGrid[y + vertexStep][x + vertexStep];
					ofxVec3f& sw = input.pointGrid[y + vertexStep][x];
					
					if(nw != 0 && ne != 0 && sw != 0 && se != 0) {

						ofxVec3f right = ne - nw;
						ofxVec3f down = sw - nw;
						ofxVec3f out = down.cross(right);
												
						glNormal3f(out.x, out.y, out.z);						
						glVertex3f(nw.x, nw.y, nw.z);
						glVertex3f(ne.x, ne.y, ne.z);
						glVertex3f(se.x, se.y, se.z);
						glVertex3f(sw.x, sw.y, sw.z);
						
						
						
						//-----------------------------------------------SHADER
						
						//glEnable(GL_LIGHTING);
						//glEnable(GL_DEPTH_TEST);
						//glEnable(GL_LIGHT0);
						//glEnable(GL_NORMALIZE);
						
						GLfloat x;							// Helix x Coordinate
						GLfloat y;							// Helix y Coordinate
						GLfloat z;							// Helix z Coordinate
						GLfloat phi;							// Angle
						GLfloat theta;							// Angle
						GLfloat v,u;							// Angles
						GLfloat r;							// Radius Of Twist
						GLfloat angle;
						int twists = 5;							// 5 Twists
						
						
						
						//angle = -20;
						
						GLfloat glfMaterialColor[]={1.2f,1.1f,1.2f,0.9f};		// Set The Material Color
						GLfloat specular[]={1.0f,1.0f,1.0f,3.2f};			// Sets Up Specular Lighting
						glBlendFunc(GL_SRC_ALPHA,GL_ONE);
												glLoadIdentity();						// Reset The Modelview Matrix
												gluLookAt(0, 0, 0, 00, 0, 0, 0, 1, 0);				// Eye Position (0,5,50) Center Of Scene (0,0,0)
						//						// Up On Y Axis.
						glPushMatrix();							// Push The Modelview Matrix
						//						
												glTranslatef(0,0,-50);						// Translate 50 Units Into The Screen
												glRotatef(angle/2.0f,1,0,0);					// Rotate By angle/2 On The X-Axis
												glRotatef(angle/3.0f,0,1,0);					// Rotate By angle/3 On The Y-Axis
						//						
						glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,glfMaterialColor);
						glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
						glPopMatrix();
						
						
					//---------------------------------------------------
						
						
					
					}
				}
			}
			glEnd();
			
			glDisable(GL_LIGHTING);
			glDisable(GL_DEPTH_TEST);
			
		
			//-------------------------------------------
		
			ofPushMatrix();
			ofTranslate(0, 0, 0);
			input.drawPerspectiveandUser();
		
		
		////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		if (interaction4 == true) {
			ofSetColor(0, 0, 250);
			ofFill();
			ofBox(ofPoint(0,0,1000),200);
			//	mySound1.play(); //Plays sound
			bSendSerialMessage = true;

		}
		
		else{
			ofSetColor(0, 0, 250);
			ofNoFill();
			ofBox(ofPoint(0,0,1000),200);
			bSendSerialMessage = false;

			
		}
	
		////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			ofPopMatrix();
			
			ofPushMatrix();
			ofTranslate(0, 0, panel.getValueF("userOffset"));
			ofScale(3, 3, panel.getValueF("userScale"));
			//input.drawUser();
		//input.maskUser();
		
			ofPopMatrix();
			
		ofPopMatrix();
		
	}
		interaction4 =false;
}

/*	//--------------------------------------------------------------
void testApp::setupArduino(){
		
		
		
		// this is where you setup all the pins and pin modes, etc
		for (int i = 0; i < 13; i++){
			ard.sendDigitalPinMode(i, ARD_OUTPUT);
		}
		
		ard.sendDigitalPinMode(13, ARD_OUTPUT);
		//ard.sendAnalogPinReporting(0, ARD_ANALOG);	// AB: report data
	//	ard.sendDigitalPinMode(11, ARD_PWM);		// on diecimelia: 11 pwm?
		
		
	}
	
	
	 
	//--------------------------------------------------------------
	
	
void testApp::updateArduino(){
		
		// update the arduino, get any data or messages:
		ard.update();
		//ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));  // pwm...
		
	}
	
*/	
	//--------------------------------------------------------------	
	
//--------------------------------------------------------------
void testApp::exit() {
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
		case ' ':
			interaction4 =true;
			break;    
	 
	}
	
	
	
	
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	//bSendSerialMessage = true;

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
	//bSendSerialMessage = false;

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
}

