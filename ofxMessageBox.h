//
//  ofxMessageBox.h
//  messageboxExample
//
//  Created by 洋紀 加治 on 12/08/16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "ofMain.h"
#include "EaseRectBox.h"
#define OFX_MESSAGEBOX_OK 0x0
#define OFX_MESSAGEBOX_OKCANCEL 0x1
#define OFX_MESSAGEBOX_YESNO 0x2
#define OFX_MESSAGEBOX_YESNOCANCEL 0x3

struct messageBox{
public:
	string title;
	string message;
	int type;
	
	EaseRectBox titleBox;
	EaseRectBox mainBox;
	vector<EaseRectBox> buttonBox;
};

class ofxMessageBox{
public:
	ofxMessageBox();
	~ofxMessageBox();
	
	void draw(ofEventArgs& args);
	void addNewMessage	(string title,string mes,int type);
	void setTitle		(int num,string title);
	void setDescription	(int num,string mes);
	void setType		(int num,int type);
	void viewMessage(int num);
	void disableMessage();
	
	virtual void mouseMoved(ofMouseEventArgs & args);
	virtual void mousePressed(ofMouseEventArgs & args);
	virtual void mouseDragged(ofMouseEventArgs & args);
	virtual void mouseReleased(ofMouseEventArgs & args);

	vector<messageBox>msgBoxes;
	
	int frame;
	int box_appearing;
	int Selected;
};