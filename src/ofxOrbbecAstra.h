//
//  ofxOrbbecAstra.h
//  ofxOrbbecAstra
//
//  Created by Matt Felsen on 10/24/15.
//
//

#pragma once

#include "ofMain.h"
#include <astra/astra.hpp>

class ofxOrbbecAstra : public astra::FrameListener {

public:

	ofxOrbbecAstra();
	~ofxOrbbecAstra();

	void setup();
	void enableDepthImage(bool enable);
	void enableRegistration(bool useRegistration);
	void setDepthClipping(unsigned short near, unsigned short far);

	void initColorStream();
	void initDepthStream();
	void initPointStream();
	void initHandStream();

	void update();
	bool isFrameNew();

	void draw(float x = 0, float y = 0, float w = 0, float h = 0);
	void drawDepth(float x = 0, float y = 0, float w = 0, float h = 0);

	ofVec3f getWorldCoordinateAt(int x, int y);

	unsigned short getNearClip();
	unsigned short getFarClip();

	ofShortPixels& getRawDepth();
	ofImage& getDepthImage();
	ofImage& getColorImage();

	unordered_map<int32_t,ofVec2f>& getHandsDepth();
	unordered_map<int32_t,ofVec3f>& getHandsWorld();

protected:

	virtual void on_frame_ready(astra::StreamReader& reader,
		astra::Frame& frame) override;

	void updateDepthLookupTable();

	astra::StreamSet streamset;
	astra::StreamReader reader;

	int width;
	int height;
	bool bSetup;
	bool bIsFrameNew;
	bool bDepthImageEnabled;
	unsigned short nearClip;
	unsigned short farClip;

	ofShortPixels depthPixels;
	ofImage depthImage;
	ofImage colorImage;

	vector<char> depthLookupTable;
	vector<ofVec3f> cachedCoords;

	unordered_map<int32_t,ofVec2f> handMapDepth;
	unordered_map<int32_t,ofVec3f> handMapWorld;

};
