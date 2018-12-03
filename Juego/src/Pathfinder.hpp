#ifndef Pathfinder_HPP
#define Pathfinder_HPP
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <cmath>
#include<bits/stdc++.h> 
#include "Nivel.hpp"
#include "Sala.hpp"

using namespace std;

class Pathfinder
{
    public:
        struct NodeRecord;
        int comprobarListas(Sala*, vector <struct NodeRecord> lista);
        int  calcularCostes(struct NodeRecord, Sala*);
        bool coincide(Sala*, Sala*);
        vector <struct NodeRecord> encontrarCamino(Sala*, Sala*);
        void getSmallest();
    private:
        struct NodeRecord{
            Sala* nodo;
            struct NodeRecord *conexion;
            int costSoFar;
            int estimatedTotalCost;
        } startNodo, actualNodo, endNodo;

        vector <struct NodeRecord> listaAbierta;
        vector <struct NodeRecord> listaCerrada;
        vector <struct NodeRecord> camino;
        vector <struct NodeRecord> conexiones;
};
#endif
