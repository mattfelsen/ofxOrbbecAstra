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
    void update();
    void draw();

    virtual void on_frame_ready(astra::StreamReader& reader,
                                astra::Frame& frame) override;

protected:

	unique_ptr<astra::StreamSet> streamset;
	unique_ptr<astra::StreamReader> reader;

	ofImage colorImg;
	ofShortImage depthImg;

};