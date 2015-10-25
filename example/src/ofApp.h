#pragma once

#include "ofMain.h"
#include "FrameListener.h"

class ofApp : public ofBaseApp{

public:
	
	void setup(){
		listener.setup();
	}

	void update(){
		listener.update();
	}
	
	void draw(){
		ofSetColor(ofColor::white);
		listener.draw();
	}

	FrameListener listener;

};
