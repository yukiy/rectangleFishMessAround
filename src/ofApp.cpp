#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

    ofEnableAlphaBlending();
    ofBackground(0,0,0);
    
    isMousePressed = false;

    myRectFish.setup(ofGetWidth()/2, ofGetHeight()/2, 0, 0, 15);
    myRectFish.manualCtrl = true;

	for (int i = 0; i < 500; i++){
		Rectangle myParticle;
        /* setInitialCondition(float px, float py, float vx, float vy) */
		myParticle.setup(ofRandom(0,1000), ofRandom(0,1000), 0, 0, ofRandom(20));

        myParticle.damping = ofRandom(0.01, 0.05);

        particles.push_back(myParticle);
	}
	
}

//------ comparison routine for sort...
bool comparisonFunction(Rectangle a, Rectangle b){
    return a.pos.x < b.pos.x;
}


//--------------------------------------------------------------
void ofApp::update(){

//	for (int i = 0; i < particles.size(); i++){
//		particles[i].resetForce();
//		
//		particles[i].addAttractionForce(mouseX, mouseY, 1000, 0.1);
//		particles[i].addRepulsionForce(mouseX, mouseY, 60, 1);
//		
////		particles[i].addDampingForce();
//		particles[i].update();
//	}
    
    //---french methods
    
    sort( particles.begin(), particles.end(), comparisonFunction );
    
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
    }
    
    for (int i = 0; i < particles.size(); i++){
        for (int j = i-1; j >= 0; j--){
            if ( fabs(particles[j].pos.x - particles[i].pos.x) > 10) break;
            particles[i].addAttractionForce( particles[j], 100, 0.5);
            particles[i].addRepulsionForce( particles[j], 20, 0.5);
        }
    }
    
    
    for (int i = 0; i < particles.size(); i++){
        //--- gather to the center of a screen
        particles[i].addAttractionForce( ofGetWidth()/2, ofGetHeight()/2, 1500, 0.01);
        
        if(!isMousePressed){
            particles[i].addRepulsionForce( myRectFish, 50, 1.7);
        }else{
            particles[i].addAttractionForce(myRectFish, 1500, 0.05);
        }
//        particles[i].addDampingForce();
        particles[i].update();
    }
    
    myRectFish.resetForce();
    myRectFish.pos.set(mouseX, mouseY);
    myRectFish.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(0x000000);
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}

    if(isMousePressed){
        ofFill();
        ofSetColor(0, 255, 0, 100);
        ofCircle(mouseX, mouseY, ofNoise(ofGetElapsedTimef())*20);
        ofNoFill();
    }
    
    myRectFish.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    particles.clear();
    for (int i = 0; i < 500; i++){
        Rectangle myParticle;
        /* setInitialCondition(float px, float py, float vx, float vy) */
        myParticle.setup(ofRandom(0,1000), ofRandom(0,1000), 0, 0, ofRandom(20));
        
        myParticle.damping = ofRandom(0.01, 0.05);
        
        particles.push_back(myParticle);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    isMousePressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    isMousePressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(){
}

