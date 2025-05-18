#include"univers.hxx"
#include"particule.hxx"
#include"affichage.hxx"
#include<random>
#include<vector>
#include<algorithm>
#include <cassert>
#include <set>
#include <cmath>

/**
 * Constructeur d'un univers
 * @param dim correspond à la dimension de l'univers, 1, 2 ou 3
 * @param nbParticules correspond au nombre de particule qui vont être présnetes dans notre univers
 * @param ld qui correspond à un vecteur indiquant la taille de l'univers dans les directions x, y et z
 * @param rcut qui est une valeur caractèristique de l'univers qui va nous permettre d'évaluer les différentes intéractions 
*/
Univers::Univers(int dim, int nbParticules, Vecteur ld, double rcut):
    dim(dim), nbParticules(nbParticules), ld(ld), rcut(rcut)
    {
        assert(dim >= 1 && dim <= 3 && "Dimension invalide !");
        // On caclule le nombre de cellule pour chaque direction
        nc = Vecteur(floor(ld[0]/rcut), floor(ld[1]/rcut), floor(ld[2]/rcut));
        //Allocation de l'espace pour stocker les particules
        //particules = (Particule*) malloc(nbParticules * sizeof(Particule));
    }

int Univers::getNbParticules() const{
    return nbParticules;
}

std::unordered_map<int, std::pair<Cellule, std::unordered_map<int,Particule>>> Univers::getCellules() const{
    return cellules;
}

Cellule Univers::getCellule(const Vecteur &p) const{
    int cellx = floor(p.getX() / rcut);
    int celly = floor(p.getY() / rcut);
    int cellz = floor(p.getZ() / rcut);
    Vecteur posCell = Vecteur(cellx, celly, cellz);
    int key_cellule = linearisation(posCell, dim);
    //int key_cellule = cellx*nc.getZ()*nc.getY() + celly*nc.getZ() + cellz;


    auto it = cellules.find(key_cellule);
    if(it != cellules.end()){
        return it->second.first;
    }
    else{
        std::cerr << "Cellule non trouvée" << std::endl;
        return Cellule(Vecteur(0,0,0), Vecteur(0,0,0));
    }
}

std::vector<Particule> Univers::get_particules() const{
    return particules;
}


/**
 * Fonction qui va nous permettre d'initialiser des particules de manière aléatoires dans notre univers
*/
void Univers::initParticulesRandom(){
    Vecteur debut = Vecteur(0,0,0);
    Vecteur fin = ld;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disx(0, fin.getX());
    std::uniform_real_distribution<> disy(0, fin.getY());
    std::uniform_real_distribution<> disz(0, fin.getZ());
    
    for (int i=0 ; i<nbParticules ; i++){
        double x = disx(gen);
        double y = disy(gen);
        double z = disz(gen);
        Vecteur v = Vecteur(x,y,z);
        Particule p = Particule(v, Vecteur(0.0,0.0,0.0), 1.0,i,"particule n° "+i);
        particules.push_back(p);

        // Après sa creation on va dans le meme temps attribuer une cellule à notre particule fraichement crée
        // Taille de la cellule dans chaque direction de l'espace
        int taillex = floor(ld.getX()/nc.getX());
        int tailley = floor(ld.getY()/nc.getY());
        int taillez = floor(ld.getZ()/nc.getZ());

        // Nous permet de savoir où se positionne la cellule dans notre univers
        int cellx = floor(p.getPosition().getX() / rcut);
        int celly = floor(p.getPosition().getY() / rcut);
        int cellz = floor(p.getPosition().getZ() / rcut);

        //linéarisation du vecteur
        int positionAbsolue = linearisation(Vecteur(cellx, celly, cellz), dim);
        //int positionAbsolue = cellx*nc.getZ()*nc.getY() + celly*nc.getZ() + cellz;

        int nb_Cellule=0;
        auto it = cellules.find(positionAbsolue);
        if(it !=cellules.end()){
             //ne fais rien s'il y a déjà la cellule contenant la particule
            // Si on a déjà vu cette clef, c'est que le cellule contient déjà une ou plusieurs particules
            it->second.second[p.getId()]=p;

             // Est-ce que c'est vraiment utile qu'une Cellule soit au courant des Particules qu'elle contient ???
        }
        else {
            // Sinon c'est que la cellule ne contient pas encore de particule
            cellules[positionAbsolue]= {Cellule(Vecteur(cellx, celly,cellz), Vecteur(taillex, tailley, taillez)),std::unordered_map<int, Particule> {{p.getId(), p}}};
        }
    }
}

