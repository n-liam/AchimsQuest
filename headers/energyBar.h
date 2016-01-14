#ifndef ENERGYBAR_H
#define ENERGYBAR_H

class EnergyBar: public sf::Sprite {
    
    private:
        Character* m_characterptr;
        sf::RenderWindow* m_window;
    public:
        EnergyBar(Character* character);
        void setWindow(sf::RenderWindow* window){ m_window = window;}
        void activate();
    
    
    
};

EnergyBar::EnergyBar(Character* characterptr) {
    (*this).setTexture(g_whiteDotTexture);
    (*this).setPosition(32,4);
    (*this).setColor(sf::Color::Magenta);
    m_characterptr = characterptr;
}

void EnergyBar::activate() {
    int energy = (*m_characterptr).getTether().energy();
    if(energy<10) {
        (*this).setColor(sf::Color::Red);
    }
    else
        { (*this).setColor(sf::Color::Magenta);}
    (*this).setScale(energy , 6 );
    (*m_window).draw(*this);
    
}



#endif