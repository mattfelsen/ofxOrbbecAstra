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

	FrameListener() : streamset(nullptr), reader(nullptr) {
	}

	~FrameListener(){
		astra::Astra::terminate();
	}

	void setup(){
		astra::Astra::initialize();

		streamset = make_unique<astra::StreamSet>();
		reader = make_unique<astra::StreamReader>(streamset->create_reader());
		reader->stream<astra::ColorStream>().start();
		reader->addListener(*this);
	}

	void update(){
		astra_temp_update();
	}

	void draw(){
		img.draw(0, 0);
	}


	void print_color(astra::ColorFrame& colorFrame){
		if (colorFrame.is_valid())
		{
			int width = colorFrame.resolutionX();
			int height = colorFrame.resolutionY();
			int frameIndex = colorFrame.frameIndex();

			astra::RGBPixel* buffer = new astra::RGBPixel[colorFrame.numberOfPixels()];
			colorFrame.copy_to(buffer);

			size_t index = ((width * (height / 2.0f)) + (width / 2.0f));
			astra::RGBPixel middle = buffer[index];

			std::cout << "color frameIndex: " << frameIndex
			<< " r: " << static_cast<int>(middle.r)
			<< " g: " << static_cast<int>(middle.g)
			<< " b: " << static_cast<int>(middle.b)
			<< std::endl;

			delete[] buffer;
		}
	}

	virtual void on_frame_ready(astra::StreamReader& reader,
								astra::Frame& frame) override
	{
		astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();

		int width = colorFrame.resolutionX();
		int height = colorFrame.resolutionY();

		img.allocate(width, height, OF_IMAGE_GRAYSCALE);
        const astra_rgb_pixel_t* colorData = colorFrame.data();

		if (colorFrame.is_valid())
		{
//			print_color(colorFrame);

			for (int i = 0; i < width * height; i++)
			{
				ofColor c;
				c.r = static_cast<int>(colorData[i].r);
				c.g = static_cast<int>(colorData[i].g);
				c.b = static_cast<int>(colorData[i].b);
				img.setColor(i, c);
			}
			img.update();
		}
	}

protected:

	unique_ptr<astra::StreamSet> streamset;
	unique_ptr<astra::StreamReader> reader;

	ofImage img;

};