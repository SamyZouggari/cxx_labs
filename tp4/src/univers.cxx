#include"univers.hxx"
#include"particule.hxx"
#include"affichage.hxx"
#include<random>
#include<vector>
#include<algorithm>
#include <cassert>

Univers::Univers(int dim, int nbParticules, Vecteur ld, float rcut):
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
    int key_cellule = cellx*nc.getZ()*nc.getY() + celly*nc.getZ() + cellz;


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


// initialisation des particules
void Univers::initParticulesRandom(){
    Vecteur debut = Vecteur(0,0,0);
    Vecteur fin = ld;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disx(0, fin.getX());
    std::uniform_real_distribution<> disy(0, fin.getY());
    std::uniform_real_distribution<> disz(0, fin.getZ());
    
    for (int i=0 ; i<nbParticules ; i++){
        float x = disx(gen);
        float y = disy(gen);
        float z = disz(gen);
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
        int positionAbsolue = cellx*nc.getZ()*nc.getY() + celly*nc.getZ() + cellz;

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

void Univers::display_particules(){
    for(int i =0 ; i< nbParticules; i++) {
        std::cout << "id = " << particules[i].getId() << std::endl;
        std::cout << "position = " << particules[i].getPosition() << std::endl;
    }
}

void Univers::display_cellules(){
    for (auto it = cellules.begin(); it != cellules.cend(); ++it) {
        std::cout << "Cellule position " << (*it).first << std::endl;
        std::cout << "Vec pos" << (*it).second.first.getPosition() << std::endl;
        
        std::unordered_map<int,Particule> part_contained = (*it).second.second;
        // Boucle qui va boucler sur les particules d'une cellule afin de les afficher
        for (auto it2 = part_contained.begin(); it2 != part_contained.cend(); ++it2){
            std::cout << "Contient particules num : " << (*it2).first << std::endl;
        }
    }
}

void Univers::stromer_verlet(std::vector<Vecteur> f_old, float dt, float tend, float epsilon, float sigma, bool affichage){
    std::vector<Vecteur> F = calcul_forces(epsilon,sigma);
    
    float t = 0;
    float x=0;
    float y=0;
    float z=0;
    float vx=0;
    float vy=0;
    float vz=0;
    int counter_file=1; //compteur pour nommer les fichiers vtk
    while (t < tend) {
        t = t + dt;
        auto it = F.begin();
        for(int i = 0 ; i<nbParticules; i++){
            Particule& p = particules[i]; 
            x = (p.getPosition()[0] + (p.getVitesse()[0] + (0.5/p.getMasse())*(*it).getX()*dt)*dt);
            y = (p.getPosition()[1] + (p.getVitesse()[1] + (0.5/p.getMasse())*(*it).getY()*dt)*dt);
            z = (p.getPosition()[2] + (p.getVitesse()[2] + (0.5/p.getMasse())*(*it).getZ()*dt)*dt);
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
            vx = p.getVitesse()[0] +  dt*(0.5/p.getMasse())*(*itF + *itF_old).getX();
            vy = p.getVitesse()[1] + dt*(0.5/p.getMasse())*(*itF + *itF_old).getY();
            vz = p.getVitesse()[2] + dt*(0.5/p.getMasse())*(*itF + *itF_old).getZ();
            Vecteur v = Vecteur (vx,vy,vz);
            p.setVitesse(v);
            std::advance(itF,1);
            std::advance(itF_old,1);
        }
    }
    
    if (affichage){
        Affichage affichage = Affichage(*this);
        affichage.create_vtk("../simulation/simu"+std::to_string(counter_file)+".vtu");
    }
}

std::vector<Vecteur> Univers::calcul_forces(float epsilon, float sigma){
    std::vector<Vecteur> forces;
    //std::vector<Vecteur> voisins;
    Vecteur r;
    float propx;
    float propy;
    float propz;
    float sumr;
    std::vector<int> cellules_voisines;
    Cellule cellule_courante;
    Vecteur sommeForce_i = Vecteur(0,0,0);
    for(Particule &p1: particules){
        cellule_courante = getCellule(Vecteur(p1.getPosition().getX(), p1.getPosition().getY(), p1.getPosition().getZ()));
        cellules_voisines = get_voisines(cellule_courante);
        for(int &hash_cellule : cellules_voisines){
            for(auto it = cellules[hash_cellule].second.begin(); it != cellules[hash_cellule].second.end() ; it++){
                Particule &p2 = it->second;
                Vecteur force_i_j= Vecteur(0,0,0);
                if(p1.getId() != p2.getId()){
                    float dist = p1.calculateDistance(p2);
                    r = p1.getPosition()-p2.getPosition();
                    sumr = r.getX()+ r.getY()+ r.getZ();
                    propx = r.getX()/sumr;
                    propy = r.getY()/sumr;
                    propz = r.getZ()/sumr;
                    if(dist>1e-5){
                        float force_scalaire = (1/dist * pow((sigma/dist),6)*(1-2*(pow((sigma/dist),6))))*24*epsilon;
                        force_i_j = Vecteur(force_scalaire*propx, force_scalaire*propy, force_scalaire*propz);
                    }
                }
                sommeForce_i+=force_i_j;
            }
        }
        forces.push_back(sommeForce_i);
    }
    // display_particules();
    return forces;
}

std::vector<int> Univers::get_voisines(Cellule &c){
    std::vector<int> cellules_voisines;
    
    Vecteur pos = c.getPosition();

    std::vector<Vecteur> voisins;
    int linearization;

    if(dim ==1){
        voisins = {Vecteur(pos.getX()-1,0,0), Vecteur(pos.getX(),0,0), Vecteur(pos.getX()+1,0,0)};
    }
    else if(dim == 2){
        voisins = {
            Vecteur(pos.getX()-1, pos.getY()-1, 0),
            Vecteur(pos.getX()-1, pos.getY(),   0),
            Vecteur(pos.getX()-1, pos.getY()+1, 0),
            
            Vecteur(pos.getX(),   pos.getY()-1, 0),
            Vecteur(pos.getX(),   pos.getY(),   0),
            Vecteur(pos.getX(),   pos.getY()+1, 0),
            
            Vecteur(pos.getX()+1, pos.getY()-1, 0),
            Vecteur(pos.getX()+1, pos.getY(),   0),
            Vecteur(pos.getX()+1, pos.getY()+1, 0)
        };
    }
    else if(dim==3){
std::vector<Vecteur> voisins = {
            // z - 1
            Vecteur(pos.getX()-1, pos.getY()-1, pos.getZ()-1),
            Vecteur(pos.getX()-1, pos.getY(),   pos.getZ()-1),
            Vecteur(pos.getX()-1, pos.getY()+1, pos.getZ()-1),
            Vecteur(pos.getX(),   pos.getY()-1, pos.getZ()-1),
            Vecteur(pos.getX(),   pos.getY(),   pos.getZ()-1),
            Vecteur(pos.getX(),   pos.getY()+1, pos.getZ()-1),
            Vecteur(pos.getX()+1, pos.getY()-1, pos.getZ()-1),
            Vecteur(pos.getX()+1, pos.getY(),   pos.getZ()-1),
            Vecteur(pos.getX()+1, pos.getY()+1, pos.getZ()-1),

            // z = 0
            Vecteur(pos.getX()-1, pos.getY()-1, pos.getZ()),
            Vecteur(pos.getX()-1, pos.getY(),   pos.getZ()),
            Vecteur(pos.getX()-1, pos.getY()+1, pos.getZ()),
            Vecteur(pos.getX(),   pos.getY()-1, pos.getZ()),
            Vecteur(pos.getX(),   pos.getY(),   pos.getZ()), 
            Vecteur(pos.getX(),   pos.getY()+1, pos.getZ()),
            Vecteur(pos.getX()+1, pos.getY()-1, pos.getZ()),
            Vecteur(pos.getX()+1, pos.getY(),   pos.getZ()),
            Vecteur(pos.getX()+1, pos.getY()+1, pos.getZ()),

            // z + 1
            Vecteur(pos.getX()-1, pos.getY()-1, pos.getZ()+1),
            Vecteur(pos.getX()-1, pos.getY(),   pos.getZ()+1),
            Vecteur(pos.getX()-1, pos.getY()+1, pos.getZ()+1),
            Vecteur(pos.getX(),   pos.getY()-1, pos.getZ()+1),
            Vecteur(pos.getX(),   pos.getY(),   pos.getZ()+1),
            Vecteur(pos.getX(),   pos.getY()+1, pos.getZ()+1),
            Vecteur(pos.getX()+1, pos.getY()-1, pos.getZ()+1),
            Vecteur(pos.getX()+1, pos.getY(),   pos.getZ()+1),
            Vecteur(pos.getX()+1, pos.getY()+1, pos.getZ()+1)
        };
    }

    for(Vecteur &v: voisins){
            linearization = v.getX()*nc[2]*nc[1] + v.getY()*nc[2] + v.getZ();
            auto ite = cellules.find(linearization);
            if(ite!=cellules.end()){
                cellules_voisines.push_back(linearization);
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
    int cellz0 = floor(p.getPosition().getY() / rcut);

    Vecteur old_cellule = Vecteur(cellx0,celly0,cellz0);
    int key_old_cellule = cellx0*nc.getZ()*nc.getY() + celly0*nc.getZ() + cellz0;

    // On doit calculer la cellule qui contiendra la particule après mouvement
    int cellx1 = floor(v.getX()/rcut);
    int celly1 = floor(v.getY()/rcut);
    int cellz1 = floor(v.getZ()/rcut);

    Vecteur new_cellule = Vecteur(cellx1,celly1,cellz1);
    int key_new_cellule = cellx1*nc.getZ()*nc.getY() + celly1*nc.getZ() + cellz1;

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