/**
 * Fonction simple permettant d'afficher toutes les particules peuplant un univers, 
 * à l'aide de leur id et de leur position
*/
void Univers::display_particules(){
    for(int i =0 ; i< nbParticules; i++) {
        std::cout << "id = " << particules[i].getId() << std::endl;
        std::cout << "position = " << particules[i].getPosition() << std::endl;
    }
}

/**
 * Fonction simple permettant d'afficher les différentes cellules de l'univers. A noté que sont 
 * affichées uniquement les cellules qui contiennent au moins une particules, car sinon elles ne sont pas stockées.
 * Affiche aussi les particules présentent dans chaque cellules.
*/
void Univers::display_cellules(){
    for (auto it = cellules.begin(); it != cellules.cend(); ++it) {
        std::cout << "Cellule numéro : " << (*it).first << std::endl;

        std::cout << "Position : " << (*it).second.first.getPosition() << std::endl;
        
        std::unordered_map<int,Particule> part_contained = (*it).second.second;
        // Boucle qui va boucler sur les particules d'une cellule afin de les afficher
        for (auto it2 = part_contained.begin(); it2 != part_contained.cend(); ++it2){
            std::cout << "Contient particules num : " << (*it2).first << std::endl;
        }
    }
}

/**
 * Fonction qui va permettrent de mettre en place le mouvement des particules à l'aide de l'algorithme de Stromer Verlet
 * @param f_old un vecteur qui contient la somme des forces s'appliquant sur chaque particule
 * @param dt le pas de temps entre deux moiuvement de particules
 * @param tend : l'instant auquel on veut arrêter la simulation
 * @param epsilon, sigma : paramètres constants caractéristiques de l'univers
*/
void Univers::stromer_verlet(std::vector<Vecteur> &f_old, double dt, double tend, double epsilon, double sigma, bool affichage){

    std::vector<Vecteur> F = calcul_forces(epsilon,sigma);
    
    double t = 0;
    double x=0;
    double y=0;
    double z=0;
    double vx=0;
    double vy=0;
    double vz=0;
    int counter_file=1; //compteur pour nommer les fichiers vtk
    while (t < tend) {
        t = t + dt;
        auto it = F.begin();
        for(int i = 0 ; i<nbParticules; i++){
            Particule& p = particules[i];
            Vecteur pos = p.getPosition();
            Vecteur speed = p.getVitesse();
            double mas = p.getMasse();

            x = pos[0] + speed[0] * dt + 0.5 * (*it).getX() / mas * dt * dt;
            y = pos[1] + speed[1] * dt + 0.5 * (*it).getY() / mas * dt * dt;
            z = pos[2] + speed[2] * dt + 0.5 * (*it).getZ() / mas * dt * dt;

            if(x > ld.getX() || x<=0){
                x = pos[0];
            }
            if(y > ld.getY() || y<=0){
                y = pos[1];
            }
            if(z > ld.getZ() || z<=0){
                z = pos[2];
            }
            Vecteur v = Vecteur (x,y,z);
            // ICI on met à jour le map en fonction des nouvelles positions des particules 
            check_part(p, v);
            p.setPosition(v);
            std::advance(it,1);
        }
        //Calculer les forces F
        F = calcul_forces(epsilon, sigma);
        auto itF = F.begin();
        auto itF_old = f_old.begin();
        for(int i = 0 ; i<nbParticules; i++){ 
            Particule& p = particules[i];

            double m = p.getMasse();
            Vecteur speed = p.getVitesse();

            Vecteur F_avg = (*itF + *itF_old) * 0.5;
            vx = speed[0] + (F_avg.getX() / m) * dt;
            vy = speed[1] + (F_avg.getY() / m) * dt;
            vz = speed[2] + (F_avg.getZ() / m) * dt;
            Vecteur v = Vecteur (vx,vy,vz);
            p.setVitesse(v);
            std::advance(itF,1);
            std::advance(itF_old,1);
        }
        if (affichage){
            Affichage affichage = Affichage(*this);
            std::cout << "Génération fichier .vtu " << counter_file + 1 << "/" << (tend/dt) << std::endl; 
            affichage.create_vtk("../simulation/simu"+std::to_string(counter_file)+".vtu");
            counter_file++;
        }
        f_old= F;
    }
    

}

