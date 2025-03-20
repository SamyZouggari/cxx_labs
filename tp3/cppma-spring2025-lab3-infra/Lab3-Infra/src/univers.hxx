#pragma once

#include"particule.hxx"
#include<vector>

class Univers {
    public:
    int nbParticules;
    int dim;
    std::vector<Particule> particules;
    Univers(int dim, int nbParticules, float deb, float fin);

    void avance(Particule &p, const Vecteur dir);
    std::vector<float> calcul_forces();
    void setVitesse(const Vecteur &v);
    void display_univers() ;
    void stromer_verlet(std::vector<float> f_old, float dt, float tend );
};