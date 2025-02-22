# pragma once

#include"vecteur.hxx"

class Particule {
    public:
    Particule(Vecteur &position, Vecteur vitesse= Vecteur(0,0,0), float masse=0.0, int id=0, std::string categorie= "default");

    int getId();
    Vecteur & getPosition();
    Vecteur & getVitesse();
    float & getMasse();
    float calculateDistance(Particule other);
    std::string getCategorie();

    private:
    Vecteur position;
    Vecteur vitesse;
    float masse;
    int id;
    std::string categorie;
};