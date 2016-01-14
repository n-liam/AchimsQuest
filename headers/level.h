 #ifndef LEVEL_H
 #define LEVEL_H
 class Level {
     
    public:
        

        Level(const char* fileName);
        ~Level();
        
        std::vector<Tile>* getGrid() {return m_grid;}
        int width() {return m_width;}
        int height() {return m_height;}
        int size() {return m_size;}
        
        void activate();
        
    private:
        int m_width;
        int m_height;
        int m_size;
        

        std::vector<Tile>* m_grid;
     
 };
 
Level::Level(const char* fileName) {
    BitMap levelbmp(fileName);
    
    m_width = levelbmp.width();
    m_height = levelbmp.height();
    
    m_size = m_width*m_height;
    
    m_grid = new std::vector<Tile>(m_size);
    
    int xpos = 0;
    int ypos = 0;
    for(int i=0;i<m_size;i++) {
        // this puts each tile in place
        ((*m_grid)[i]).setPosition(xpos,ypos);
        xpos+=16;
        if(xpos>=g_dimx*16) {
            ypos+=16;
            xpos=0;
        }
        
        // 0 0 0 Black --- colliable all
        // 0 0 255 Blue -- collidable ghost
        // 255 0 0 Red ---- collidable you
        
        std::vector<unsigned int> rgbVec = levelbmp.getPixel( indexToX(i), indexToY(i) );
        
        //std::cout<<"("<<indexToX(i)<<","<<indexToY(i)<<"): ";
        
        if( rgbVec[0]==0 && rgbVec[1] ==0 && rgbVec[2]==0 ) {
            (*m_grid)[i].setCollidable(true);
            //std::cout<<"1 ";
        }
        else if( rgbVec[0]==255 && rgbVec[1] ==255 && rgbVec[2]==255 ) {
            
        }
        else if(rgbVec[0]==0 && rgbVec[1]==0 && rgbVec[2] ==255) {
            (*m_grid)[i].setCollidableGhostOnly(true);   
            //std::cout<<"0 ";            
        }
        else if(rgbVec[0]==255 && rgbVec[1]==0 && rgbVec[2] ==0) {
            (*m_grid)[i].setCollidableYouOnly(true);
            //std::cout<<"0 ";
        }
        /*
        else {
            std::cout<<"?" ;
        }
        if( (i+1) %20 ==0 ) {
            std::cout<<"\n";
        }*/
 
    }
    
    
}
 
Level::~Level() {
    (*m_grid).clear();
    delete m_grid;
}
 
void Level::activate() {
    g_dimx = m_width;
    g_dimy = m_height;
}
 
 #endif
