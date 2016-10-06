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

	vector<string> devices = {
		"device/sensor0",
		"device/sensor1",
		"device/sensor2"
	};
	cameras.resize(devices.size());

	for (int i = 0; i < cameras.size(); i++) {
		auto& astra = cameras[i];
		astra.setup(devices[i]);
		astra.enableRegistration(bUseRegistration);
		astra.initDepthStream();
		astra.setDepthClipping(300, 5000);
	}
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));

	for (auto& astra : cameras) {
		astra.update();
	}
}

void ofApp::draw(){
	ofSetColor(ofColor::white);
	cameras[0].drawDepth(0, 0);
	cameras[1].drawDepth(640, 0);
	cameras[2].drawDepth(0, 480);

	stringstream ss;
	ss << "r: toggle registration between color & depth images (";
	ss << (bUseRegistration ? "on)" : "off)") << endl;

	ofSetColor(ofColor::red);
	ofDrawBitmapStringHighlight(ss.str(), 20, ofGetHeight() - 30);
}

void ofApp::keyPressed(int key){

	if (key == 'r') {
		bUseRegistration ^= 1;
		for (auto& astra : cameras) {
			astra.enableRegistration(bUseRegistration);
		}
	}
}
