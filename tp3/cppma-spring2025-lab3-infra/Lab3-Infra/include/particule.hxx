# pragma once

#include"vecteur.hxx"

class Particule {
    public:
    Particule(const Vecteur &position, const Vecteur &vitesse= Vecteur(0,0,0), double masse=0.0, int id=0, std::string categorie= "default");
    Particule(const Particule &other) = default; // constructeur par recopie par défaut car les attributs sont des types de base.

    int getId() const;
    Vecteur getPosition() const;
    void setPosition(const Vecteur &v);
    Vecteur getVitesse() const;
    void setVitesse(const Vecteur &v);
    double getMasse() const;
    std::string getCategorie() const;
    bool operator==(const Particule& other) const;
    bool operator!=(const Particule& other) const;

    private:
    Vecteur position;
    Vecteur vitesse;
    double masse;
    int id;
    std::string categorie;
};