/**
 * Fonction qui va calculer la somme des forces qui s'appliquent sur chaque particules
*/
std::vector<Vecteur> Univers::calcul_forces(double epsilon, double sigma) {
    std::vector<Vecteur> forces(nbParticules+1, Vecteur(0.0,0.0,0.0));  // forces[i] = F_i
    Vecteur r;

    for (Particule &p1 : particules) {
        Vecteur pos1 = p1.getPosition();
        int id1 = p1.getId();

        Cellule cellule_courante = getCellule(pos1);
        std::vector<int> cellules_voisines = get_voisines(cellule_courante);

        for (int &hash_cellule : cellules_voisines) {
            for (auto &[id2, p2] : cellules[hash_cellule].second) {
                if (id2 <= id1) continue;  // Pour ne pas traiter chaque paire deux fois

                Vecteur pos2 = p2.getPosition();
                r = pos2 - pos1;

                double r2 = r.getX()*r.getX() + r.getY()*r.getY() + r.getZ()*r.getZ();
                if (r2 < rcut*rcut && r2 > 0.5) {
                    double sig2 = (sigma * sigma) / r2;
                    double sig6 = sig2 * sig2 * sig2;
                    double force_mag = (24 * epsilon * sig6 * (1 - 2 * sig6)) / r2;
                    Vecteur force = r * force_mag;

                    forces[id1] += force;
                    forces[id2] -= force;
                }
            }
        }
    }

    return forces;
}

/**
 * Fonction qui va noius permettre de récupérer les cellules voisine d'une cellule de l'univers
 * @param c : la cellule dont on veut récupérer les voisines
 * @return Un vecteur d'entier, ou chaque entier correspond au hash d'une cellule voisine de c
*/
std::vector<int> Univers::get_voisines(Cellule &c){
    std::vector<int> cellules_voisines;
    
    Vecteur pos = c.getPosition();

    int linearization;

    if(dim ==1){
        for (int i = std::max(0, (int) (pos.getX() - 1)); i <= std::min(pos.getX() + 1, nc[0] - 1); i++) {
            Vecteur v = Vecteur(i, 0, 0);
            linearization = linearisation(v, dim);
            auto ite = cellules.find(linearization);
            if (ite != cellules.end()){
                cellules_voisines.push_back(linearization);
            }
        }
    }
    else if(dim == 2){
        for (int i = std::max(0, (int) (pos.getX() - 1)); i <= std::min(pos.getX() + 1, nc[0] - 1); i++) {
            for (int j = std::max(0, (int) (pos.getY() - 1)); j <= std::min(pos.getY() + 1, nc[1] - 1); j++) {
                Vecteur v = Vecteur(i, j, 0);
                linearization = linearisation(v, dim);
                auto ite = cellules.find(linearization);
                if (ite != cellules.end()){
                    cellules_voisines.push_back(linearization);
                }
            }
        }
    }
    else if(dim==3) {
        for (int i = std::max(0, (int) (pos.getX() - 1)); i <= std::min(pos.getX() + 1, nc[0] - 1); i++) {
            for (int j = std::max(0, (int) (pos.getY() - 1)); j <= std::min(pos.getY() + 1, nc[1] - 1); j++) {
                for (int k = std::max(0, (int) (pos.getZ() - 1)); k <= std::min(pos.getZ() + 1, nc[2] - 1); k++) {
                    Vecteur v = Vecteur(i, j, k);
                    linearization = linearisation(v, dim);
                    auto ite = cellules.find(linearization);
                    if (ite != cellules.end()){
                        cellules_voisines.push_back(linearization);
                    }
                }
            }
        }
    }

    return cellules_voisines;
}

/**
 * Création d'une fonction qui prend 2 particules en paramètre et qui va renvoyer
 * si elles appartiennent à des cellules voisines ou non
 * @param part1, part2 deux particules de l'univers
 * @return true si les deux particules sont assez proches pour intéragit entre elles
 * false sinon
*/
bool Univers::est_voisine(const Particule& part1, const Particule& part2) const{
    // Partant des deux particules il nous faut retrouver la cellule à laquelle elles appartiennt
    // On retrouve à partir de la particule les coordonnées de sa cellule
    int cell1x = floor(part1.getPosition().getX() / rcut);
    int cell1y = floor(part1.getPosition().getY() / rcut);
    int cell1z = floor(part1.getPosition().getY() / rcut);

    int cell2x = floor(part2.getPosition().getX() / rcut);
    int cell2y = floor(part2.getPosition().getY() / rcut);
    int cell2z = floor(part2.getPosition().getY() / rcut);

    Vecteur posCell1 = Vecteur(cell1x, cell1y, cell1z);
    Vecteur posCell2 = Vecteur(cell2x, cell2y, cell2z);

    if (dim == 1) {
        // dans un univers en 1 dimension les voisins sont simplement la cellule elle
        // même, celle d'avant et celle d'après
        return (abs(int(posCell1.getX()) - int(posCell2.getX())) <= 1);
    } else if (dim == 2)
    {
        return ((abs(posCell1.getX() - posCell2.getX()) <= 1) && (abs(posCell1.getY() - posCell2.getY() <= 1)));
    } else if (dim == 3)
    {
        /* code */
        return ( (abs(posCell1.getX() - posCell2.getX()) <= 1) && (abs(posCell1.getY() - posCell2.getY() <= 1)) && (abs(posCell1.getZ() - posCell2.getZ() <= 1)));
    }
    return false;
}

