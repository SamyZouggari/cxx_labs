
#include"univers.hxx"
#include"vecteur.hxx"
#include"particule.hxx"
#include"math.h"

int main() {
    Univers u = Univers(3,pow(2,7), 0.0, 1.0);
    std::vector<float> fold = u.calcul_forces();
    u.stromer_verlet(fold, 0.015,425);
    u.display_univers();
    return 1;
}