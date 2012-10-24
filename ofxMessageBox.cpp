//
//  ofxMessageBox.cpp
//  messageboxExample
//
//  Created by 洋紀 加治 on 12/08/16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ofxMessageBox.h"

ofxMessageBox::ofxMessageBox(){
	box_appearing = -1;
	frame = 0;
	Selected = -1;
	Response = -1;
	ofAddListener(ofEvents().draw, this, &ofxMessageBox::draw);
    ofAddListener(ofEvents().mouseMoved, this, &ofxMessageBox::mouseMoved);
    ofAddListener(ofEvents().mousePressed, this, &ofxMessageBox::mousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &ofxMessageBox::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &ofxMessageBox::mouseReleased);
    ofAddListener(ofEvents().keyPressed, this, &ofxMessageBox::keyPressed);
}

ofxMessageBox::~ofxMessageBox(){
	ofRemoveListener(ofEvents().draw, this, &ofxMessageBox::draw);
    ofRemoveListener(ofEvents().mouseMoved, this, &ofxMessageBox::mouseMoved);
    ofRemoveListener(ofEvents().mousePressed, this, &ofxMessageBox::mousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxMessageBox::mouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxMessageBox::mouseReleased);
    ofRemoveListener(ofEvents().keyPressed, this, &ofxMessageBox::keyPressed);
}

void ofxMessageBox::addNewMessage(string title, string mes, int type,ofPoint position){
	messageBox bx;
	msgBoxes.push_back(bx);
	ofPoint win_size = ofPoint(320,130);
	ofRectangle mr = ofRectangle(ofGetWidth()/2-win_size.x/2,
								 ofGetHeight()/2-win_size.y/2,
								 win_size.x,win_size.y);
	if (position != ofPoint(0,0)){
        mr = ofRectangle(position.x-win_size.x/2,
                         position.y-win_size.y/2,
                         win_size.x,win_size.y);
    }
    
	msgBoxes[msgBoxes.size()-1].mainBox.setArea(mr);
	setTitle		(msgBoxes.size()-1, title);
	setType			(msgBoxes.size()-1, type);
	setDescription	(msgBoxes.size()-1, mes);
}

void ofxMessageBox::draw(ofEventArgs& args){
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	if (box_appearing > -1){
		frame++;
		ofSetColor(0,MIN(120,msgBoxes[box_appearing].mainBox.temp_area.width / msgBoxes[box_appearing].mainBox.area.width * 120.0));
		ofRect(0, 0, ofGetWidth(), ofGetHeight());		
	}
	
	ofSetHexColor(0xFFFFFF);
	bool startDissapear = false;
	for (int i = 0;i < msgBoxes.size();i++){
		msgBoxes[i].mainBox.draw();
		msgBoxes[i].titleBox.draw();
		
		for (int j = 0;j < msgBoxes[i].buttonBox.size();j++){
			msgBoxes[i].buttonBox[j].draw();
			if (msgBoxes[i].buttonBox[j].bSelected){
				startDissapear = true;
			}
		}
		if (startDissapear){
			for (int j = 0;j < msgBoxes[i].buttonBox.size();j++){
				if ((msgBoxes[i].buttonBox[j].bSelected)&&
                    (msgBoxes[i].buttonBox.size() != 1)){
					Selected = j;
					Response = j;
				}else{
					if (!msgBoxes[i].buttonBox[j].disappearing){
						msgBoxes[i].buttonBox[j].disappear(true);
					}
					if (msgBoxes[i].buttonBox[j].temp_area.width < 1){
						disableMessage();
					}
				}
			}
		}
	}
}

void ofxMessageBox::setTitle(int num, string title){
	msgBoxes[num].title = title;
	ofRectangle mr = msgBoxes[num].mainBox.area;
	msgBoxes[num].titleBox.setArea(ofRectangle(mr.x,mr.y,mr.width,20));
	msgBoxes[num].titleBox.setMessage(title,false);
	msgBoxes[num].titleBox.setAlign(EASERECT_ALIGN_CENTER);
	msgBoxes[num].titleBox.setYPos (0,EASERECT_VLIGN_CENTER);
}

void ofxMessageBox::setDescription(int num, string mes){
	msgBoxes[num].message = mes;
	msgBoxes[num].mainBox.setMessage(mes,false);
	msgBoxes[num].mainBox.setAlign(EASERECT_ALIGN_CENTER);
	msgBoxes[num].mainBox.setYPos (60);
	msgBoxes[num].mainBox.Box_double = true;
}

void ofxMessageBox::viewMessage(int num){
	disableMessage();
	if (num >= msgBoxes.size()) return;
	msgBoxes[num].titleBox.appear(true);
	msgBoxes[num].mainBox.appear(true);
	for (int i = 0;i < msgBoxes[num].buttonBox.size();i++){
		msgBoxes[num].buttonBox[i].appear(true);
	}
	box_appearing = num;
	frame = 0;
	Selected = -1;
	Response = -1;
}

int ofxMessageBox::getResponse(){
	int res = Response;
	Response = -1;
	return res;
}

void ofxMessageBox::disableMessage(){
	for (int i = 0;i < msgBoxes.size();i++){
		msgBoxes[i].titleBox.disappear(false);
		msgBoxes[i].mainBox.disappear(true);
		for (int j = 0;j < msgBoxes[i].buttonBox.size();j++){
			msgBoxes[i].buttonBox[j].disappear(true);
			msgBoxes[i].buttonBox[j].bSelected = false;
		}
	}
	box_appearing = -1;
	frame = 0;
}

