//
//  ofApp.cpp
//  example
//
//  Created by Matt Felsen on 11/15/15.
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

	ofxOrbbecAstra astra;

	ofVboMesh mesh;
	ofEasyCam cam;

	bool bDrawPointCloud;
	bool bPointCloudUseColor;
	bool bUseRegistration;

};
