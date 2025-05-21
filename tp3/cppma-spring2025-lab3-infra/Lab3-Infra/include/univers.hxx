#pragma once

#include"particule.hxx"
#include<vector>

class Univers {
    private :
    int dim;
    int nbParticules;
    std::vector<Particule> particules;

    public:
    Univers(int dim, int nbParticules);

    void avance(Particule &p, const Vecteur dir);
    std::vector<Vecteur> calcul_forces();
    std::vector<Vecteur> calcul_forces_v2(); // methode qui permet d'aller deux fois plus vite
    void setVitesse(const Vecteur &v);
    void affiche_univers() const ;
    void stormer_verlet(std::vector<Vecteur> &f_old, double dt, double tend );
    void ajouterParticule(const Particule &p);
};