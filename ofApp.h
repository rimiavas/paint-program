#pragma once

#include "ofMain.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofFbo canvasFbo;
		void simpleBrush(float x, float y);
		bool paintIsOn;
		void eraserBrush(float x, float y);
		enum BrushMode { BRUSH, ERASER, DYNAMIC, RECTANGLE};
		BrushMode currentMode;

		vec2 previousMousePos;
		vec2 gestureDirection;
		float gestureMagnitude;

		void dynamicBrush(float x, float y, float speed, vec2 direction);

		float prevMouseAmt;
		float currentMouseAmount;

		void rectangleBrush(float x, float y);

		ofColor brushColor;
};
