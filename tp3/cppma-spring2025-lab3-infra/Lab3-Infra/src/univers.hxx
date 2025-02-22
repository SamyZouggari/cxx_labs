#pragma once

#include"particule.hxx"

class Univers {
    public:
    int nbParticules;
    Particule* particules;
    Univers(int nbParticules, float deb, float fin);
    Univers(const Univers & u);
};