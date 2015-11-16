//
//  ofxOrbbecAstra.h
//  ofxOrbbecAstra
//
//  Created by Matt Felsen on 10/24/15.
//
//

#pragma once

#include "ofMain.h"
#include <Astra/Astra.h>
#include <AstraUL/AstraUL.h>

class ofxOrbbecAstra : public astra::FrameReadyListener {

public:

    ofxOrbbecAstra();
    ~ofxOrbbecAstra();

    void setup();
    void setRegistration(bool useRegistration);

    void initColorStream();
    void initDepthStream();
    void initPointStream();

    void update();

    void draw(float x = 0, float y = 0, float w = 0, float h = 0);
    void drawDepth(float x = 0, float y = 0, float w = 0, float h = 0);

    ofVec3f getWorldCoordinateAt(int x, int y);

    ofShortPixels& getRawDepth();
    ofImage& getDepthImage();
    ofImage& getColorImage();

protected:

    virtual void on_frame_ready(astra::StreamReader& reader,
                                astra::Frame& frame) override;

    void updateDepthLookupTable();

    unique_ptr<astra::StreamSet> streamset;
    unique_ptr<astra::StreamReader> reader;

    int width;
    int height;
    bool bSetup;

    ofShortPixels depthPixels;
    ofImage depthImage;
    ofImage colorImage;

    vector<char> depthLookupTable;
    vector<ofVec3f> cachedCoords;

};