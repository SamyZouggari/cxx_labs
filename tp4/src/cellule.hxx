#pragma once
#include<vector>
#include"particule.hxx"
#include"vecteur.hxx"



class Cellule{
    private:
        Vecteur position;
        Vecteur taille;
        std::vector<Vecteur> indices; //positions des sommets de la cellule

    public:
        Cellule(const Vecteur &position, const Vecteur &taille);
        Cellule();
        Vecteur getPosition() const;
        std::vector<Vecteur> getIndices() const;
};