#ifndef GHOSTCHAR_H
#define GHOSTCHAR_H


class Ghost: public Character {
    
    public:
        Ghost();
        
        void create(int pixelx, int pixely);
        void destroy();
        
        bool exists() {return m_exists;}
        void exists(bool b) {m_exists = b;}
        
        int distanceToMoveX_ghost(std::vector<Tile> grid);
        int distanceToMoveY_ghost(std::vector<Tile> grid);
        
        bool isInView(sf::View& view);
        
        void checkIfInView(sf::View& view);
        
    private:
        bool m_exists;
        
        
        
    
    
};

Ghost::Ghost() {
    m_exists = false;
}

void Ghost::create(int pixelx, int pixely) {
    (*this).setPosition(pixelx,pixely);
    m_exists = true;
}

void Ghost::destroy() {
	m_exists = false;
    (*this).setPosition(32,32);
    (*this).xvel(0);
    (*this).yvel(0);
    m_touchingFloor = false;
}

int Ghost::distanceToMoveX_ghost(std::vector<Tile> grid)  {
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
                if( grid[ coordToIndex(xValuesToTry[iii],yIntersections[jjj])].isCollidableGhost() ) {
                    distance =  16*xValuesToTry[iii] - (*this).relevantXPixelBound();
                }
            }
            else if (m_facing<0) {
                if( grid[ coordToIndex(xValuesToTry[iii]-1,yIntersections[jjj])].isCollidableGhost() ) {
                    distance =  16*xValuesToTry[iii] - (*this).relevantXPixelBound();
                }
            }
        }
    }
    return minAbsValue(distance,(*this).xvel());
}
    
int Ghost::distanceToMoveY_ghost(std::vector<Tile> grid) {
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
                if( grid[ coordToIndex(xIntersections[jjj],yValuesToTry[iii])].isCollidableGhost() ) {
                    distance =  16*yValuesToTry[iii] - (*this).relevantYPixelBound();
                    if(distance ==0) {
                        m_touchingFloor = true;
                    }
                }
            }
                
            else if(m_upOrDown<0) {
                if( grid[ coordToIndex(xIntersections[jjj],yValuesToTry[iii]-1)].isCollidableGhost() ) {
                    distance =  16*yValuesToTry[iii]- (*this).relevantYPixelBound();
                }
            }
            
        }
    }
    
    return minAbsValue(distance,(*this).yvel());
}

bool Ghost::isInView(sf::View & view) {
	if (  (*this).getPosition().x > view.getCenter().x + SCREENSIZE/2 ) {
		return false;
	}
	if ( (*this).getPosition().x < view.getCenter().x - SCREENSIZE/2 ) {
		return false;
	}
	if ( (*this).getPosition().y > view.getCenter().y + SCREENSIZE/2 ) {
		return false;
	}
	if ( (*this).getPosition().y < view.getCenter().y - SCREENSIZE/2 ) {
		return false;
	}
	return true;
}

void Ghost::checkIfInView(sf::View& view) {
	if(! (*this).isInView(view) ) {
		(*this).destroy();
	}
}

#endif 
