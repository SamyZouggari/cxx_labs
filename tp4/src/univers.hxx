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
        std::unordered_map<int, std::pair<Cellule, std::unordered_map<int,Particule>>> cellules;
        std::vector<Particule> particules; // Il nous faut quand même stocker l'ensemble des particules pour des questions de facilité

    public:
        Univers(int dim, int nbParticules, Vecteur ld, float rcut);
        Cellule getCellule(const Vecteur &p) const;
        std::vector<Particule> get_particules() const;
        int getNbParticules() const;
        std::unordered_map<int, std::pair<Cellule, std::unordered_map<int,Particule>>> getCellules() const;
        std::vector<Cellule> getCellulesVoisines(const Cellule &c) const;
        void displayUnivers();
        void initParticulesRandom();
        void display_particules();
        void display_cellules();
        void display_univers();
        std::vector<Vecteur> calcul_forces(float epsilon, float sigma);
        bool est_voisine(const Particule &p1,const Particule &p2) const;
        void stromer_verlet(std::vector<Vecteur> f_old, float dt, float tend, float epsilon, float sigma, bool affichage);
        // std::vector<Vecteur> posVoisines(Vecteur);
        void check_part(const Particule& p, const Vecteur& v);
        std::vector<int> get_voisines(Cellule &c);
        bool est_voisine(const Cellule& cell1, const Cellule& cell2) const;

        void initSimuParticules(Vecteur vit, float mas);

        int linearisation(const Vecteur &v, int dimension) const;

        void testSimu(Vecteur vit, float mas);
};

