#include"affichage.hxx"
#include<iostream>
#include<fstream>

// classe qui permet de créer les fichier .vtk nécessaires à la visualisation sur Paraview

Affichage::Affichage(Univers u): u(u){};

void Affichage::create_vtk(std::string filepath){
    std::ofstream fichier(filepath, std::ios::out | std::ios::trunc);

    if(!fichier.is_open()){
        std::cerr << "Impossible d'ouvrir le fichier" << filepath << std::endl;
        return;
    }

    fichier << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">" << std::endl;

    fichier << "\t\"<UnstructuredGrid>\"" << std::endl;
    fichier <<  "\t\t <Piece NumberOfPoints=\"" << u.getNbParticules() << "\" NumberOfCells=\"" << u.getCellules().size() <<"\">" << std::endl;
    fichier << "\t\t\t<Points>" << std::endl;
    fichier << "\t\t\t\t<DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"2\" format=\"ascii\">" << std::endl;
    fichier << "\t\t\t\t\t";
    for(int i=0; i<u.getNbParticules() ; i++){
        Particule& p = u.get_particules()[i];
        fichier << p.getPosition().getX() << " " << p.getPosition().getY() << " ";
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;
    fichier << "\t\t\t</Points>" << std::endl;
    fichier << "\t\t\t<PointData Vectors=\"vector\">" << std::endl;
    fichier << "\t\t\t\t<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;
    fichier << "\t\t\t\t\t";
    for(int i=0; i<u.getNbParticules() ; i++){
        Particule& p = u.get_particules()[i];
        fichier << p.getVitesse().getX() << " " << p.getVitesse().getY() << " ";
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;
    fichier << "\t\t\t\t<DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">" << std::endl;
    fichier << "\t\t\t\t\t";
    for(int i=0; i<u.getNbParticules() ; i++){
        Particule& p = u.get_particules()[i];
        fichier << p.getMasse() << " " ;
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;
    fichier << "\t\t\t</PointData>" << std::endl;
    fichier << "\t\t\t<Cells>" << std::endl;
    fichier << "\t\t\t\t<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << std::endl;
    for(int i = 0 ; i<=4*u.getCellules().size(); i++){
        fichier << i << " ";
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;
    fichier << "\t\t\t\t<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">" << std::endl;
    for(int i = 1 ; i<=u.getCellules().size(); i++){
        fichier << 4*i << " ";
    }
    fichier << "\t\t\t\t</DataArray>" << std::endl;
    fichier << "\t\t\t\t<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">" << std::endl;
    fichier << 9 << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;
    fichier << "\t\t\t</Cells>" << std::endl;
    fichier << "\t\t</Piece>" << std::endl;
    fichier << "\t</UnstructuredGrid>" << std::endl;
    fichier << "</VTKFile>" << std::endl;


    fichier.close();
}    
