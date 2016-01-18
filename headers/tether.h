#ifndef TETHER_H
#define TETHER_H

sf::Texture g_whiteDotTexture;
class Tether: public sf::Sprite {
  
    private:
        bool m_active;
        int m_energy; 
        int m_cooldown;
    
    public:
        Tether();
        void activate();
        void deactivate(); 
        bool active() {return m_active;}
        void check();
        int energy() {return m_energy;}
            
          


  
};


Tether::Tether() {
    g_whiteDotTexture.loadFromFile("sprites/whiteDot.png");
    (*this).setTexture(g_whiteDotTexture);
    (*this).setColor(sf::Color::Blue);
    //(*this).setPosition(300,300);
    //(*this).setScale(30,30);
    m_active = false;
    m_energy = 100;
    m_cooldown = 0;
}

void Tether::activate() {
    if( m_energy>10 && m_cooldown ==0) {
        m_active = true;

    }
}

void Tether::deactivate() {
    if(m_active) {
    m_active = false;
    m_cooldown = 60;
    }
}

void Tether::check() {
    if(m_cooldown!=0) {
        (*this).deactivate();
    }
    if(m_active) {
        if(m_energy ==0) {
            (*this).deactivate();
        }
        else if(m_energy>0) {
            m_energy -=1;
            if(m_energy<0) {
                m_energy =0;
            }
        }
    }
    else {
        m_cooldown-=3;
        if(m_cooldown<0) {
            m_cooldown = 0;
        }
        //std::cout<<m_cooldown<<" ";
        m_energy+=1;
        if(m_energy>100) {
            m_energy =100;
        }
        //std::cout<<m_energy<<"\t";
    }
}

#endif
