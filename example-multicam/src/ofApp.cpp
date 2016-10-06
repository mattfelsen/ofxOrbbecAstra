//
//  ofApp.cpp
//  example
//
//  Created by Matt Felsen on 11/15/15.
//
//

#include "ofApp.h"

void ofApp::setup(){
    
	ofBackground(0);
	ofSetWindowShape(640*2, 480 * 2);
	ofSetVerticalSync(true);


	bUseRegistration = false;

	astra1.setup("device/sensor0");
	astra1.enableRegistration(bUseRegistration);
	astra1.initDepthStream();
    astra1.setDepthClipping(300, 5000);
    
    astra2.setup("device/sensor1");
    astra2.enableRegistration(bUseRegistration);
    astra2.initDepthStream();
    astra2.setDepthClipping(300, 5000);

    astra3.setup("device/sensor2");
    astra3.enableRegistration(bUseRegistration);
    astra3.initDepthStream();
    astra3.setDepthClipping(300, 5000);
    
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));

	astra1.update();
    astra2.update();
    astra3.update();
    
}

void ofApp::draw(){


    ofSetColor(ofColor::white);
    astra1.drawDepth(0, 0);
    astra2.drawDepth(640, 0);
    astra3.drawDepth(0, 480);


	stringstream ss;
	ss << "r: toggle registration between color & depth images (";
	ss << (bUseRegistration ? "on)" : "off)") << endl;


	ofSetColor(ofColor::red);
	ofDrawBitmapStringHighlight(ss.str(), 20, ofGetHeight() - 30);

}

void ofApp::keyPressed(int key){

	if (key == 'r') {
		bUseRegistration ^= 1;
		astra1.enableRegistration(bUseRegistration);
		astra2.enableRegistration(bUseRegistration);
        astra3.enableRegistration(bUseRegistration);
    }
}
