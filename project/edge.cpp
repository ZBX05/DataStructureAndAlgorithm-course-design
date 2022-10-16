#include "edge.h"


Edge::Edge(){
    from = -1;
    to = -1;
    weight = 0;
}

Edge::Edge(int f, int t, int w){
    from = f;
    to = t;
    weight = w;
}

bool Edge::operator>(Edge& e){
    if (weight > e.weight) return 1;
    else return 0;
}