/**
 * Fonction qui vérifie que deux cellules sont bien voisines
*/
bool Univers::est_voisine(const Cellule& cell1, const Cellule& cell2) const{
    // Partant des deux particules il nous faut retrouver la cellule à laquelle elles appartiennt
    // On retrouve à partir de la particule les coordonnées de sa cellule

    Vecteur posCell1 = cell1.getPosition();
    Vecteur posCell2 = cell2.getPosition();

    if (dim == 1) {
        // dans un univers en 1 dimension les voisins sont simplement la cellule elle
        // même, celle d'avant et celle d'après
        return (abs(int(posCell1.getX()) - int(posCell2.getX())) <= 1);
    } else if (dim == 2)
    {
        return ((abs(posCell1.getX() - posCell2.getX()) <= 1) && (abs(posCell1.getY() - posCell2.getY() <= 1)));
    } else if (dim == 3)
    {
        /* code */
        return ( (abs(posCell1.getX() - posCell2.getX()) <= 1) && (abs(posCell1.getY() - posCell2.getY() <= 1)) && (abs(posCell1.getZ() - posCell2.getZ() <= 1)));
    }
    return false;
}
/**
 * Méthode qui va être appelé une fois qu'on a calculé la nouvelle position d'une
 * particule, et qui va permettre de mettre à jour notre Map de cellule. 
 * @param p la particule avant son mouvement, pour retrouver à quelle cellule elle appartient
 * @param v nouveau vecteur position de la particule p, pour voir dans quelle cellule la particule va bouger
*/
void Univers::check_part(const Particule& p, const Vecteur& v) {
    // On doit trouver la position de la cellule qui contient p
    int cellx0 = floor(p.getPosition().getX() / rcut);
    int celly0 = floor(p.getPosition().getY() / rcut);
    int cellz0 = floor(p.getPosition().getZ() / rcut);

    Vecteur old_cellule = Vecteur(cellx0,celly0,cellz0);

    int key_old_cellule = linearisation(old_cellule, dim);
    //int key_old_cellule = cellx0*nc.getZ()*nc.getY() + celly0*nc.getZ() + cellz0;

    // On doit calculer la cellule qui contiendra la particule après mouvement
    int cellx1 = floor(v.getX()/rcut);
    int celly1 = floor(v.getY()/rcut);
    int cellz1 = floor(v.getZ()/rcut);

    Vecteur new_cellule = Vecteur(cellx1,celly1,cellz1);

    int key_new_cellule = linearisation(new_cellule, dim);
    //int key_new_cellule = cellx1*nc.getZ()*nc.getY() + celly1*nc.getZ() + cellz1;

    //maintenant on regarde si après mouvement la particule aura changé de cellule
    if (old_cellule != new_cellule){
        // Si les cellules sont différentes, il va falloir décrémenter le nombre de particules de l'ancienne cellule
        auto it = cellules.find(key_old_cellule);
        if (it != cellules.end()) {
            it->second.second.erase(p.getId());
            // cellules[key_old_cellule].second -= 1;
            // On verifie maintenant qu'il y ait encore des particules dans l'ancienne cellule, sinon on la supprime
            if (it->second.second.begin() == it->second.second.end()) { //vérifie que la liste de particule d'une cellule est vide
                // cellules.erase(key_old_cellule);
                cellules.erase(it);
            }
        }

        // Ensuite il va falloir incrémenter le nombre de particule dans la nouvelle cellule, ou la créer au besoin
        auto ite = cellules.find(key_new_cellule);
        if (ite != cellules.end()) {
            // Si la cellule existe déjà dans le map, on n'a qu'à incrémenter le compteur
            // cellules[key_new_cellule].second += 1;
            ite->second.second[p.getId()]=p;
        } else {
            // Si la cellule n'existe pas encore dans le map il faut la créer
            // Taille de la cellule dans chaque direction de l'espace
            int taillex = floor(ld.getX()/nc.getX());
            int tailley = floor(ld.getY()/nc.getY());
            int taillez = floor(ld.getZ()/nc.getZ());
            cellules.insert({key_new_cellule, {Cellule(new_cellule, Vecteur(taillex, tailley, taillez)), std::unordered_map<int, Particule>{{p.getId(), p}}}});
        }
    }
    // Si on est par rentré dans le if c'est que la particule est toujours dans la même cellule même après son mouvement donc on ne fait rien
}

