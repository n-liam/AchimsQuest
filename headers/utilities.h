 #ifndef UTILITIES_H
 #define UTILITIES_H
 
#define PI 3.1415

int g_dimx=200;
int g_dimy=50;
 
 int coordToIndex(int x, int y) {
     return x+g_dimx*y;
 }
 
 int indexToX(int index) {
    return index%(g_dimx);
 }
 
 int indexToY(int index) {
     return index/(g_dimx);
 }
 
bool contains(std::vector<int> v, int n) {
    for(int i=0; i<v.size(); i++) {
        if(v[i]==n) {return true;}
    }
    return false;
}
 
// returns the number which has the smaller absolute value. 
// so minAbsValue( -10,-9) returns -9
int minAbsValue(int i, int j) {
    if (abs(i)<abs(j)) {return i;}
    else {return j;}
}


// returns the closest integer in the direction of zero;
int absFloor(float a) {
    if( a>=0 ) {
        return int(floor(a));
    }
    if( a<0 ) {
        return int(ceil(a));
    }
}

int sgn( int i) {
    if(i>0) {return 1;}
    else if(i<0) {return -1;}
    else {return 0;}
}
 
 
double radToDeg(double rad) {
    return 180*rad/PI;
}


 
 #endif