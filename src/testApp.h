#pragma once

#include "ofMain.h"
#include "ofxTesseract.h"
#include "ofxAutoControlPanel.h"
#include "CvUtils.h"
#include "levenshtein.cpp"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345
using namespace cv;

class testApp : public ofBaseApp{
    
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    

    
    
    string runOcr(float scale, int medianSize);
    vector<string> recognition (vector<string> result);
    vector<string> getRef();
    
    vector<string> result;
    
    
    ofxTesseract tess;
    ofImage img, scaled;
    string ocrResult;
    ofxAutoControlPanel panel;
    
    bool start = false;
    
    ofVideoGrabber cam;
    
    ofxOscSender sender;
    
    //String Ref
    
    //        string distortion = "Distortion";
    //        string wah = "Wah";
    //        string delay = "Delay";
    //        string tremolo = "Tremolo";
    //        string reverb = "Reverb";
    
};
