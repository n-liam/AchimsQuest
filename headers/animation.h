#ifndef ANIMATION_H
#define ANIMATION_H

namespace Animation {

    void animation() {
        if(GhostChar::ghost.facing()==-1) {
            GhostChar::ghost.setTexture(GhostChar::texture_l);
        }
        else if (GhostChar::ghost.facing()==1) {
            GhostChar::ghost.setTexture(GhostChar::texture_r);
        }
        if(MainChar::you.facing()==-1) {
            MainChar::you.setTexture(MainChar::texture_l);
        }
        else if (MainChar::you.facing()==1) {
            MainChar::you.setTexture(MainChar::texture_r);
        }
    }
    
    
    void viewControl(sf::View &view, Character character)
    {
		// the character position
		int x_pos = character.getPosition().x;
		int y_pos = character.getPosition().y;
		
		// the window dimensions
		int x_size = SCREENSIZE;
		int y_size = SCREENSIZE;
		
		// the full map dimensions
		int x_mapDim = SCREENSIZE;
		int y_mapDim =SCREENSIZE;
		
		
		// initiate the view position
		int x_view = x_pos;
		int y_view = y_pos;
		
		
		
		if ( x_pos + x_size/2  > x_mapDim ) { x_view = x_mapDim - x_size/2; }
		if ( x_pos - x_size/2 < 0 )	{ x_view = x_size/2; }
		
		if ( y_pos + y_size/2  > y_mapDim ) { y_view = y_mapDim - y_size/2; }
		if ( y_pos - y_size/2 < 0 )	{ y_view = y_size/2; }
		
		view.setCenter(x_view, y_mapDim/2);
	}
}

#endif