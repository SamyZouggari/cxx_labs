#pragma once

#include"particule.hxx"
#include"cellule.hxx"
#include"vecteur.hxx"
#include<vector>
#include<cmath>

class Univers {
    private:
    int nbParticules;
    int dim;
    Vecteur ld;
    float rcut;
    int nc;
    Cellule* cellules;

    public:
    Univers(int dim, int nbParticules, float deb, float fin, Vecteur ld, float rcut);
    Cellule getCellule(const Vecteur &p) const;
    std::vector<Cellule> getCellulesVoisines(const Cellule &c) const;
    void displayUnivers();
    void createParticules();
};

