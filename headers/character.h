#ifndef CHARACTER_H
#define CHARACTER_H

class Character: public Entity {
    private:
        
        
        int m_accel; //running accel
        
        int m_moving; //right left or no |--> 1 -1 0
        
        float m_accelFromGravity;
        float m_frictionDecel;
        
        bool m_tryToJump;
        int m_jumpHeight;
        
        Tether m_tether;
        bool m_isTethered;
        
        
        void gravity();
        void jump();
        
      
    
    public:
    
		static int s_highJump; //jump height
		static int s_lowJump;
        bool m_touchingFloor;
        int m_facing;
        int m_upOrDown; //-1 is up, 1 is down
        
    
        int relevantXGridBound();
        int relevantYGridBound();
        int relevantXPixelBound();
        int relevantYPixelBound();
        
        int distanceToMoveX(std::vector<Tile> grid);
        int distanceToMoveY(std::vector<Tile> grid);
        
        int distanceToMoveX_you(std::vector<Tile> grid);
        int distanceToMoveY_you(std::vector<Tile> grid);
    
        void facing(int i) { m_facing = i;}
        int facing() {return m_facing;}
        
        void upOrDown(int i) {m_upOrDown = i;}
        int upOrDown() {return m_upOrDown;}
        
        void tryToJump(bool b) {m_tryToJump = b;}
        bool tryingToJump() {return m_tryToJump;}
        void setJumpHeight(int i) { m_jumpHeight =i;}
        
        void moving(int i) {m_moving = i;}
        
        void tether(Character other, sf::RenderWindow* window);
        void tryToTether();
        void tetherCheck();
        Tether getTether() {return m_tether;}
        void turnOffTether(){m_isTethered=false;m_tether.deactivate();}
        
        int accel() {return m_accel;}
        
        
        
        void physics(Character other, sf::RenderWindow * window);
       
        
        
        Character();
    
};

int Character::s_highJump= -8;
int Character::s_lowJump = -4;

Character::Character()  {
    m_facing = 0;
    m_upOrDown = 0;
    (*this).setOrigin(8,8); //Origin is center of object
    m_touchingFloor = false;
    m_accelFromGravity = 0.;
    m_accel = 1;
    m_frictionDecel = 0.;
}

int Character::relevantXGridBound() {
    
    if( m_facing >= 0 ) {
        int pixelValue = 8 + (*this).getPosition().x;
        
        // The code below will return the grid position instead of pixel position
        for(int i=0;i<16;i++) {
            if(pixelValue%16==0) {
                return pixelValue/16;
            }
            pixelValue++;
        }
    }
    else if (m_facing<0) {
        
        int pixelValue = -8 + (*this).getPosition().x;
        
        for(int i=0;i<16;i++) {
            if(pixelValue%16==0) {
                return pixelValue/16;
            }
            pixelValue--;
        }
    }
}

int Character::relevantXPixelBound() {
    
    if( m_facing >= 0 ) {
        int pixelValue = 8 + (*this).getPosition().x;
        return pixelValue;
    }
    else if (m_facing<0) {
        
        int pixelValue = -8 + (*this).getPosition().x;
        return pixelValue;
    }
}

int Character::relevantYGridBound() {
    
    if( m_upOrDown >= 0 ) {
        int pixelValue = 8 + (*this).getPosition().y;
        
        for(int i=0;i<16;i++) {
            if(pixelValue%16==0) {
                return pixelValue/16;
            }
            pixelValue++;
        }
    }
    else if (m_upOrDown<0) {
        
        int pixelValue = -8 + (*this).getPosition().y;
      
        for(int i=0;i<16;i++) {
            if(pixelValue%16==0) {
                return pixelValue/16;
            }
            pixelValue--;
        }
    }
   
}

int Character::relevantYPixelBound() {
    
    if( m_upOrDown >= 0 ) {
        int pixelValue = 8 + (*this).getPosition().y;
        return pixelValue;
    }
    else if (m_upOrDown<0) {
        
        int pixelValue = -8 + (*this).getPosition().y;
        return pixelValue;
    }
   
}

/* These collision functions not tested for when velocities are greater than 16. */

