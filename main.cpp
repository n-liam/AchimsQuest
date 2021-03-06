#define SCREENSIZE 800

//Ghost seems to be moving when the you're moving.


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>

#include "headers/bmp.h"
#include "headers/utilities.h"

#include "headers/tile.h"
#include "headers/entity.h"
#include "headers/tether.h"
#include "headers/character.h"
#include "headers/ghostChar.h"
#include "headers/energyBar.h"
#include "headers/level.h"


#include "headers/mainCharacterSetup.h"
#include "headers/ghostCharacterSetup.h"
#include "headers/tetherSetup.h"
#include "headers/testLevel.h"

#include "headers/animation.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREENSIZE, SCREENSIZE), "MAIN");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);
    
    sf::View view;
    view.setSize(SCREENSIZE,SCREENSIZE);
    
    TestLevel::testLevel.activate();
    
    MainChar::energyBar.setWindow(&window);

	
    MainChar::setup();
    GhostChar::setup();
    
    TestLevel::setup();
    
    
    


    while (window.isOpen())
    {
        
        if(! TestLevel::musicPlaying ) {
            TestLevel::musicPlaying = true;
            TestLevel::music.play();
        }
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
                window.close();
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    if(!GhostChar::ghost.exists() ) {
                    int x = MainChar::you.getPosition().x + MainChar::you.facing()*32;
                    int y = MainChar::you.getPosition().y;
                    GhostChar::ghost.create( x,y);
                    }
                    else {
                        GhostChar::ghost.exists(false);
                    }
                }/*
                if(event.key.code == sf::Keyboard::W) {
                    MainChar::you.tryToJump(true);
                    MainChar::you.upOrDown(-1);
                }*/
            }
            if (event.type == sf::Event::JoystickButtonPressed) {
                if (event.joystickButton.button == 5) {
                    if(!GhostChar::ghost.exists() ) {
                    int x = MainChar::you.getPosition().x + MainChar::you.facing()*32;
                    int y = MainChar::you.getPosition().y;
                    GhostChar::ghost.create( x,y);
                    }
                    else {
                        GhostChar::ghost.exists(false);
                    }
                }                
            }
            
        }
       
       /* MAIN CHAR MOVMENT */
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) >50. )
        {
            MainChar::you.upOrDown(1);    
            MainChar::you.incy(3); //so you can fast fall;
        }
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -30. || sf::Joystick::getAxisPosition(0, sf::Joystick::Z) > 20.)
        {
			// both are set for high jump right now
			if( sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -70. || sf::Joystick::getAxisPosition(0, sf::Joystick::Z) > 60.) {
				MainChar::you.setJumpHeight(Character::s_highJump);
			}
			else {
				MainChar::you.setJumpHeight(Character::s_highJump);
			}
			
            MainChar::you.tryToJump(true);
            MainChar::you.upOrDown(-1);
        }
        
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||sf::Joystick::getAxisPosition(0, sf::Joystick::X)<-50.)
        {
            MainChar::you.incx(-1*MainChar::you.accel());
            MainChar::you.moving(-1);
        }
        else if( sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||sf::Joystick::getAxisPosition(0, sf::Joystick::X)>50. )
        {
            MainChar::you.incx(1*MainChar::you.accel());
            MainChar::you.moving(1);
        }
        else {
            MainChar::you.moving(0);
        }
        if( ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)|| sf::Joystick::isButtonPressed(0, 4) )&& GhostChar::ghost.exists() )
        {
            if(GhostChar::ghost.exists() ) {
                MainChar::you.tryToTether();
            }
        }
        else {
            MainChar::you.turnOffTether();
        }
        
         /* GHOST CHAR MOVEMENT */
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::V) >50. )
        {
            GhostChar::ghost.upOrDown(1);  
            GhostChar::ghost.incy(3); //fast fall
        }
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::V) < -30. || sf::Joystick::getAxisPosition(0, sf::Joystick::R) > 20.)
        {
			
			if( sf::Joystick::getAxisPosition(0, sf::Joystick::V) < -70. || sf::Joystick::getAxisPosition(0, sf::Joystick::R) > 60.) {
				GhostChar::ghost.setJumpHeight(Character::s_highJump);
			}
			else {
				GhostChar::ghost.setJumpHeight(Character::s_highJump);
			}
            GhostChar::ghost.tryToJump(true);
            GhostChar::ghost.upOrDown(-1);
        }
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Joystick::getAxisPosition(0, sf::Joystick::U) <-50.)
        {
            GhostChar::ghost.incx(-1*GhostChar::ghost.accel());
            GhostChar::ghost.moving(-1);
        }
        else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Joystick::getAxisPosition(0, sf::Joystick::U)>50. )
        {
            GhostChar::ghost.incx(1*GhostChar::ghost.accel());
            GhostChar::ghost.moving(1);
        }
        else {
            GhostChar::ghost.moving(0);
        }
        
        

        
        
        window.clear();
        
        
        
        Animation::animation();
        
        MainChar::you.physics(GhostChar::ghost, &window);
        
        
       
        int xDist = MainChar::you.distanceToMoveX_you(*TestLevel::testLevelGrid);
        MainChar::you.move(xDist,0);
        int yDist = MainChar::you.distanceToMoveY_you(*TestLevel::testLevelGrid);
        MainChar::you.move(0, yDist);

       
        
        
        for(int i=0;i<TestLevel::levelSize;i++) {
            if( (*TestLevel::testLevelGrid)[i].shouldDraw() ){
                window.draw( (*TestLevel::testLevelGrid)[i] );
            }
        }
        
        
        
        
        
        
       
        if( GhostChar::ghost.exists()) {
           
            GhostChar::ghost.physics(MainChar::you, &window);
            int xDist_g = GhostChar::ghost.distanceToMoveX_ghost( (*TestLevel::testLevelGrid));
            GhostChar::ghost.move(xDist_g,0);
            int yDist_g = GhostChar::ghost.distanceToMoveY_ghost( (*TestLevel::testLevelGrid));
            GhostChar::ghost.move(0,yDist_g);
            window.draw(GhostChar::ghost);
        }
        else {
            GhostChar::ghost.destroy();
        }
        
        
        // this block has to come after ghost movement. {
        Animation::viewControl(view, MainChar::you); // sets the view
        window.setView(view);
        
        MainChar::energyBar.updatePosition(view);
        
        GhostChar::ghost.checkIfInView(view);
        
        // }
        
        
        
        
        window.draw(MainChar::you);
        
        MainChar::energyBar.activate(); //also draws energybar
        
        
        
        
        
        
        
        window.display();
        
        
		
		// axes for joystick
		//R-- right trigger
		//Z-- left trigger
		//U-- x, right joystick
		//V-- y, right joystick
		
    }

    return 0;
}

/*
cl main.cpp entity.cpp /I SFML\SFML-2.3.1\include /link SFML\SFML-2.3.1\lib\sfml-graphics.lib SFML\SFML-2.3.1\lib\sfml-window.lib SFML\SFML-2.3.1\lib\sfml-system.lib SFML\SFML-2.3.1\lib\sfml-audio.lib
*/
