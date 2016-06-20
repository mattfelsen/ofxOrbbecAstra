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
	ofSetWindowShape(640*2, 768);
	ofSetVerticalSync(true);

	bDrawPointCloud = false;
	bPointCloudUseColor = false;
	bUseRegistration = true;
	mesh.setMode(OF_PRIMITIVE_POINTS);

	astra.setup();
	astra.enableRegistration(bUseRegistration);

	astra.initColorStream();
	// If you are using an Astra Pro camera and only see a black screen, try
	// commenting out the above initColorStream() call and use
	// initVideoGrabber() instead
//	astra.initVideoGrabber();

	astra.initDepthStream();
	astra.initPointStream();
	astra.initHandStream();
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));

	astra.update();

	if (astra.isFrameNew() && bDrawPointCloud) {
		mesh.clear();

		int maxDepth = 1500;
		int w = astra.getDepthImage().getWidth();
		int h = astra.getDepthImage().getHeight();

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				ofVec3f p = astra.getWorldCoordinateAt(x, y);

				if (p.z == 0) continue;
				if (p.z > maxDepth) continue;

				mesh.addVertex(p);

				if (bPointCloudUseColor) {
					mesh.addColor(astra.getColorImage().getColor(x, y));
				} else {
					float hue  = ofMap(p.z, 0, maxDepth, 0, 255);
					mesh.addColor(ofColor::fromHsb(hue, 255, 255));
				}
			}
		}
	}
}

void ofApp::draw(){

	if (!bDrawPointCloud) {
		ofSetColor(ofColor::white);
		astra.drawDepth(0, 0);
		astra.draw(640, 0);

		for (auto& hand : astra.getHandsDepth()) {
			auto& pos = hand.second;
			ofSetColor(ofColor::red);
			ofDrawCircle(pos, 10);

			stringstream ss;
			ss << "id: " << hand.first << endl;
			ss << "pos: " << hand.second;
			ofDrawBitmapStringHighlight(ss.str(), pos.x, pos.y - 30);
		}
	} else {
		cam.begin();
		ofEnableDepthTest();
		ofRotateY(180);
		ofScale(1.5, 1.5);

		mesh.draw();


		for (auto& hand : astra.getHandsWorld()) {
			auto& pos = hand.second;
			ofSetColor(ofColor::white);
			ofDrawCircle(pos, 10);

			stringstream ss;
			ss << "id: " << hand.first << endl;
			ss << "pos: " << hand.second;
			ofDrawBitmapString(ss.str(), pos.x, pos.y - 30, pos.z);
		}

		ofDisableDepthTest();
		cam.end();
	}

	stringstream ss;
	ss << "r: toggle registration between color & depth images (";
	ss << (bUseRegistration ? "on)" : "off)") << endl;
	ss << "p: switch between images and point cloud" << endl;
	ss << "c: toggle point cloud using color image or gradient (";
	ss << (bPointCloudUseColor ? "color image)" : "gradient)") << endl;
	ss << "rotate the point cloud with the mouse" << endl << endl;

	ss << "tracked hands: " << astra.getHandsDepth().size() << endl;
	ss << "try moving your hands in a circle until they are recognized";

	ofSetColor(ofColor::white);
	ofDrawBitmapStringHighlight(ss.str(), 20, 500);
}

void ofApp::keyPressed(int key){
	if (key == 'p')
		bDrawPointCloud ^= 1;
	if (key == 'c')
		bPointCloudUseColor ^= 1;
	if (key == 'r') {
		bUseRegistration ^= 1;
		astra.enableRegistration(bUseRegistration);
	}
}
