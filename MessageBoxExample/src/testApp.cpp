#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	msgBox.addNewMessage("Title", "Yes:Red No:Blue", OFX_MESSAGEBOX_YESNOCANCEL);
	
	col.set(255, 0, 0);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0, 0, 0);
	
	ofSetHexColor(0xFFFFFF);
	ofDrawBitmapString("Click mouse", 50,50);
	
	ofSetColor(col);
	ofCircle(ofGetWidth()/2, ofGetHeight()/2, 300);
	
	
	if (msgBox.Selected != -1){
		switch (msgBox.Selected) {
			case 0:
				col.set(255, 0, 0);
				break;
			case 1:
				col.set(0, 0, 255);
				break;
			default:
				
				break;
		}
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if (msgBox.box_appearing == -1) msgBox.viewMessage(0);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}