#include"univers.hxx"
#include"vecteur.hxx"
#include"cellule.hxx"
#include"particule.hxx"
#include"affichage.hxx"
#include<iostream>
#include<fstream>


int main(){
    // On crée un univers de test
    // Univers u = Univers(3, 2, Vecteur(10,10,10), 2.5);
    // std::cout << "Création des particules dans l'univers" << std::endl;
    // int epsilon = 1;
    // int sigma = 1;
    // u.initParticulesRandom();
    // std::cout << "\nAffichage des particules" << std::endl;
    // u.display_particules();
    // std::cout << "\nAffichage des cellules découpant l'univers" << std::endl;
    // u.display_cellules();
    // std::vector<Vecteur> f_old = u.calcul_forces(epsilon, sigma);
    // u.stromer_verlet(f_old, 5,10,1,1,true);
    // u.display_particules();

    // On crée un univers pour la simualation
    int eps = 5;
    int mass = 1;
    int sigm = 1;
    Vecteur vit = Vecteur(0,10,0);
    float dt = 0.00005;
    float rcut = 2.5 * sigm;
    Univers uni = Univers(2, 8000, Vecteur(250,200,0), rcut); // ld par y ne peut pas valoir 40, du coup j'ai mis 200 au pif
    std::cout << "Création des particules dans l'univers" << std::endl;
    uni.initSimuParticules(vit,mass);

    // Affichage des particules
    // uni.display_particules();

    // Affichage des cellules
    uni.display_cellules();

    Affichage aff = Affichage(uni);
    aff.create_vtk("../simulation/univers.vtk");
    return 1;
}

