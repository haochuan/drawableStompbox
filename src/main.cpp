#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 480, 600, OF_WINDOW);
	ofRunApp(new testApp());
}
