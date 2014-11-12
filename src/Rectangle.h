#pragma once

#include "ofMain.h"

class Rectangle {
    
    public:
        
        //Rectangle();
        void setup(float px, float py, float vx, float vy, float _headSize);
        void update();
        void draw();

        void resetForce();
        void addDampingForce();
        void addRepulsionForce( Rectangle &p, float radius, float scale);
        void addRepulsionForce( float px, float py, float radius, float strength);
        void addAttractionForce(Rectangle & p, float radius, float scale);
        void addAttractionForce( float px, float py, float radius, float strength);
        void setInitialCondition(float px, float py, float vx, float vy);

        vector < ofPoint > points;
        
        float headSize;
        float damping;

        ofPoint pos;
        ofPoint frc;
        ofPoint vel;
    
        bool manualCtrl;

};