/**
 * Une fonction qui va ajouter et placer les particules convenablement dans l'univers, comme le veut la simulation
 * @param vit : un vecteur vitesse correspondant à la vitesse des particules dans chaque direction de l'espace
 * @param mas : la masse de chaque particule
*/
void Univers::initSimuParticules(Vecteur vit, double mas) {
    double distInterPart = std::pow(2.0, 1.0/6.0);

    // Les lignes suivantes permettent de placer les particules du carré rouge
    Vecteur initPoint = Vecteur(102.5,40,0); // Ce sont les coordonnées de la particule en haut à gauche du carré rouge
    Vecteur pos = initPoint;
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            // on crée la particule
            Particule p = Particule(pos,vit, mas, (40*i)+j,"particule");
            particules.push_back(p);
            
            // On crée la cellule
            // Après sa creation on va dans le meme temps attribuer une cellule à notre particule fraichement crée
            // Taille de la cellule dans chaque direction de l'espace
            int taillex = floor(ld.getX()/nc.getX());
            int tailley = floor(ld.getY()/nc.getY());
            int taillez = floor(ld.getZ()/nc.getZ());

            // Nous permet de savoir où se positionne la cellule dans notre univers
            int cellx = floor(p.getPosition().getX() / rcut);
            int celly = floor(p.getPosition().getY() / rcut);
            int cellz = floor(p.getPosition().getZ() / rcut);

            //linéarisation du vecteur
            // PROBLEME : quand on met z=0 pour faire un univers en 2 dimension, la linéarisation vaudra toujours 0
            int positionAbsolue = linearisation(Vecteur(cellx, celly, cellz), dim);
            //int positionAbsolue = cellx*nc.getZ()*nc.getY() + celly*nc.getZ() + cellz;

            int nb_Cellule=0;
            auto it = cellules.find(positionAbsolue);
            if(it !=cellules.end()){
                //ne fais rien s'il y a déjà la cellule contenant la particule
                // Si on a déjà vu cette clef, c'est que le cellule contient déjà une ou plusieurs particules
                it->second.second[p.getId()]=p;

                // Est-ce que c'est vraiment utile qu'une Cellule soit au courant des Particules qu'elle contient ???
            }
            else {
                // Sinon c'est que la cellule ne contient pas encore de particule
                cellules[positionAbsolue]= {Cellule(Vecteur(cellx, celly,cellz), Vecteur(taillex, tailley, taillez)),std::unordered_map<int, Particule> {{p.getId(), p}}};
            }

            // On se décale pour générer une nouvelle particule
            double new_x = pos.getX() + distInterPart;
            pos = Vecteur(new_x, pos.getY(), pos.getZ());
        }
        // On a fini une ligne donc on descend pour en commencer une nouvelle
        double new_y = pos.getY() + distInterPart;
        pos = Vecteur(initPoint.getX(), new_y, pos.getZ());
    }

    // Maintenant il faut créer les particules du bloc bleu
    Vecteur start_point = Vecteur(35,95,0);
    Vecteur cur_pos = start_point;
    for (int i = 0; i < 40; i++){
        for (int j = 0; j < 160; j++){
            Particule p2 = Particule(cur_pos,Vecteur(), mas, (160*i)+j + 1601,"particule");
            particules.push_back(p2);

            // On crée la cellule
            // Après sa creation on va dans le meme temps attribuer une cellule à notre particule fraichement crée
            // Taille de la cellule dans chaque direction de l'espace
            int taillex = floor(ld.getX()/nc.getX());
            int tailley = floor(ld.getY()/nc.getY());
            int taillez = floor(ld.getZ()/nc.getZ());

            // Nous permet de savoir où se positionne la cellule dans notre univers
            int cellx = floor(p2.getPosition().getX() / rcut);
            int celly = floor(p2.getPosition().getY() / rcut);
            int cellz = floor(p2.getPosition().getZ() / rcut);

            //linéarisation du vecteur
            int positionAbsolue = linearisation(Vecteur(cellx, celly, cellz), dim);
            //int positionAbsolue = cellx*nc.getZ()*nc.getY() + celly*nc.getZ() + cellz;

            int nb_Cellule=0;
            auto it = cellules.find(positionAbsolue);
            if(it !=cellules.end()){
                //ne fais rien s'il y a déjà la cellule contenant la particule
                // Si on a déjà vu cette clef, c'est que le cellule contient déjà une ou plusieurs particules
                it->second.second[p2.getId()]=p2;

                // Est-ce que c'est vraiment utile qu'une Cellule soit au courant des Particules qu'elle contient ???
            }
            else {
                // Sinon c'est que la cellule ne contient pas encore de particule
                cellules[positionAbsolue]= {Cellule(Vecteur(cellx, celly,cellz), Vecteur(taillex, tailley, taillez)),std::unordered_map<int, Particule> {{p2.getId(), p2}}};
            }

            // On se décale pour générer une nouvelle particule
            double new_x = cur_pos.getX() + distInterPart;
            cur_pos = Vecteur(new_x, cur_pos.getY(), cur_pos.getZ());
        }
        // On a fini une ligne donc on descend pour en commencer une nouvelle
        double new_y = cur_pos.getY() + distInterPart;
        cur_pos = Vecteur(start_point.getX(), new_y, cur_pos.getZ());
    }
}


