//
//  FrameListener.h
//  example
//
//  Created by Matt Felsen on 10/24/15.
//
//

#pragma once

#include "ofMain.h"
#include <Astra/Astra.h>
#include <AstraUL/AstraUL.h>

class FrameListener : public astra::FrameReadyListener {

public:

	FrameListener() :
		streamset(nullptr),
		reader(nullptr)
	{}

	~FrameListener(){
		astra::Astra::terminate();
	}

	void setup(){
		int width = 640;
		int height = 480;
		img.allocate(width, height, OF_IMAGE_COLOR);

		astra::Astra::initialize();

		streamset = make_unique<astra::StreamSet>();
		reader = make_unique<astra::StreamReader>(streamset->create_reader());

		astra::ImageStreamMode colorMode;
		auto colorStream = reader->stream<astra::ColorStream>();

		colorMode.set_width(width);
		colorMode.set_height(height);
		colorMode.set_pixelFormat(astra_pixel_formats::ASTRA_PIXEL_FORMAT_RGB888);
		colorMode.set_fps(30);

		colorStream.set_mode(colorMode);
		colorStream.start();

		reader->addListener(*this);
	}

	void update(){
		astra_temp_update();
	}

	void draw(){
		img.draw(0, 0);
	}

	virtual void on_frame_ready(astra::StreamReader& reader,
								astra::Frame& frame) override
	{
		astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();

		int width = colorFrame.resolutionX();
		int height = colorFrame.resolutionY();

		const astra::RGBPixel* colorData = colorFrame.data();

		if (colorFrame.is_valid()) {
			colorFrame.copy_to((astra::RGBPixel*) img.getPixels().getData());
			img.update();
		}
	}

protected:

	unique_ptr<astra::StreamSet> streamset;
	unique_ptr<astra::StreamReader> reader;

	ofImage img;

};