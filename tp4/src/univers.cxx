#include"univers.hxx"
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
        particules = new Particule[nbParticules];
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
        // particules.push_back(p);
        particules[i] = p;

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
        int positionAbsolue = cellx*nc[2]*nc[1] + celly*nc[2] + cellz;


        auto it = cellules.find(positionAbsolue);
        if(it !=cellules.end()){
            continue; //ne fais rien s'il y a déjà la cellule contenant la particule
            // Si on a déjà vu cette clef, c'est que le cellule contient déjà une ou plusieurs particules

            //it->second.addParticule(p); // Est-ce que c'est vraiment utile qu'une Cellule soit au courant des Particules qu'elle contient ???
        }
        else {
            // Sinon c'est que la cellule ne contient pas encore de particule
            cellules.insert({positionAbsolue, Cellule(Vecteur(cellx, celly,cellz), Vecteur(taillex, tailley, taillez))});
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
        std::cout << "Vec pos" << (*it).second.getPosition() << std::endl;
    }
}

Univers::~Univers() {
    delete [] particules;
}

void Univers::stromer_verlet(std::vector<float> f_old, float dt, float tend, float epsilon, float sigma){
    std::vector<Vecteur> F = calcul_forces(epsilon,sigma);
    float t = 0;
    float x=0;
    float y=0;
    float z=0;
    float vx=0;
    float vy=0;
    float vz=0;
    while (t < tend) {
        t = t + dt;
        auto it = F.begin();
        for(int i = 0 ; i<nbParticules; i++){
            Particule& p = particules[i]; 
            x = (p.getPosition()[0] + (p.getVitesse()[0] + (0.5/p.getMasse())*(*it).getX()*dt)*dt);
            y = (p.getPosition()[1] + (p.getVitesse()[1] + (0.5/p.getMasse())*(*it).getY()*dt)*dt);
            z = (p.getPosition()[2] + (p.getVitesse()[2] + (0.5/p.getMasse())*(*it).getZ()*dt)*dt);
            Vecteur v = Vecteur (x,y,z);
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
}

std::vector<Vecteur> Univers::calcul_forces(float epsilon, float sigma){
    std::vector<Vecteur> forces;
    //std::vector<Vecteur> voisins;
    Vecteur r;
    float propx;
    float propy;
    float propz;
    float sumr;
    for(int i = 0 ; i<nbParticules; i++){
        Particule& p1= particules[i];
        Vecteur sommeForce_i = Vecteur(0,0,0);
        for(int j = 0 ; j<nbParticules; j++){
            Vecteur force_i_j= Vecteur(0,0,0);
            Particule& p2 = particules[j];
            if(p1.getId() != p2.getId() && est_voisine(p1,p2)){
                float dist = p1.calculateDistance(p2);
                r = p1.getPosition()-p2.getPosition();
                sumr = r.getX()+ r.getY()+ r.getZ();
                propx = r.getX()/sumr;
                propy = r.getY()/sumr;
                propz = r.getZ()/sumr;
                //if(dist>1e-5){ // je l'ai mis au tp2 car j'avais des nan quand la distance etait trop petite
                float force_scalaire = (1/pow(dist,2) * pow((sigma/dist),6)*(1-2*(pow((sigma/dist),6))))*24*epsilon;
                force_i_j = Vecteur(force_scalaire*propx, force_scalaire*propy, force_scalaire*propz);
                //}
            }
            sommeForce_i+=force_i_j;
        }
        forces.push_back(sommeForce_i);
    }
    return forces;
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