void ofxMessageBox::setType(int num, int type){
	ofRectangle mr = msgBoxes[num].mainBox.area;
	EaseRectBox okBox;
	EaseRectBox cancelBox;
	EaseRectBox yesBox;
	EaseRectBox noBox;
	
	okBox		.setMessage("OK",false);
	cancelBox	.setMessage("Cancel",false);
	yesBox		.setMessage("Yes",false);
	noBox		.setMessage("No",false);
	
	okBox		.setAlign(EASERECT_ALIGN_CENTER);
	cancelBox	.setAlign(EASERECT_ALIGN_CENTER);
	yesBox		.setAlign(EASERECT_ALIGN_CENTER);
	noBox		.setAlign(EASERECT_ALIGN_CENTER);
	int bw = 80;
	switch (type) {
		case OFX_MESSAGEBOX_OK:
			okBox.setArea(ofRectangle(mr.x+mr.width/2-bw/2,
									  mr.y+mr.height-35,bw,18));
			okBox.setYPos(0,EASERECT_VLIGN_CENTER);
			
			msgBoxes[num].buttonBox.push_back(okBox);
			break;
		case OFX_MESSAGEBOX_OKCANCEL:
			okBox.setArea		(ofRectangle(mr.x+mr.width/2 - mr.width/6 -bw/2,
											 mr.y+mr.height-35,bw,18));
			cancelBox.setArea	(ofRectangle(mr.x+mr.width/2 + mr.width/6 -bw/2,
											 mr.y+mr.height-35,bw,18));

			okBox		.setYPos(0,EASERECT_VLIGN_CENTER);
			cancelBox	.setYPos(0,EASERECT_VLIGN_CENTER);
			msgBoxes[num].buttonBox.push_back(okBox);
			msgBoxes[num].buttonBox.push_back(cancelBox);
			break;
		case OFX_MESSAGEBOX_YESNO:
			yesBox.setArea		(ofRectangle(mr.x+mr.width/2 - mr.width/6 -bw/2,
											 mr.y+mr.height-35,bw,18));
			noBox.setArea		(ofRectangle(mr.x+mr.width/2 + mr.width/6 -bw/2,
											 mr.y+mr.height-35,bw,18));
			yesBox		.setYPos(0,EASERECT_VLIGN_CENTER);
			noBox		.setYPos(0,EASERECT_VLIGN_CENTER);
			msgBoxes[num].buttonBox.push_back(yesBox);
			msgBoxes[num].buttonBox.push_back(noBox);			
			break;
		case OFX_MESSAGEBOX_YESNOCANCEL:
			yesBox.setArea		(ofRectangle(mr.x+mr.width/2 - mr.width/3 -bw/2,
											 mr.y+mr.height-35,bw,18));
			noBox.setArea		(ofRectangle(mr.x+mr.width/2 - bw/2,
											 mr.y+mr.height-35,bw,18));
			cancelBox.setArea	(ofRectangle(mr.x+mr.width/2 + mr.width/3 -bw/2,
											 mr.y+mr.height-35,bw,18));
			
			yesBox		.setYPos(0,EASERECT_VLIGN_CENTER);
			noBox		.setYPos(0,EASERECT_VLIGN_CENTER);
			cancelBox	.setYPos(0,EASERECT_VLIGN_CENTER);
			msgBoxes[num].buttonBox.push_back(yesBox);
			msgBoxes[num].buttonBox.push_back(noBox);			
			msgBoxes[num].buttonBox.push_back(cancelBox);
			break;
			
		default:
			break;
	}
	for (int i = 0;i < msgBoxes[num].buttonBox.size();i++){
		msgBoxes[num].buttonBox[i].bInteractive = true;
	}
}

void ofxMessageBox::mouseMoved(ofMouseEventArgs &args){
	for (int i = 0;i < msgBoxes.size();i++){
		for (int j = 0;j < msgBoxes[i].buttonBox.size();j++){
			msgBoxes[i].buttonBox[j].mouseMoved(args);
		}
	}
}

void ofxMessageBox::mousePressed(ofMouseEventArgs &args){
	for (int i = 0;i < msgBoxes.size();i++){
		for (int j = 0;j < msgBoxes[i].buttonBox.size();j++){
			msgBoxes[i].buttonBox[j].mousePressed(args);
		}
	}	
}

void ofxMessageBox::mouseDragged(ofMouseEventArgs &args){
	for (int i = 0;i < msgBoxes.size();i++){
		for (int j = 0;j < msgBoxes[i].buttonBox.size();j++){
			msgBoxes[i].buttonBox[j].mouseDragged(args);
		}
	}
}

void ofxMessageBox::mouseReleased(ofMouseEventArgs &args){
	for (int i = 0;i < msgBoxes.size();i++){
		for (int j = 0;j < msgBoxes[i].buttonBox.size();j++){
			msgBoxes[i].buttonBox[j].mouseReleased(args);
		}
	}
}

void ofxMessageBox::keyPressed(ofKeyEventArgs &key){
    if (key.key == OF_KEY_RETURN){
        for (int i = 0;i < msgBoxes.size();i++){
            if (box_appearing == i){
                ofMouseEventArgs g;
                g.x = msgBoxes[i].buttonBox[0].area.x + 3;
                g.y = msgBoxes[i].buttonBox[0].area.y + 3;
                g.button = 1;

                msgBoxes[i].buttonBox[0].onMouse = true;
                msgBoxes[i].buttonBox[0].mouseReleased(g);
            }
        }
    }
}