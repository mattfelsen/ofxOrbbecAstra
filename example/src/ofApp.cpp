//
//  ofApp.cpp
//  example
//
//  Created by Matt Felsen on 11/15/15.
//
//

#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(640*2, 480);
    astra.setup();
}

void ofApp::update(){
    astra.update();
}

void ofApp::draw(){
    ofSetColor(ofColor::white);
    astra.draw(0, 0);
    astra.drawDepth(640, 0);
}