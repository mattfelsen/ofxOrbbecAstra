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
	astra.initDepthStream();
	astra.initPointStream();
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
					mesh.addColor(ofColor::fromHsb(ofMap(p.z, 0, maxDepth, 0, 255), 255, 255));
				}
			}
		}
	}
}

void ofApp::draw(){

	if (!bDrawPointCloud) {
		ofSetColor(ofColor::white);
		astra.draw(0, 0);
		astra.drawDepth(640, 0);
	} else {
		cam.begin();
		ofEnableDepthTest();
		ofRotateY(180);
		ofScale(1.5, 1.5);

		mesh.draw();

		ofDisableDepthTest();
		cam.end();
	}

	stringstream ss;
	ss << "r: toggle registration between color & depth images (";
	ss << (bUseRegistration ? "on)" : "off)") << endl;
	ss << "p: switch between images and point cloud" << endl;
	ss << "c: toggle point cloud using color image or gradient (";
	ss << (bPointCloudUseColor ? "color image)" : "gradient)") << endl;
	ss << "rotate the point cloud with the mouse";

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