int Character::distanceToMoveX(std::vector<Tile> grid) {
    if( (*this).xvel() >8) {(*this).xvel(8);}
    std::vector<int> yIntersections = (*this).getYIntersections(grid);
    int intendedDistance=(*this).xvel();
    int nextGridValue= (*this).relevantXGridBound();
    std::vector<int> xValuesToTry;
    xValuesToTry.push_back(nextGridValue);
    int i=m_facing;
    while(intendedDistance) {
        intendedDistance/=16;
        if(intendedDistance) {
            xValuesToTry.push_back(nextGridValue+i);
            std::cout<<"REACHED CHARACTER.H "<<__LINE__<<" ";
        }
        i+=m_facing;
    }
    int distance = (*this).xvel();
    for(int iii=0;iii<xValuesToTry.size();iii++) {
        for(int jjj=0;jjj<yIntersections.size();jjj++) {
            if(m_facing>=0) {    
                if( grid[ coordToIndex(xValuesToTry[iii],yIntersections[jjj])].isCollidable() ) {
                    distance =  16*xValuesToTry[iii] - (*this).relevantXPixelBound();
                }
            }
            else if (m_facing<0) {
                if( grid[ coordToIndex(xValuesToTry[iii]-1,yIntersections[jjj])].isCollidable() ) {
                    distance =  16*xValuesToTry[iii] - (*this).relevantXPixelBound();
                }
            }
        }
    }
    return minAbsValue(distance,(*this).xvel());
}

int Character::distanceToMoveY(std::vector<Tile> grid) {
     if( (*this).yvel() >8) {(*this).yvel(8);}
    std::vector<int> xIntersections = (*this).getXIntersections(grid);
    int intendedDistance=(*this).yvel();
    int nextGridValue= (*this).relevantYGridBound();
    std::vector<int> yValuesToTry;
    yValuesToTry.push_back(nextGridValue);
    int i=m_upOrDown;
    while(intendedDistance) {
        intendedDistance/=16;
        if(intendedDistance) {
            yValuesToTry.push_back(nextGridValue+i);
        }
        i+=m_upOrDown;
    }
    int distance = (*this).yvel();
    for(int iii=0;iii<yValuesToTry.size();iii++) {
        for(int jjj=0;jjj<xIntersections.size();jjj++) {
            if(m_upOrDown>=0) {
                if( grid[ coordToIndex(xIntersections[jjj],yValuesToTry[iii])].isCollidable() ) {
                    distance =  16*yValuesToTry[iii] - (*this).relevantYPixelBound();
                    if(distance ==0) {
                        m_touchingFloor = true;
                    }
                }
            }
                
            else if(m_upOrDown<0) {
                if( grid[ coordToIndex(xIntersections[jjj],yValuesToTry[iii]-1)].isCollidable() ) {
                    distance =  16*yValuesToTry[iii]- (*this).relevantYPixelBound();
                }
            }
            
        }
    }
    
    return minAbsValue(distance,(*this).yvel());
}

int Character::distanceToMoveX_you(std::vector<Tile> grid)  {
    if( (*this).xvel() >8) {(*this).xvel(8);}
    std::vector<int> yIntersections = (*this).getYIntersections(grid);
    int intendedDistance=(*this).xvel();
    int nextGridValue= (*this).relevantXGridBound();
    std::vector<int> xValuesToTry;
    xValuesToTry.push_back(nextGridValue);
    int i=m_facing;
    while(intendedDistance) {
        intendedDistance/=16;
        if(intendedDistance) {
            xValuesToTry.push_back(nextGridValue+i);
            std::cout<<"REACHED CHARACTER.H "<<__LINE__<<" ";
        }
        i+=m_facing;
    }
    int distance = (*this).xvel();
    for(int iii=0;iii<xValuesToTry.size();iii++) {
        for(int jjj=0;jjj<yIntersections.size();jjj++) {
            if(m_facing>=0) {    
                if( grid[ coordToIndex(xValuesToTry[iii],yIntersections[jjj])].isCollidableYou() ) {
                    distance =  16*xValuesToTry[iii] - (*this).relevantXPixelBound();
                }
            }
            else if (m_facing<0) {
                if( grid[ coordToIndex(xValuesToTry[iii]-1,yIntersections[jjj])].isCollidableYou() ) {
                    distance =  16*xValuesToTry[iii] - (*this).relevantXPixelBound();
                }
            }
        }
    }
    return minAbsValue(distance,(*this).xvel());
}
    
int Character::distanceToMoveY_you(std::vector<Tile> grid) {
     if( (*this).yvel() >8) {(*this).yvel(8);}
    std::vector<int> xIntersections = (*this).getXIntersections(grid);
    int intendedDistance=(*this).yvel();
    int nextGridValue= (*this).relevantYGridBound();
    std::vector<int> yValuesToTry;
    yValuesToTry.push_back(nextGridValue);
    int i=m_upOrDown;
    while(intendedDistance) {
        intendedDistance/=16;
        if(intendedDistance) {
            yValuesToTry.push_back(nextGridValue+i);
        }
        i+=m_upOrDown;
    }
    int distance = (*this).yvel();
    for(int iii=0;iii<yValuesToTry.size();iii++) {
        for(int jjj=0;jjj<xIntersections.size();jjj++) {
            if(m_upOrDown>=0) {
                if( grid[ coordToIndex(xIntersections[jjj],yValuesToTry[iii])].isCollidableYou() ) {
                    distance =  16*yValuesToTry[iii] - (*this).relevantYPixelBound();
                    if(distance ==0) {
                        m_touchingFloor = true;
                    }
                }
            }
                
            else if(m_upOrDown<0) {
                if( grid[ coordToIndex(xIntersections[jjj],yValuesToTry[iii]-1)].isCollidableYou() ) {
                    distance =  16*yValuesToTry[iii]- (*this).relevantYPixelBound();
                }
            }
            
        }
    }
    
    return minAbsValue(distance,(*this).yvel());
}