/**
    * Fonction de linéarisation d'un vecteur
    * @param v le vecteur à linéariser
    * @param dimension la dimension de l'univers
    * @return la valeur linéarisée du vecteur
*/
int Univers::linearisation(const Vecteur &v, int dimension) const{
    // On va linéariser le vecteur en fonction de la dimension de l'univers
    if(dimension == 1)
        return v.getX();
    else if(dimension == 2)
        return v.getX()*nc.getY() + v.getY();
    else if(dimension == 3)
        return v.getX()*nc.getZ()*nc.getY() + v.getY()*nc.getZ() + v.getZ();

    return 0;
}

/**
 * Fonction qui va nous permettre de générer un univers avec beaucoup moins de particules, afin de
 * détecter à quel moment notre calcule de force n'est pas bon
*/
void Univers::testSimu(Vecteur vit, double mas) {
    // ans un premier temps on va va ajouter qu'une seule particule sans aucune force afin de voir si elle reste bien immobile
    double distInterPart = std::pow(2.0, 1.0/6.0);

    Vecteur initPoint = Vecteur(102.5,40,0); // Ce sont les coordonnées de la particule en haut à gauche du carré rouge
    Vecteur pos = initPoint;

    Particule p = Particule(pos,vit, mas, 0,"particule");
    particules.push_back(p);
    
    // On crée la cellule
    // Après sa creation on va dans le meme temps attribuer une cellule à notre particule fraichement crée
    // Taille de la cellule dans chaque direction de l'espace
    int taillex = floor(ld.getX()/nc.getX());
    int tailley = floor(ld.getY()/nc.getY());
    int taillez = floor(ld.getZ()/nc.getZ());

    // Nous permet de savoir où se positionne la cellule dans notre univers
    int cellx = floor(p.getPosition().getX() / rcut);
    int celly = floor(p.getPosition().getY() / rcut);
    int cellz = floor(p.getPosition().getZ() / rcut);

    //linéarisation du vecteur
    // PROBLEME : quand on met z=0 pour faire un univers en 2 dimension, la linéarisation vaudra toujours 0
    int positionAbsolue = linearisation(Vecteur(cellx, celly, cellz), dim);
    //int positionAbsolue = cellx*nc.getZ()*nc.getY() + celly*nc.getZ() + cellz;

    int nb_Cellule=0;
    auto it = cellules.find(positionAbsolue);
    if(it !=cellules.end()){
        //ne fais rien s'il y a déjà la cellule contenant la particule
        // Si on a déjà vu cette clef, c'est que le cellule contient déjà une ou plusieurs particules
        it->second.second[p.getId()]=p;

        // Est-ce que c'est vraiment utile qu'une Cellule soit au courant des Particules qu'elle contient ???
    }
    else {
        // Sinon c'est que la cellule ne contient pas encore de particule
        cellules[positionAbsolue]= {Cellule(Vecteur(cellx, celly,cellz), Vecteur(taillex, tailley, taillez)),std::unordered_map<int, Particule> {{p.getId(), p}}};
    }
}