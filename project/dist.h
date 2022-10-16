#ifndef DIST_H
#define DIST_H

class Dist{
public:
    Dist(){
        index = 0;
        length = 0;
        pre = 0;
    }
    int index;
    int length;
    int pre;
    bool operator>(Dist& d){
        if (length > d.length) return 1;
        else return 0;
    }

};

#endif // DIST_H
