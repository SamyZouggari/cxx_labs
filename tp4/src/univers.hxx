#pragma once

#include"particule.hxx"
#include"cellule.hxx"
#include"vecteur.hxx"
#include<vector>
#include<cmath>
#include<unordered_map>

class Univers {
    private:
        int nbParticules;
        int dim;
        Vecteur ld; // Taille de l'univers dans chaque direction de l'espace
        float rcut;
        Vecteur nc; // Nombre de cellules dans chaque direction de l'espace
        // Un dictionnaire pour stocker les cellules de notre univers
        // La clefs : Linéarison des coordonnées de la cellule
        // la valeurs : la cellule
        std::unordered_map<int, Cellule> cellules;
        Particule* particules; // Il nous faut quand même stocker l'ensemble des particules pour des questions de facilité

    public:
        Univers(int dim, int nbParticules, Vecteur ld, float rcut);
        Cellule getCellule(const Vecteur &p) const;
        std::vector<Cellule> getCellulesVoisines(const Cellule &c) const;
        void displayUnivers();
        void initParticulesRandom();
        void display_particules();
        void display_cellules();
        void display_univers();
        ~Univers();
        std::vector<float> calcul_forces();
        void stromer_verlet(std::vector<float> f_old, float dt, float tend);
        std::vector<Vecteur> posVoisines(Vecteur);
};

