//
//  EaseRectBox.h
//  messageboxExample
//
//  Created by 洋紀 加治 on 12/08/16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ofMain.h"

#define EASERECT_ALIGN_LEFT 0x0
#define EASERECT_ALIGN_RIGHT 0x1
#define EASERECT_ALIGN_CENTER 0x2

#define EASERECT_VLIGN_TOP 0x0
#define EASERECT_VLIGN_CENTER 0x1
#define EASERECT_VLIGN_BOTTOM 0x2

class EaseRectBox{
public:

	EaseRectBox();
	~EaseRectBox();
	
	void setArea(ofRectangle rect);
	void setMessage(string mes,bool autoWidth = true);
	void setAlign(int align_type);
	void setYPos(float y_,int option = -1);
	
	void appear(bool animated);
	void draw();
	void disappear(bool animated);
	void SetColor(ofColor color);
	void SetColor(int r,int g,int b);
	
	virtual void mouseMoved(ofMouseEventArgs & args);
	virtual void mousePressed(ofMouseEventArgs & args);
	virtual void mouseDragged(ofMouseEventArgs & args);
	virtual void mouseReleased(ofMouseEventArgs & args);
	
	ofColor			main_color;
	ofColor			hilight_color;
	bool			appearing;
	bool			disappearing;
	bool			animating;
	bool			Box_double;
	bool			bInteractive;
	bool			bSelected;
	int 			onMouse;
	int				frame;
	int				alignment_type;
	float			ypos;
	string			message;
	ofRectangle		temp_area;
	ofRectangle		area;
};