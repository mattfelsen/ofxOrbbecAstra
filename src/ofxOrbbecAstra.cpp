//
//  ofxOrbbecAstra.h
//  ofxOrbbecAstra
//
//  Created by Matt Felsen on 10/24/15.
//
//

#include "ofxOrbbecAstra.h"

ofxOrbbecAstra::ofxOrbbecAstra() {
    streamset = nullptr;
    reader = nullptr;

    width = 640;
    height = 480;
    nearClip = 300;
    farClip = 1800;

    bSetup = false;
    bIsFrameNew = false;
    bDepthImageEnabled = true;
}

ofxOrbbecAstra::~ofxOrbbecAstra(){
    astra::Astra::terminate();
}

void ofxOrbbecAstra::setup(){
    colorImage.allocate(width, height, OF_IMAGE_COLOR);
    depthImage.allocate(width, height, OF_IMAGE_GRAYSCALE);
    depthPixels.allocate(width, height, OF_IMAGE_GRAYSCALE);
    cachedCoords.resize(width * height);
    updateDepthLookupTable();

    astra::Astra::initialize();

    streamset = make_unique<astra::StreamSet>();
    reader = make_unique<astra::StreamReader>(streamset->create_reader());

    if (streamset != nullptr && reader != nullptr) {
        bSetup = true;
        reader->addListener(*this);
    }
}

void ofxOrbbecAstra::enableDepthImage(bool enable) {
    bDepthImageEnabled = enable;
}

void ofxOrbbecAstra::enableRegistration(bool useRegistration) {
    if (!bSetup) {
        ofLogWarning("ofxOrbbecAstra") << "Must call setup() before setRegistration()";
        return;
    }

    reader->stream<astra::DepthStream>().enable_registration(useRegistration);
}

void ofxOrbbecAstra::setDepthClipping(unsigned short near, unsigned short far) {
    nearClip = near;
    farClip = far;
    updateDepthLookupTable();
}

void ofxOrbbecAstra::initColorStream() {
    if (!bSetup) {
        ofLogWarning("ofxOrbbecAstra") << "Must call setup() before initColorStream()";
        return;
    }

    astra::ImageStreamMode colorMode;
    auto colorStream = reader->stream<astra::ColorStream>();

    colorMode.set_width(width);
    colorMode.set_height(height);
    colorMode.set_pixelFormat(astra_pixel_formats::ASTRA_PIXEL_FORMAT_RGB888);
    colorMode.set_fps(30);

    colorStream.set_mode(colorMode);
    colorStream.start();
}

void ofxOrbbecAstra::initDepthStream() {
    if (!bSetup) {
        ofLogWarning("ofxOrbbecAstra") << "Must call setup() before initDepthStream()";
        return;
    }

    astra::ImageStreamMode depthMode;
    auto depthStream = reader->stream<astra::DepthStream>();

    depthMode.set_width(width);
    depthMode.set_height(height);
    depthMode.set_pixelFormat(astra_pixel_formats::ASTRA_PIXEL_FORMAT_DEPTH_MM);
    depthMode.set_fps(30);

    depthStream.set_mode(depthMode);
    depthStream.start();
}

void ofxOrbbecAstra::initPointStream() {
    if (!bSetup) {
        ofLogWarning("ofxOrbbecAstra") << "Must call setup() before initPointStream()";
        return;
    }

    reader->stream<astra::PointStream>().start();
}

void ofxOrbbecAstra::update(){
    // See on_frame_ready() for more processing
    bIsFrameNew = false;
    astra_temp_update();
}

void ofxOrbbecAstra::draw(float x, float y, float w, float h){
    if (!w) w = width;
    if (!h) h = height;
    colorImage.draw(x, y, w, h);
}

void ofxOrbbecAstra::drawDepth(float x, float y, float w, float h){
    if (!w) w = width;
    if (!h) h = height;
    depthImage.draw(x, y, w, h);
}

bool ofxOrbbecAstra::isFrameNew() {
    return bIsFrameNew;
}

void ofxOrbbecAstra::on_frame_ready(astra::StreamReader& reader,
                                    astra::Frame& frame)
{
    bIsFrameNew = true;
    
    auto colorFrame = frame.get<astra::ColorFrame>();
    auto depthFrame = frame.get<astra::DepthFrame>();
    auto pointFrame = frame.get<astra::PointFrame>();

    if (colorFrame.is_valid()) {
        colorFrame.copy_to((astra::RGBPixel*) colorImage.getPixels().getData());
        colorImage.update();
    }

    if (depthFrame.is_valid()) {
        depthFrame.copy_to((short*) depthPixels.getData());

        if (bDepthImageEnabled) {
            // TODO do this with a shader so it's fast?
            for (int i = 0; i < depthPixels.size(); i++) {
                short depth = depthPixels.getColor(i).r;
                float val = depthLookupTable[depth];
                depthImage.setColor(i, ofColor(val));
            }
            depthImage.update();
        }
    }

    if (pointFrame.is_valid()) {
        // TODO: Figure out why pointFrame.copy_to() isn't working
        // Update: This is a known bug in the 0.4.0 SDK, use memcpy() for now
        // https://3dclub.orbbec3d.com/t/copy-to-not-working-properly-for-pointframe/127
        // pointFrame.copy_to((astra::Vector3f*) cachedCoords.data());
        memcpy(cachedCoords.data(), pointFrame.data(), cachedCoords.size() * sizeof(ofVec3f));
    }
}

void ofxOrbbecAstra::updateDepthLookupTable() {
    // From product specs, range is 8m
    int maxDepth = 8000;
    depthLookupTable.resize(maxDepth);

    // Depth values of 0 should be discarded, so set the LUT value to 0 as well
    depthLookupTable[0] = 0;

    // Set the rest
    for (int i = 1; i < maxDepth; i++) {
        depthLookupTable[i] = ofMap(i, nearClip, farClip, 255, 0, true);
    }

}

ofVec3f ofxOrbbecAstra::getWorldCoordinateAt(int x, int y) {
    return cachedCoords[int(y) * width + int(x)];
}

unsigned short ofxOrbbecAstra::getNearClip() {
    return nearClip;
}

unsigned short ofxOrbbecAstra::getFarClip() {
    return farClip;
}

ofShortPixels& ofxOrbbecAstra::getRawDepth() {
    return depthPixels;
}

ofImage& ofxOrbbecAstra::getDepthImage() {
    return depthImage;
}

ofImage& ofxOrbbecAstra::getColorImage() {
    return colorImage;
}