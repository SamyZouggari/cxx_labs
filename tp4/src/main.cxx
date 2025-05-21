#include"univers.hxx"
#include"vecteur.hxx"
#include"cellule.hxx"
#include"particule.hxx"
#include"affichage.hxx"
#include<iostream>
#include<filesystem>


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
    double eps = 5;
    double mass = 1;
    double sigm = 1;
    Vecteur vit = Vecteur(0,10,0);
    double dt = 0.00005;
    double rcut = 2.5 * sigm;
    Univers uni = Univers(2, 8000, Vecteur(250,200,0), rcut); // ld par y ne peut pas valoir 40, du coup j'ai mis 200 au pif
    double tend = 19.5;

    std::cout << "Création des particules dans l'univers" << std::endl;
    uni.initSimuParticules(vit,mass);
    std::cout << "Particules crées avec succès !" << std::endl;

    // Affichage des particules
    // uni.display_particules();
    std::string path = "../simulation";
    if (!std::filesystem::exists(path)) {
        if (std::filesystem::create_directory(path)) {
            std::cout << "Dossier '" << path << "' créé avec succès." << std::endl;
        } else {
            std::cerr << "Erreur lors de la création du dossier." << std::endl;
        }
    } else {
        std::cout << "Le dossier existe déjà." << std::endl;
    }
    // Affichage des cellules
    Affichage aff = Affichage(uni);
    // std::cout << "Génération fichier .vtu " << 1 << "/" << (tend/dt) << std::endl;
    std::cout << "\rGénération fichier .vtu " << 1 << "/" << static_cast<int>(tend/dt) << std::flush;
    aff.create_vtk("../simulation/simu0.vtu");

    std::cout << std::endl;
    std::cout << "Début du mouvement des particules..." << std::endl;
    std::vector<Vecteur> f_old = uni.calcul_forces(eps, sigm);
    uni.stromer_verlet(f_old, dt, tend, eps, sigm, true);

    std::cout << std::endl;
    std::cout << "Fin simulation" << std::endl;
    std::cout << "Tous les fichiers .vtu ont été générés avec succès." << std::endl;
    std::cout << "Vous pouvez ouvrir les fichiers présnets dans le dossier /simulation sur paraview" << std::endl;


    // // On va créer un univers avec une seule particule sans vitesse et sans force afin de vérifier qu'elle reste bien immobile
    // int eps = 5;
    // int mass = 1;
    // int sigm = 1;
    // Vecteur vit = Vecteur(0,10,0);
    // float dt = 0.005;
    // float rcut = 2.5 * sigm;
    // Univers uni = Univers(2, 1, Vecteur(250,200,0), rcut); // ld par y ne peut pas valoir 40, du coup j'ai mis 200 au pif
    // std::cout << "Création des particules dans l'univers" << std::endl;
    // uni.testSimu(vit,mass);

    // // Affichage des particules
    // uni.display_particules();

    // // Affichage des cellules
    // uni.display_cellules();

    // // Affichage aff = Affichage(uni);
    // // aff.create_vtk("../simulation/simu0.vtu");
    // uni.stromer_verlet(uni.calcul_forces(eps, sigm), dt, 0.05, eps, sigm, true);

    // std::cout << "Apres mouvement : " << std::endl;
    // uni.display_particules();
    // uni.display_cellules();

    return 1;
}

