#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(Define::WIN_W , Define::WIN_H, OF_WINDOW);			// <-------- setup the GL context

	ofSetFrameRate(60);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	ofRunApp(new ofApp());

	//Hello Hello
}
