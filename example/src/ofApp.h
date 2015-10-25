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

	}

	FrameListener listener;

};
