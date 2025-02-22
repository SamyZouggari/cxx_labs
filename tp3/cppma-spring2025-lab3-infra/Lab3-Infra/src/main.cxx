
#include"univers.hxx"
#include"math.h"

int main(){
    Univers u = Univers(pow(pow(2,5),3),0.0, 1.0);
    int count = 0;
    for(int i = 0 ; i<u.nbParticules ; i++){
        std::cout << u.particules[i].getPosition() << std::endl;  
        std::cout << count << std::endl;
        count++;
    }
    return 1;
}