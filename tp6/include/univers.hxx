#pragma once

#include"particule.hxx"
#include"cellule.hxx"
#include"vecteur.hxx"
#include"limite.hxx"
#include<vector>
#include<cmath>
#include<unordered_map>

class Univers {
    private:
        int nbParticules;
        int dim;
        Vecteur ld; // Taille de l'univers dans chaque direction de l'espace
        double rcut;
        Vecteur nc; // Nombre de cellules dans chaque direction de l'espace
        // Un dictionnaire pour stocker les cellules de notre univers
        // La clefs : Linéarison des coordonnées de la cellule
        // la valeurs : la cellule
        std::unordered_map<int, std::pair<Cellule, std::unordered_map<int,Particule>>> cellules;
        std::vector<Particule> particules; // Il nous faut quand même stocker l'ensemble des particules pour des questions de facilité
        LIMITE condition_limite;
        bool gravite;     //pour savoir si l'univers applique le champ gravitationnel (question 5 du tp6)
    public:
        Univers(int dim, int nbParticules, Vecteur ld, double rcut, LIMITE condition_limite, bool gravite);
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
        std::vector<Vecteur> calcul_forces(double epsilon, double sigma);
        bool est_voisine(const Particule &p1,const Particule &p2) const;
        void stromer_verlet(std::vector<Vecteur> &f_old, double dt, double tend, double epsilon, double sigma, bool affichage);
        // std::vector<Vecteur> posVoisines(Vecteur);
        bool update_part(Particule& p, Vecteur& v);
        std::vector<int> get_voisines(Cellule &c);
        bool est_voisine(const Cellule& cell1, const Cellule& cell2) const;

        void initSimuParticules(Vecteur vit, double mas);

        int linearisation(const Vecteur &v, int dimension) const;

        void testSimu(Vecteur vit, double mas);

        void testAbsorption(Vecteur vit, double mas);

        void testReflex(Vecteur vit, double mas);
};

