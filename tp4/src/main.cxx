#include"univers.hxx"
#include"vecteur.hxx"
#include"cellule.hxx"
#include"particule.hxx"
#include<iostream>
#include<fstream>


int main(){
    Univers u = Univers(3, 2, Vecteur(5,5,5), 2.5);
    std::cout << "Création des particules dans l'univers" << std::endl;
    int epsilon = 1;
    int sigma = 1;
    u.initParticulesRandom();
    std::cout << "\nAffichage des particules" << std::endl;
    u.display_particules();
    std::cout << "\nAffichage des cellules découpant l'univers" << std::endl;
    u.display_cellules();
    std::vector<Vecteur> f_old = u.calcul_forces(epsilon, sigma);
    // u.stromer_verlet(f_old, 0.15,10,1,1,true);
    // u.display_particules();
    return 1;
}

