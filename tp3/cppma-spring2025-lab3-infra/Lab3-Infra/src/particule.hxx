# pragma once

#include"vecteur.hxx"

class Particule {
    public:
    Particule(Vecteur &position, Vecteur &vitesse, float &masse, int &id, std::string &categorie);

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