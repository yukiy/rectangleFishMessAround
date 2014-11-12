#include "Rectangle.h"
#include "ofMain.h"


//------------------------------------------------------------
void Rectangle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}


//------------------------------------------------------------
void Rectangle::addDampingForce(){
    
    // the usual way to write this is  vel *= 0.99
    // basically, subtract some part of the velocity
    // damping is a force operating in the oposite direction of the velocity vector
    
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}


//------------------------------------------------------------
void Rectangle::addRepulsionForce( float px, float py, float radius, float strength){
    
    
    ofPoint posOfForce;
    posOfForce.set(px, py);
    
    ofPoint diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        frc.x += diff.x * pct * strength;
        frc.y += diff.y * pct * strength;
    }
    
}

//------------------------------------------------------------
void Rectangle::addAttractionForce( float px, float py, float radius, float strength){
    
    ofPoint posOfForce;
    posOfForce.set(px, py);
    
    ofPoint diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        frc.x -= diff.x * pct * strength;
        frc.y -= diff.y * pct * strength;
    }
    
}

//------------------------------------------------------------
void Rectangle::addRepulsionForce(Rectangle &p, float radius, float scale){
    
    // ----------- (1) make a vector of where this particle p is:
    ofVec2f posOfForce;
    posOfForce.set(p.pos.x,p.pos.y);
    
    // ----------- (2) calculate the difference & length
    
    ofVec2f diff	= pos - posOfForce;
    float length	= diff.length();
    
    // ----------- (3) check close enough
    
    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
    // ----------- (4) if so, update force
    
    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
        frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
        p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void Rectangle::addAttractionForce(Rectangle &p, float radius, float scale){
    
    // ----------- (1) make a vector of where this particle p is:
    ofVec2f posOfForce;
    posOfForce.set(p.pos.x,p.pos.y);
    
    // ----------- (2) calculate the difference & length
    
    ofVec2f diff	= pos - posOfForce;
    float length	= diff.length();
    
    // ----------- (3) check close enough
    
    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
    // ----------- (4) if so, update force
    
    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
        frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
        p.frc.x = p.frc.x + diff.x * scale * pct;
        p.frc.y = p.frc.y + diff.y * scale * pct;
    }
    
}


//------------------------------------------------------------------
void Rectangle::setup(float px, float py, float vx, float vy, float _headSize){
    pos.set(px,py);
    vel.set(vx,vy);
    headSize = _headSize;
    damping = 0.09f;
    manualCtrl = false;
}


//------------------------------------------------------------
void Rectangle::update(){
    if(!manualCtrl){
        vel = vel + frc;
        pos = pos + vel;
    }

    points.push_back(pos);
    if (points.size() > 10){
        points.erase(points.begin());
    }
}


//------------------------------------------------------------------
void Rectangle::draw() {
    
    float noiseX = ofNoise(ofGetElapsedTimef()) * 3;
    float noiseY = ofNoise(ofGetElapsedTimef() + 100) * 3;


    ofSetColor(255,255,255);
    ofNoFill();

    ofBeginShape();
    float dX = 0;
    float dY = 0;

    for (int i = 0; i < points.size(); i++){
        
        ofVertex(points[i].x, points[i].y);
        
        if(i > 0){
            dX = points[i].x - points[i-1].x;
            dY = points[i].y - points[i-1].y;
            ofPushMatrix();
            ofTranslate(points[i].x, points[i].y);
            ofRotateZ(atan2(dY, dX)*180/PI);
            ofSetColor(255, 255, 255, ofMap(i, 0, points.size(), 0, 255));
            if(i == points.size()-1){
                ofFill();
                ofSetColor(255, 255, 255, ofMap(i, 0, points.size(), 0, 200));
            }
            
            float rectSize = ofMap(i, 0, points.size(), 0, headSize);
            ofSetRectMode(OF_RECTMODE_CENTER);

            if(manualCtrl){
                ofFill();
                ofSetColor(0 ,255, 0, 100);
            }

            ofRect(0, 0, rectSize, rectSize);
            ofNoFill();
            ofPopMatrix();
        }
    }
    ofEndShape();

}









