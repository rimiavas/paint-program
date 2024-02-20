#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // Allocate an FBO with the same size as the window
    canvasFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 5);

    // Clear the FBO at the start
    canvasFbo.begin();
    ofClear(ofColor(255, 255, 255, 255));
    canvasFbo.end();

    // Initialise variables
    paintIsOn = false;
    currentMode = BRUSH;
    previousMousePos = vec2(0, 0);
    gestureDirection = vec2(0, 0);
    gestureMagnitude = 0;
    prevMouseAmt = 0.9;
    currentMouseAmount = 1 - prevMouseAmt;

    brushColor = ofColor::black;

}

//--------------------------------------------------------------
void ofApp::update() {

    // Draw to the FBO
    canvasFbo.begin();
    if (paintIsOn) {
        if (currentMode == BRUSH) {
            simpleBrush(mouseX, mouseY);
        }
        else if (currentMode == ERASER) {
            eraserBrush(mouseX, mouseY);
        }
        else if (currentMode == DYNAMIC) {
            dynamicBrush(previousMousePos.x, previousMousePos.y, gestureMagnitude, gestureDirection);
        }
        else if (currentMode == RECTANGLE) {
            rectangleBrush(mouseX, mouseY);
        }
    }
    canvasFbo.end();

    // Calculate mouse gesture
    vec2 mousePos = vec2(mouseX, mouseY);
    vec2 gesture = mousePos - previousMousePos;
    gestureMagnitude = length(gesture);
    gestureDirection = normalize(gesture);

    // Store previous mouse position
    previousMousePos.x = prevMouseAmt * previousMousePos.x + mouseX * currentMouseAmount;
    previousMousePos.y = prevMouseAmt * previousMousePos.y + mouseY * currentMouseAmount;
}

//--------------------------------------------------------------
void ofApp::draw() {
    // Draw the FBO to the window
    ofSetColor(255);
    canvasFbo.draw(0, 0);
    ofSetColor(0);
    ofDrawBitmapString("Press 'e' for eraser, 'd' for dynamic brush, 'r' for rectangle brush, 'b' for simple brush", 10, ofGetHeight() - 20);
}

/// Draws an ellipse at x & y coordinates
/// parameter x - the x coordinate of the mouse position
/// parameter y - the y coordinate of the mouse position
void ofApp::simpleBrush(float x, float y) {
 
    // Set color to black
    ofSetColor(brushColor);
    // Draw an ellipse at the mouse position
    ofDrawEllipse(x, y, 50, 50);
    ofSetColor(0);;

    ofDrawBitmapString("Press 1 for black, 2 for red, 3 for green, 4 for blue", 10, ofGetHeight() - 50);

}

void ofApp::eraserBrush(float x, float y) {
    // Set color to white
    ofSetColor(255);
    // Draw an ellipse at the mouse position
    ofDrawEllipse(x, y, 50, 50);
}

/// Draws at x & y coordinates with scale and rotation affected by speed and direction
/// parameter x - the x coordinate of the mouse position
/// parameter y - the y coordinate of the mouse position
/// parameter speed - the distance between the mouse position and previous position
/// parameter direction - direction of mouse movement
void ofApp::dynamicBrush(float x, float y, float speed, vec2 direction) {
    // Set line width to 1
    ofSetLineWidth(1);

    // Multiply unit vector by clamped value
    vec2 limited = direction * ofClamp(speed, 1, 30);
    // Map speed parameter to scale, clamp it in this range
    float scale = ofMap(speed, 1, 50, 0.1, 3, true);

    // Rotation angle
    float angle = atan2(gestureDirection.y, gestureDirection.x);
    ofPushMatrix();
    // Translate to mouse position
    ofTranslate(x, y);

    // Draw something different
    ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    ofSetLineWidth(ofRandom(1, 10));
    int resolution = ofMap(speed, 1, 50, 3, 20, true);
    ofBeginShape();
    for (int i = 0; i < resolution; i++) {
        float angle = ofMap(i, 0, resolution, 0, TWO_PI);
        float radius = ofMap(speed, 1, 50, 0.5, 30, true);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        ofVertex(x, y);
    }
    ofEndShape();

    // Rotating and scaling a drawing
    ofSetColor(0);
    ofScale(scale);
    // Angle aligns the rotation direction with direction of mouse
    ofRotateRad(angle);
    ofDrawTriangle(-10, -5, -10, 5, 0, 0);

    ofPopMatrix();
}

void ofApp::rectangleBrush(float x, float y) {
    // Set color to random
    ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    // Draw a rectangle at the mouse position
    ofDrawRectangle(x, y, 50, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // Switch brush mode based on key press
    if (key == 'e') {
        currentMode = ERASER;
    }
    else if (key == 'd') {
        currentMode = DYNAMIC;
    }
    else if (key == 'r') {
        currentMode = RECTANGLE;
    }
    else if (key == 'b') {
        currentMode = BRUSH;
    }

    if (key == '1') {
        brushColor = ofColor::black;
    }
    else if (key == '2') {
        brushColor = ofColor::red;
    }
    else if (key == '3') {
        brushColor = ofColor::green;
    }
    else if (key == '4') {
        brushColor = ofColor::blue;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    // Start painting
    paintIsOn = true;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    // Stop painting
    paintIsOn = false;

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
