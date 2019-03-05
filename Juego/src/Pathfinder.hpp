#ifndef Pathfinder_HPP
#define Pathfinder_HPP
#include <vector>
#include<bits/stdc++.h> 
#include "Jugando/Sala.hpp"

using namespace std;


        
class Pathfinder
{
    public:
        ~Pathfinder(void);
        static Pathfinder *getInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(unica_instancia == 0)
            unica_instancia = new Pathfinder();
            return unica_instancia;
        }
        struct NodeRecord;
        int comprobarListas(Sala*, vector <struct NodeRecord> lista);
        int  calcularCostes(struct NodeRecord, Sala*);
        bool coincide(Sala*, Sala*);
        vector <Waypoint*> encontrarCamino(Sala*, Sala*);
        void getSmallest();
    private:
        //clase singleton
        Pathfinder();
        static Pathfinder* unica_instancia;
        //fin clase singleton
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
        
        int contador;
        vector <struct NodeRecord> listaAbierta;
        vector <struct NodeRecord> listaCerrada;
        vector <struct NodeRecord> camino;
        vector <Waypoint*> waypointsRecorridos;
};
#endif
