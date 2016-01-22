 #ifndef TESTLEVEL_H
 #define TESTLEVEL_H
 
 namespace TestLevel {
     

     
     Level testLevel("levels/testlevel.bmp");
     std::vector<Tile>* testLevelGrid = testLevel.getGrid();
     sf::Music music;
     bool musicPlaying;
    void setup() {
        musicPlaying = false;
         if(!music.openFromFile("music/Achims_Quest_3_Theme.flac") ) {
            std::cerr<<"Unable to open music\n";
        }
        music.setLoop(true);
    }
     
     int levelWidth = testLevel.width();
     int levelHeight = testLevel.height();
     int levelSize = testLevel.size();
     
     
 
    int getx(int index) {
        return index%(20);
    }
 
    int gety(int index) {
        return index/(20);
    }
     
    void test() {
        for(int i = 0; i<100;i++) {
                if( (*testLevelGrid)[i].isCollidable() ) {
                    std::cout<<"1 ";
                }
                else {
                    std::cout<<"0 ";
                }
                if( (i+1) %20 ==0 ) {
                    std::cout<<"\n";
                }
            
        }
    }
     /*
    const int levelWidth = 50;
    const int levelHeight = 50;
    const int levelSize = levelWidth*levelHeight;
    std::vector<Tile> testLevelGrid(levelSize);
    
    
    BitMap levelbmp("levels/testlevel.bmp");
    
    
    void setTestGrid() {
        
        if( levelbmp.width() != levelWidth || levelbmp.height() != levelHeight ) {
            std::cerr<<"Bad Dimensions. testLevel.h\n";
        }
        
        int xpos = 0;
        int ypos = 0;
        for(int i=0;i<levelSize;i++) {
            // this puts each tile in place
            (testLevelGrid[i]).setPosition(xpos,ypos);
            xpos+=16;
            if(xpos>=SCREENSIZE) {
                ypos+=16;
                xpos=0;
            }
            
            std::vector<unsigned int> rgbVec = levelbmp.getPixel( indexToX(i), indexToY(i) );
            if( rgbVec[0]==0 && rgbVec[1] ==0 && rgbVec[2]==0 ) {
                testLevelGrid[i].setCollidable(true);
            }
            else if(rgbVec[0]==0 && rgbVec[1]==0 && rgbVec[2] ==255) {
                testLevelGrid[i].setCollidableGhostOnly(true);
            }
            else if(rgbVec[0]==255 && rgbVec[1]==0 && rgbVec[2] ==0) {
                testLevelGrid[i].setCollidableYouOnly(true);
            }
            
            
            /*
            if( indexToY(i)==7 && indexToX(i)<17) {
                (testLevelGrid[i]).setCollidable(true);
            }
            if( indexToY(i)==7 && (indexToX(i)==5 || indexToX(i)==6)) {
                (testLevelGrid[i]).setCollidable(false);
            }
            if(indexToY(i)==0 || indexToX(i)==0 || indexToY(i)==49 || indexToX(i)==49) {
                testLevelGrid[i].setCollidable(true);
            }
            
            
            
        }
        
    }
    */
 
 
 }
 #endif
