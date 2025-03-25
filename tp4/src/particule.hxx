# pragma once

#include"vecteur.hxx"

class Particule {
    public:
    Particule(Vecteur &position, Vecteur vitesse= Vecteur(0,0,0), float masse=0.0, int id=0, std::string categorie= "default");
    Particule();
    int getId() const;
    Vecteur getPosition() const;
    void setPosition(const Vecteur &v);
    Vecteur getVitesse() const;
    void setVitesse(const Vecteur &v);
    float getMasse() const;
    float calculateDistance(const Particule other);
    std::string getCategorie() const;
    Vecteur vecteurCylindrique(const Particule &p2) const;
    private:
    Vecteur position;
    Vecteur vitesse;
    float masse;
    int id;
    std::string categorie;
};