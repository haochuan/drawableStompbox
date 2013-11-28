#include "testApp.h"


void testApp::setup(){
    cam.initGrabber(480, 360);
    sender.setup(HOST, PORT);
    //	panel.setup();
    //	panel.addPanel("Preprocessing");
    //	panel.addSlider("scale", "scale", 2.5, 1, 4);
    //	panel.addSlider("medianSize", "medianSize", 2, 0, 12, true);
    
	tess.setup();
	tess.setWhitelist("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,");
	tess.setAccuracy(ofxTesseract::ACCURATE);
	tess.setMode(ofxTesseract::AUTO);
    
	
    //	img.loadImage("article.png");
    //	img.setImageType(OF_IMAGE_GRAYSCALE);
    //	img.update();
}

void testApp::update(){
    
    cam.update();
    if(cam.isFrameNew()) {
        if(ofGetFrameNum()%30==0) {
            ocrResult= tess.findText( cam.getPixelsRef());
            
            //        	cout << ocrResult;
        }
    }
    //	if(panel.hasValueChanged("scale") || panel.hasValueChanged("medianSize")) {
    //		ocrResult = runOcr(panel.getValueF("scale"), panel.getValueI("medianSize"));
    //		scaled.update();
    //		panel.clearAllChanged();
    //	}
}

void testApp::draw(){
    cam.draw(0, 0);
    ofDrawBitmapString("Hold 'r' to recognize, release 'r' to send message", 0, 400);
    ofDrawBitmapString("Press 's' to clear all message", 0, 420);
    ofDrawBitmapString("Result: ", 0, 440);
   
	
    //	ofTranslate(0, 361);
    //
    //	ofSetColor(0);
    if(start) {
        vector<string> lines = ofSplitString(ocrResult, "\n");
        result = recognition(lines);
        ofTranslate(0, 460);
        for(int i = 0; i < result.size(); i++) {
        
            ofDrawBitmapString(result[i], 10, 20 + i * 12);
            
      
        
        }
    }
    
    
    
    
    
    
	
    //	ofSetColor(255);
    //	img.draw(0, 200);
    //	scaled.draw(0, 400);
	
}

// depending on the source of the text you want to OCR,
// you might need to preprocess it. here i'm doing a
// simple resize followed by a median blur.
string testApp::runOcr(float scale, int medianSize) {
	scaled = img;
	
	// resize and median blur the image
	scaled.resize(img.getWidth() * scale, img.getHeight() * scale);
	medianBlur(scaled, medianSize);
	
	return tess.findText(scaled);
}

void testApp::keyPressed(int key) {
    vector<string> ref = getRef();
    if(key == 'r') {
//        message.setAddress("/test");
//        for(int i = 0; i < ref.size(); i++) {
//            message.addStringArg("null");
//            
//        }
        start = true;
            
        

    }
    
    if(key == 's') {
        vector<string> ref = getRef();
        ofxOscMessage message;
        message.setAddress("/test");
        for(int i = 0; i < ref.size(); i++) {
            message.addIntArg(0);
        }
        sender.sendMessage(message);

    }
}

void testApp::keyReleased(int key) {
    if(key == 'r') {
        vector<string> final = result;
        vector<string> ref = getRef();
        ofxOscMessage message;
        message.setAddress("/test");
        for(int i = 0; i < ref.size(); i++) {
            bool temp = false;
            for(int j = 0; j < final.size(); j++) {
                if(ref[i] == final[j]) {
                    message.addIntArg(1);
                    temp = true;
                }
            }
            if(temp == false) {
                message.addIntArg(0);
            }

            
        }
        
        for(int i = 0; i < final.size(); i++) {
            
            cout << final[i] << endl;;
            
            
            
        }
        
        sender.sendMessage(message);
        start = false;
    }
}

vector<string> testApp::recognition (vector<string> result) {
    vector<string> ref = getRef();
    
    for(int i = 0; i < result.size(); i++) {
        for(int j = 0; j < ref.size(); j++) {
            if(levenshtein_distance(result[i], ref[j]) <= ref[j].length() / 2) {
                result[i] = ref[j];
            }
            if(result[i].length() > 9) {
                result[i] = "Distortion";
            }
            
        }
    }
    
    return result;
}

vector<string> testApp::getRef() {
    vector<string> ref;
    ref.push_back("Distortion");
    ref.push_back("Magic");
    ref.push_back("Vocoder");
    ref.push_back("Reverb");
    ref.push_back("Phasor");
    ref.push_back("Wah");
    ref.push_back("Ring");
    ref.push_back("Bass");
    ref.push_back("Vibrato");
    ref.push_back("Falling");
    ref.push_back("Violin");
    return ref;
}