void Character::gravity() {
  
    int terminalVelocity = 20;
   
    m_accelFromGravity+=0.5;
    if (m_accelFromGravity>=1.0) {
        (*this).incy(1);
        m_accelFromGravity = 0.;
    }
    
    if( (*this).yvel() >= terminalVelocity ) {  
        (*this).yvel(terminalVelocity);
    }
    if( (*this).yvel() >=0 ) {
        m_upOrDown = 1;
    }
    
}

void Character::jump() {
	
    (*this).incy(m_jumpHeight); //set initial jump velocity
}

void Character::physics(Character other, sf::RenderWindow * window) {
    (*this).tetherCheck();
    if((*this).yvel()!=0) {
        (*this).upOrDown(sgn((*this).yvel()));
    }
    
    if(! m_isTethered) {
        if(m_touchingFloor) {
            (*this).yvel(0);
            if(m_tryToJump) {
                (*this).jump();
                (*this).tryToJump(false);
                m_accelFromGravity = 0.;
            }        
        }
    
        (*this).gravity();
    }
    
    m_touchingFloor = false;
    
    //  terminal forwards velocity
    // friction is handled at key input time
    int terminalVel = 6;
    if( (*this).xvel() >=terminalVel ) {
        (*this).xvel(terminalVel);
    }
    else if( (*this).xvel() <=-1*terminalVel ) {
        (*this).xvel(-1*terminalVel);
    }
    if( (*this).xvel() != 0 ) {
        m_facing = sgn( (*this).xvel() );
    }
    
    // This controls how powerful friction is. Bigger is stronger
    float friction = 1.6    ;
    
    if( (*this).xvel()==0 ) {
        m_frictionDecel = 0.;
    }
    
    if( (*this).xvel()>0 && m_facing>0 && m_moving!=1 ) { 
        /* m_moving (in previous line) checks if 'D' key is pressed. 
        Friction disabled while actively moving that direction */
        m_frictionDecel+=friction;
        if(m_frictionDecel>=1.) {
            (*this).incx(-1);
            m_frictionDecel=0.;
            if( (*this).xvel() < 0) {
                (*this).xvel(0);
            }
        }
    }
    else if( (*this).xvel()<0 && m_facing<0 && m_moving!=-1 ) {
        // See comment above for explanation of m_moving
        m_frictionDecel+=friction;
        if(m_frictionDecel>=1.) {
            (*this).incx(1);
            m_frictionDecel=0.;
            if( (*this).xvel()>0 ) {
                (*this).xvel(0);
            }
        }
    }
    
    //Tethering stuff;
    
    if( m_isTethered) {
        (*this).yvel(0);
        (*this).tether(other,window);
    }
    
}

void Character::tryToTether() {
    m_tether.activate();
    m_isTethered = m_tether.active();
}

void Character::tetherCheck() {
    m_tether.check();
    if( !m_tether.active() ) {
        m_isTethered = false;
    }
}

void Character::tether(Character other, sf::RenderWindow* window) {
    
    m_tether.activate();
    if(m_tether.active()) {
        int mainX = (*this).getPosition().x;
        int mainY = (*this).getPosition().y; 
        int ghostX = other.getPosition().x; 
        int ghostY = other.getPosition().y;
        
        int xDist = ghostX-mainX;
        int yDist = ghostY-mainY;
        
        double tetherDist = sqrt(xDist*xDist + yDist*yDist);
       
        double tetherAngle = atan2( yDist, xDist);//in rad
        tetherAngle =  radToDeg(tetherAngle); //convert to deg;
        
        m_tether.setScale( tetherDist, 2);
        m_tether.setRotation( tetherAngle);
        m_tether.setPosition( mainX, mainY);
      
        (*window).draw(m_tether);
        
        //now to follow the tether:
        if(tetherDist>1.) {
            float x = xDist;
            float y = yDist;
            //if( x==0){x=1;}
            //if( y==0){y=1;}
            x=x/sqrt(x*x+y*y);
            y=y/sqrt(x*x+y*y);
            
            (*this).incx(5*x); // coefficient affects tether strength
            (*this).incy(5*y);
            (*this).upOrDown(sgn(floor(y)));
        }
    }
}



#endif
