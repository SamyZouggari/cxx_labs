#include"particule.hxx"
#include"univers.hxx"
#include"limite.hxx"
#include"affichage.hxx"

int main(){
    // Création d'un univers
    double eps = 0;
    double mass = 1;
    double sigm = 1;
    Vecteur vit = Vecteur(10.0,5.0,0);
    double dt = 0.005;
    double rcut = 2.5 * sigm;
    LIMITE cond_lim{LIMITE::REFLEXION_POTENTIEL};
    Univers uni = Univers(2, 1600, Vecteur(50.0,50.0,0), rcut, cond_lim, false); // ld par y ne peut pas valoir 40, du coup j'ai mis 200 au pif
    double tend = 10;

    std::cout << "Création des particules dans l'univers" << std::endl;
    // uni.testReflex(vit, mass);
    uni.testReflex(vit, mass);

    // Affichage des cellules
    Affichage aff = Affichage(uni);
    // std::cout << "Génération fichier .vtu " << 1 << "/" << (tend/dt) << std::endl;
    std::cout << "\rGénération fichier .vtu " << 1 << "/" << static_cast<int>(tend/dt) << std::flush;
    aff.create_vtk("../simulation/simu0.vtu");

    std::cout << "Début du mouvement des particules..." << std::endl;
    // std::vector<Vecteur> f_old(8000, Vecteur(0, 0, 0));
    std::vector<Vecteur> f_old = uni.calcul_forces(eps, sigm);
    uni.stromer_verlet(f_old, dt, tend, eps, sigm, true);

    std::cout << std::endl;
    std::cout << "Fin simulation" << std::endl;
    std::cout << "Tous les fichiers .vtu ont été générés avec succès." << std::endl;
    std::cout << "Vous pouvez ouvrir les fichiers présnets dans le dossier /simulation sur paraview" << std::endl;

    return 1;
}