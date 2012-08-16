//
//  EaseRectBox.cpp
//  messageboxExample
//
//  Created by 洋紀 加治 on 12/08/16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "EaseRectBox.h"

EaseRectBox::EaseRectBox(){
	animating = false;
	appearing = false;
	disappearing = false;
	Box_double = false;
	frame = 0;
	alignment_type = EASERECT_ALIGN_CENTER;
	main_color.set(255, 255, 255);
	hilight_color.setHsb(235, 255, 255,180);
	
	bInteractive = false;
	bSelected = false;

}

EaseRectBox::~EaseRectBox(){
}

void EaseRectBox::setArea(ofRectangle rect){
	area = rect;
}

void EaseRectBox::setMessage(string mes,bool autoWidth){
	message = mes;
	if (autoWidth){
		area.width = message.length()*8 + 10;
	}
}

void EaseRectBox::setAlign(int align_type){
	alignment_type = align_type;
}

void EaseRectBox::setYPos(float y_,int option){
	ypos = y_;
	if (option == EASERECT_VLIGN_TOP) ypos = 17;
	if (option == EASERECT_VLIGN_CENTER) ypos = area.height/2+4;
	if (option == EASERECT_VLIGN_BOTTOM) ypos = area.height-4;
}

void EaseRectBox::appear(bool animated){
	appearing = true;
	disappearing = false;
	frame = 0;
	animating = animated;
	temp_area = ofRectangle(area.x,area.y,0,0);
	if (!animated){
		temp_area = area;
	}
}

void EaseRectBox::draw(){
	string mes = "";
	
	mes += message.substr(0,MIN(message.length(),(frame)/2));
	
	for (int j = 0;j < MAX(0,(float)message.length()-MAX(0,(frame)/2));j++){
		mes += ofToString((char)ofRandom(33,120));
	}
	
	float eas_k = 4.0*ofGetFrameRate()/60.0f;
	if (appearing) frame += 1;
	if ((appearing)&&(animating)){
		temp_area.width += (area.width - temp_area.width)/eas_k;
		temp_area.height+= (area.height - temp_area.height)/eas_k;
	}
	if ((disappearing)&&(animating)){
		frame++;
		temp_area.x += (area.x+area.width/2  - temp_area.x)/eas_k;
		temp_area.y += (area.y+area.height/2 - temp_area.y)/eas_k;
		temp_area.width +=  (0.0  - temp_area.width)/eas_k;
		temp_area.height += (0.0 - temp_area.height)/eas_k;
	}

	ofPoint mes_pos;
	switch (alignment_type) {
		case EASERECT_ALIGN_LEFT:
			mes_pos.x = 2;
			break;
		case EASERECT_ALIGN_RIGHT:
			mes_pos.x = area.width - mes.length()*8-4;
			break;
		case EASERECT_ALIGN_CENTER:
			mes_pos.x = area.width/2 - mes.length()*4+1;
			break;
		default:
			break;
	}
	mes_pos.y = ypos;
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(0, 50);
	ofRect(temp_area);
	main_color.a = MIN(255,temp_area.width / area.width * 512.0);
	ofSetColor(main_color);
	ofNoFill();
	if (temp_area.width > 1){
		ofRect(temp_area);
		if (Box_double) ofRect(temp_area.x-2, temp_area.y-2,
							   temp_area.width+4, temp_area.height+4);		
	}
	main_color.a = 255;
	ofSetColor(main_color);
	if (appearing) ofDrawBitmapString(mes, 
									  area.x+mes_pos.x,
									  area.y + mes_pos.y);
	
	if ((temp_area.x < ofGetMouseX())&&(ofGetMouseX() < (temp_area.x+temp_area.width))&&
		(temp_area.y < ofGetMouseY())&&(ofGetMouseY() < (temp_area.y+temp_area.height))){
		onMouse = 1;
	}else {
		onMouse = 0;
	}
	
	ofFill();
	if ((onMouse)&&(bInteractive)){
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofSetColor(hilight_color);
		ofRect(temp_area);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	}
	
}

void EaseRectBox::disappear(bool animated){
	appearing = false;
	disappearing = true;
	frame = 0;
	animating = animated;
	if (!animated){
		temp_area = ofRectangle(area.x,area.y,0,0);
	}
}

void EaseRectBox::SetColor(ofColor color){
	main_color = color;
}

void EaseRectBox::SetColor(int r, int g, int b){
	SetColor(ofColor(r,g,b));
}

void EaseRectBox::mouseMoved(ofMouseEventArgs & args){

}
void EaseRectBox::mousePressed(ofMouseEventArgs & args){
	if (onMouse){
		hilight_color.setHsb(145, 255, 255,255);
	}else{
	}
}
void EaseRectBox::mouseDragged(ofMouseEventArgs & args){
	
}
void EaseRectBox::mouseReleased(ofMouseEventArgs & args){
	if (onMouse){
		bSelected = true;
		hilight_color.setHsb(235, 255, 255,180);
	}else{
		hilight_color.setHsb(235, 255, 255,180);
	}
}
