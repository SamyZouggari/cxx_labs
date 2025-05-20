#pragma once

#include<string>

class Particule {
    private :
        double x, y;
        double vitessex, vitessey;
        double masse;
        int id;
        std::string categorie;
    
    public:
        Particule(double x, double y, double vitessex,double vitessey, double masse, int id, std::string categorie);
        int getId() const;
        double getX() const;
        double getVitessex() const;
        double getVitessey() const;
        double getY() const;
        double getMasse() const;
        double calculateDistance(const Particule &other) const;
        std::string getCategorie() const;
        bool operator<(const Particule& other) const;  // Opérateur de comparaison pour std::set

        bool operator==(const Particule& other) const; // Opérateur d'égalité
        bool operator!=(const Particule& other) const; // Opérateur de différence

        void setX(double newX) { x = newX; }
        void setY(double newY) { y = newY; }

        void setVitessex(double newVitessex) { vitessex = newVitessex; }
        void setVitessey(double newVitessey) { vitessey = newVitessey; }
};
