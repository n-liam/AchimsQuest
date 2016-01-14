#ifndef ENTITY_H
#define ENTITY_H


class Entity: public sf::Sprite {
    
    
    public:
        
        Entity();
        
        std::vector<int> getYIntersections(std::vector<Tile> grid);
        std::vector<int> getXIntersections(std::vector<Tile> grid);
        
        
        void incx(int i) { m_xvel+=i;}
        void incy(int i) {m_yvel+=i;}
        void xvel(int x) {m_xvel = x;}
        void yvel(int y) {m_yvel = y;}
        
        int xvel() {return m_xvel;}
        int yvel() {return m_yvel;}

    private:
        int m_xvel;
        int m_yvel;
        
        std::vector<int> m_yIntersections;
        std::vector<int> m_xIntersections;
        
        void setYIntersections(std::vector<Tile> grid); 
        void setXIntersections(std::vector<Tile> grid);
        
        
        
        
        
        
    
};

Entity::Entity() {
    m_xvel = 0;
    m_yvel = 0;
}

// returns the grid values 
void Entity::setYIntersections(std::vector<Tile> grid) {
    m_yIntersections.clear();
    for (int i=0; i<grid.size(); i++) {
        if( ((*this).getGlobalBounds()).intersects(  (grid[i].getGlobalBounds() ) )) {
            int y = indexToY(i);
            if(!contains(m_yIntersections,y)) {
                m_yIntersections.push_back(y);
            }
        }
    }
}

void Entity::setXIntersections(std::vector<Tile> grid) {
    m_xIntersections.clear();
    for (int i=0; i<grid.size(); i++) {
        if( ((*this).getGlobalBounds()).intersects(  (grid[i].getGlobalBounds() ) )) {
            int x = indexToX(i);
            if(!contains(m_xIntersections,x)) {
                m_xIntersections.push_back(x);
            }
        }
    }
}

std::vector<int> Entity::getYIntersections(std::vector<Tile> grid) {
    (*this).setYIntersections(grid);
    return m_yIntersections;
}

std::vector<int> Entity::getXIntersections(std::vector<Tile> grid) {
    (*this).setXIntersections(grid);
    return m_xIntersections;
}


#endif