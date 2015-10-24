//
//  FrameListener.h
//  example
//
//  Created by Matt Felsen on 10/24/15.
//
//

#pragma once

#include <Astra/Astra.h>
#include <AstraUL/AstraUL.h>

class FrameListener : public astra::FrameReadyListener {

public:

	astra::StreamSet streamset;
	astra::StreamReader reader;

	// Looks like the StreamReader needs to get intialized to NULL since it
	// keeps a ReaderRefPtr?
	FrameListener() : reader(NULL) {
	}

	~FrameListener(){
		astra::Astra::terminate();
	}

	void setup(){
		astra::Astra::initialize();

		reader = streamset.create_reader();
		reader.stream<astra::ColorStream>().start();
		reader.addListener(*this);
	}

	void update(){
		astra_temp_update();
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

		if (colorFrame.is_valid())
		{
			print_color(colorFrame);
		}
	}

};