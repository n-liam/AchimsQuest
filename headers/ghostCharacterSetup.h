#ifndef GHOSTCHARACTERSETUP_H
#define GHOSTCHARACTERSETUP_H

namespace GhostChar {
    Ghost ghost;
    sf::Texture texture_r;
    sf::Texture texture_l;
    void setup() {
        
        texture_l.loadFromFile("sprites/character_left.png");
        
        texture_r.loadFromFile("sprites/character_right.png");
        
        
        ghost.setTexture(texture_r);
        ghost.setPosition(0,0);
        ghost.setColor(sf::Color::White);
    }
    
    
}



#endif