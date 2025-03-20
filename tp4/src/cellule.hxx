#pragma once
#include<vector>
#include"particule.hxx"
#include"vecteur.hxx"



class Cellule{
    private:
    Vecteur position;
    Vecteur taille;

    public:
    Cellule(const Vecteur &position);
    Cellule();
    Vecteur getPosition() const;
    void addParticule(const Particule &p);
    //void addCelluleVoisine(const Cellule &c);
    std::vector<Particule> getParticules() const;
};