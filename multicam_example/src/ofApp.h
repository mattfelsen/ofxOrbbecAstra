//
//  ofApp.cpp
//  example
//
//  Created by Matt Felsen on 11/15/15.
//
//  Edited by Adiel Fernandez on 10/5/16
//
//  Example opens the depth stream (only)
//  of 3 different Orbbec Astra Cameras
//
//


#pragma once

#include "ofMain.h"
#include "ofxOrbbecAstra.h"



class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	ofxOrbbecAstra astra1;
	ofxOrbbecAstra astra2;
	ofxOrbbecAstra astra3;

	bool bUseRegistration;

};
