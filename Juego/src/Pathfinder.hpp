#ifndef Pathfinder_HPP
#define Pathfinder_HPP
#include <vector>
#include<bits/stdc++.h> 
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
        struct Enlace{
            Sala* desde;
            int estimatedTotalCost;
        };
        struct NodeRecord{
            Sala* nodo;
            struct Enlace conexion;
            int costSoFar;
            int estimatedTotalCost;
        } startNodo, actualNodo, endNodo;
        

        vector <struct NodeRecord> listaAbierta;
        vector <struct NodeRecord> listaCerrada;
        vector <struct NodeRecord> camino;
};
#endif
