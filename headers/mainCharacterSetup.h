#ifndef MAINCHARACTERSETUP_H
#define MAINCHARACTERSETUP_H

namespace MainChar {
    Character you;
    sf::Texture texture_r;
    sf::Texture texture_l;

    EnergyBar energyBar(&you);
    
    void setup() {
        
        texture_l.loadFromFile("sprites/character_left.png");
        
        texture_r.loadFromFile("sprites/character_right.png");
        
        
        you.setTexture(texture_r);
        you.setPosition(16*5,16*5);
        you.setColor(sf::Color::Cyan);
        

    }
    
    
}



#endif