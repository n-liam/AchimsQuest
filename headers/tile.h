
#ifndef TILE_H
#define TILE_H

sf::Texture g_defaultTileTexture;
class Tile: public sf::Sprite {
    
    public:
    
        static bool s_loadedDefaultTexture;
        
        Tile();
        void setCollidable(bool b);
        void setCollidableGhostOnly(bool b);
        void setCollidableYouOnly(bool b);
        
        void setRed();
        
        bool isCollidable() {return m_collidable;}
        
        
        bool isCollidableGhost();
        bool isCollidableYou();
        
        bool shouldDraw();
        
    private:
        bool m_collidable; 
        bool m_collidableGhost;
        bool m_collidableYou;
    
    
        
};


bool Tile::s_loadedDefaultTexture = false;

Tile::Tile()  {
    if(!s_loadedDefaultTexture) {
        g_defaultTileTexture.loadFromFile("sprites/tile.png");
        s_loadedDefaultTexture=true;
    }
    m_collidable = false;
    (*this).setTexture(g_defaultTileTexture); 
}

void Tile::setCollidable(bool b) {
    
    m_collidable = b;
    if(b) {
        (*this).setColor(sf::Color::Green);
    }
    else {
        (*this).setColor(sf::Color::White);
    }
}

void Tile::setCollidableGhostOnly(bool b) {
    m_collidableGhost = b;
    if(b) {
        (*this).setColor(sf::Color::White);
    }
    else {
        (*this).setColor(sf::Color::White);
    }
}

void Tile::setCollidableYouOnly(bool b) {
    m_collidableYou =  b;
    if(b) {
        (*this).setColor(sf::Color::Cyan);
    }
    else {
        (*this).setColor(sf::Color::Green);
    }
        
}

void Tile::setRed() {
    (*this).setColor(sf::Color::Red);
}

bool Tile::isCollidableYou() {
    if( m_collidable || m_collidableYou ) {
        return true;
    }
    else {
        return false;
    }
}

bool Tile::isCollidableGhost() {
    if(m_collidable || m_collidableGhost) {
        return true;
    }
    else {
       return false;
    }
}

bool Tile::shouldDraw() {
    if( m_collidable || m_collidableGhost || m_collidableYou) {
        return true;
    }
    else {
        return false;
    }
}

#endif