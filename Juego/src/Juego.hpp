//#include "MotorGrafico.hpp"
#include "MotorAudio.hpp"
#include "Estado.hpp"
#include "Jugando/Nivel.hpp"
#include "CargadorBehaviorTrees.hpp" //prueba
#include "CargadorXML.hpp"
#include "Times.hpp"

#ifndef Juego_HPP
#define Juego_CPP

    class Juego
    {
        public:

            //singleton public
            ~Juego(void);
            static Juego* getInstance() //esto se utiliza para crear el objeto una sola vez
            {
                if(_unica_instancia == 0)
                _unica_instancia = new Juego();
                return _unica_instancia;
            }
            //fin singleton public

            bool Running();//te devuelve true si esta en funcionamiento la ventana del juego, te devuelve false si se ha cerrado la ventana
            void InicializarVentana();//te inicializa la ventana en la que se va a mostrar el juego
            void Draw(); //actualiza renderizados
            void Update(); //actualiza logica
            void UpdateIA(); //ejecuta la ia
            void LimpiarVentana();//borra de la memoria la ventana del juego.
            void Salir();//sale del juego
            void Jugar();//cambia de estado y cargar mapa //aqui saldra el selector de nivel cuando se implemente
            void setNivelThen();
            void cambiarEstadoMenu();//cambia al estado menu
            void CargarArbolesXML();
            void CargarPuzzlesXML();

        private:

            //clase singleton
            Juego();
            static Juego* _unica_instancia;
            //fin clase singleton private
            Estado*  estado;//puntero del estado
            MotorGrafico* _motor;//instancia de la fachada
            MotorAudioSystem* _motora;//instancia de la fachada audio
            Cinematica cinematica;//contiene la clase cinematica (estado)
            Menu menu;//contiene la clase menu (estado)
            Jugando jugando;//contiene la clase Jugando (estado)
            Nivel* nivel;
            
            // Probando puzzles
            Puzzles haciendo_puzzles;//contiene la clase Puzzles (estado)
            CargadorXML cargadorXML;

            //cinematicas
            float tiempoTotal = 18000.0f;//esto indica el tiempo de las cinematicas total en segundos
            float marcaTiempo = 0;//llamaremos a getiempo cuando se inicialice la ventana luego simplemente comprobamos que el tiempo sea mayor que el total para cambiar a menu
    };

#endif /* MotorGrafico_HPP */
