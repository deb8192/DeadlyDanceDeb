# Declaration of variables
CC_FLAGS = -w #comandos extras para el compilador
RUTACPP = src/ #variable donde iran las clases que utilizamos
# $(CXX) - Es la variable de entorno del compilador si estas con g++ o gcc te lo detecta solo+
CXXFLAGS = -g -Wall # lo que hace es que crea archivos debug para que se pueda comprobar la informacion
CABECERAS =-I"/usr/include/irrlicht" -I"librerias/fmod/lowlevel/inc/" -I"librerias/fmod/studio/inc/" -I"librerias/reactphysics3d/src/" -I"librerias/glew/inc/" -I"librerias/glad/inc/" -I"librerias/glfw/inc/" -I"librerias/stb_image/inc/" -I"librerias/glm/" -I"librerias/assimp/inc/" -I"librerias/catopengl/inc/" #nos dice donde estan los includes
LIBRERIAS =-L"librerias/reactphysics3d/lib/" -L"librerimmas/fmod/lowlevel/lib/x86_64/" -L"librerias/fmod/studio/lib/x86_64/" -L"librerias/glew/lib/" -L"librerias/glad/lib/" -L"librerias/glfw/lib/" -L"librerias/assimp/lib/" -L"librerias/catopengl/lib/" #nos dice donde estan las librerias
LIBRERIAS_CARPETAS = "librerias/fmod/lowlevel/lib/x86_64/:librerias/fmod/studio/lib/x86_64/:librerias/irrlicht/:librerias/reactphysics3d/lib:librerias/glew/lib:librerias/glad/lib:librerias/glfw/lib:librerias/assimp/lib:librerias/catopengl/lib"
LIBRERIAS_ESPECIFICAS = librerias/fmod/studio/lib/x86_64/libfmodstudio.so librerias/fmod/lowlevel/lib/x86_64/libfmod.so librerias/reactphysics3d/lib/libreactphysics3d.a librerias/glew/lib/libGLEW.a librerias/glad/lib/libglad.a librerias/glfw/lib/libglfw3.a librerias/assimp/lib/libIrrXML.a librerias/catopengl/lib/libcatopengl.a #librerias necesarias
irrlichtN =  -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor -lGL -lIrrlicht -lassimp   #porque nombre llamarla
libSeguimiento = $(shell ls librerias/catopengl/obj/*.o)
SHELL = /bin/bash
CPUCOUNT=$(shell grep -c   "^processor" /proc/cpuinfo)
# ${CXXFLAGS} - Son las opciones del compilador
#pwd

# File names
EXEC = Ejecutable
BEGIN = Comienzo

SOURCES = $(shell ls src/*.cpp)
SOURCESM = $(shell ls src/Menus/*.cpp)
SOURCESP = $(shell ls src/Personajes/*.cpp)
SOURCESE = $(shell ls src/Enemigos/*.cpp)
SOURCESJ = $(shell ls src/Jugando/*.cpp)
SOURCESPU = $(shell ls src/Puzzles/*.cpp)
SOURCESO = $(shell ls src/Objetos/*.cpp)
SOURCESA = $(shell ls src/Armas/*.cpp)
SOURCESMO = $(shell ls src/Motores/*.cpp)

SOURCESHEADER = $(shell ls src/*.hpp)
SOURCESHEADERM = $(shell ls src/Menus/*.hpp)
SOURCESHEADERP = $(shell ls src/Personajes/*.hpp)
SOURCESHEADERE = $(shell ls src/Enemigos/*.hpp)
SOURCESHEADERJ = $(shell ls src/Jugando/*.hpp)
SOURCESHEADERPU = $(shell ls src/Puzzles/*.hpp)
SOURCESHEADERO = $(shell ls src/Objetos/*.hpp)
SOURCESHEADERA = $(shell ls src/Armas/*.hpp)
SOURCESHEADERMO = $(shell ls src/Motores/*.hpp)

#OSOURCES = $(wildcard obj/*.o) #se elimina por problemas de no refrescarse

OSOURCESV2 = $(shell ls obj/*.o)
OSOURCESMV2 = $(shell ls obj/Menus/*.o)
OSOURCESPV2 = $(shell ls obj/Personajes/*.o)
OSOURCESEV2 = $(shell ls obj/Enemigos/*.o)
OSOURCESJV2 = $(shell ls obj/Jugando/*.o)
OSOURCESPU2 = $(shell ls obj/Puzzles/*.o)
OSOURCESO2 = $(shell ls obj/Objetos/*.o)
OSOURCESA2 = $(shell ls obj/Armas/*.o)
OSOURCESMO2 = $(shell ls obj/Motores/*.o)

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTSM = $(SOURCESM:.cpp=.o)
OBJECTSP = $(SOURCESP:.cpp=.o)
OBJECTSE = $(SOURCESE:.cpp=.o)
OBJECTSJ = $(SOURCESJ:.cpp=.o)
OBJECTSPU = $(SOURCESPU:.cpp=.o)
OBJECTSO = $(SOURCESO:.cpp=.o)
OBJECTSA = $(SOURCESA:.cpp=.o)
OBJECTSMO = $(SOURCESMO:.cpp=.o)

RECUR = Recursiva
RECUR2 = Recursiva2
PRECA = Precaucion
LG = LIBRERIAGRAFICA
PARALLEL = Paralelo
BUSQ = $(shell find ./obj  -maxdepth 1 -name "*.o" | wc -l)
BUSQM = $(shell find ./obj/Menus  -maxdepth 1 -name "*.o" | wc -l)
BUSQP = $(shell find ./obj/Personajes  -maxdepth 1 -name "*.o" | wc -l)
BUSQE = $(shell find ./obj/Enemigos  -maxdepth 1 -name "*.o" | wc -l)
BUSQJ = $(shell find ./obj/Jugando  -maxdepth 1 -name "*.o" | wc -l)
BUSQPU = $(shell find ./obj/Puzzles  -maxdepth 1 -name "*.o" | wc -l)
BUSQO = $(shell find ./obj/Objetos  -maxdepth 1 -name "*.o" | wc -l)
BUSQA = $(shell find ./obj/Armas  -maxdepth 1 -name "*.o" | wc -l)
BUSQMO = $(shell find ./obj/Motores  -maxdepth 1 -name "*.o" | wc -l)

BUSQ2 = $(shell find ./src  -maxdepth 1 -name "*.o" | wc -l)
BUSQ2M = $(shell find ./src/Menus  -maxdepth 1 -name "*.o" | wc -l)
BUSQ2P = $(shell find ./src/Personajes  -maxdepth 1 -name "*.o" | wc -l)
BUSQ2E = $(shell find ./src/Enemigos  -maxdepth 1 -name "*.o" | wc -l)
BUSQ2J = $(shell find ./src/Jugando  -maxdepth 1 -name "*.o" | wc -l)
BUSQ2PU = $(shell find ./src/Puzzles  -maxdepth 1 -name "*.o" | wc -l)
BUSQ2O = $(shell find ./src/Objetos  -maxdepth 1 -name "*.o" | wc -l)
BUSQ2A = $(shell find ./src/Armas  -maxdepth 1 -name "*.o" | wc -l)
BUSQ2MO = $(shell find ./src/Motores  -maxdepth 1 -name "*.o" | wc -l)

# Aqui es donde se hace la magia y se unifican las clases en una sola, basicamente se le pasa las clases de objeto (.o) para unificarlas
$(BEGIN): 
	@echo -e '\e[45m Paso 1 Revision Libreria Grafica \e[0m';
	$(MAKE) $(LG)
	@echo -e '\e[45m Paso 2 Precuaciones \e[0m';
	$(MAKE) $(PRECA)
	$(MAKE) $(RECUR)
	@echo -e '\e[45m Paso 3 Creando Objetos (con $(CPUCOUNT) hilos) \e[0m';
	$(MAKE) -j$(CPUCOUNT) $(PARALLEL) 
	@echo -e '\e[45m Paso 4  \e[0m';
	$(MAKE) $(RECUR2)
	@echo -e '\e[45m Paso 5 Creacion de Ejecutable \e[0m';
	$(MAKE) $(EXEC)
	@echo -e '\e[45m Finalizado Ejecucion Makefile \e[0m';

$(PARALLEL): $(OBJECTS) $(OBJECTSP) $(OBJECTSE) $(OBJECTSM) $(OBJECTSJ) $(OBJECTSPU) $(OBJECTSO) $(OBJECTSA) $(OBJECTSMO) |

#Finalizado Comprobaciones

$(EXEC): $(OSOURCESV2) $(OSOURCESMV2) $(OSOURCESPV2) $(OSOURCESEV2) $(OSOURCESJV2) $(OSOURCESPU2) $(OSOURCESO2) $(OSOURCESA2) $(OSOURCESMO2) $(libSeguimiento)
	#Comprobando ejecutable si esta actualizado
	$(CXX) $(OSOURCESV2) $(OSOURCESMV2) $(OSOURCESPV2) $(OSOURCESEV2) $(OSOURCESJV2) $(OSOURCESPU2) $(OSOURCESO2) $(OSOURCESA2) $(OSOURCESMO2) $(irrlichtN) $(LIBRERIAS) $(LIBRERIAS_ESPECIFICAS)  -o $(EXEC)
	#Ejecutable Actualizado

$(PRECA):
	if [ $(BUSQ2) -gt 0 ] ; then mv src/*.o obj/ ; fi
	if [ $(BUSQ2M) -gt 0 ] ; then mv src/Menus/*.o obj/Menus/ ; fi
	if [ $(BUSQ2P) -gt 0 ] ; then mv src/Personajes/*.o obj/Personajes/ ; fi
	if [ $(BUSQ2E) -gt 0 ] ; then mv src/Enemigos/*.o obj/Enemigos/ ; fi
	if [ $(BUSQ2J) -gt 0 ] ; then mv src/Jugando/*.o obj/Jugando/ ; fi
	if [ $(BUSQ2PU) -gt 0 ] ; then mv src/Puzzles/*.o obj/Puzzles/ ; fi
	if [ $(BUSQ2O) -gt 0 ] ; then mv src/Objetos/*.o obj/Objetos/ ; fi
	if [ $(BUSQ2A) -gt 0 ] ; then mv src/Armas/*.o obj/Armas/ ; fi
	if [ $(BUSQ2MO) -gt 0 ] ; then mv src/Motores/*.o obj/Motores/ ; fi

$(RECUR):
	if [ $(BUSQ) -gt 0 ] ; then mv obj/*.o src/ ; fi
	if [ $(BUSQM) -gt 0 ] ; then mv obj/Menus/*.o src/Menus/ ; fi
	if [ $(BUSQP) -gt 0 ] ; then mv obj/Personajes/*.o src/Personajes/ ; fi
	if [ $(BUSQE) -gt 0 ] ; then mv obj/Enemigos/*.o src/Enemigos/ ; fi
	if [ $(BUSQJ) -gt 0 ] ; then mv obj/Jugando/*.o src/Jugando/ ; fi
	if [ $(BUSQPU) -gt 0 ] ; then mv obj/Puzzles/*.o src/Puzzles/ ; fi
	if [ $(BUSQO) -gt 0 ] ; then mv obj/Objetos/*.o src/Objetos/ ; fi
	if [ $(BUSQA) -gt 0 ] ; then mv obj/Armas/*.o src/Armas/ ; fi
	if [ $(BUSQMO) -gt 0 ] ; then mv obj/Motores/*.o src/Motores/ ; fi

# si los cpp cambian los .o tambien cambiara (basicamente dice eso), luego si cambian los vuelve a crear

%.o: %.cpp %.hpp #para las clases normales
	#Compilacion objeto con cabecera
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(CABECERAS)

%.o: %.cpp #esto es para el main sobretodo
	#Compilacion objeto sin cabecera
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(CABECERAS)

$(RECUR2):
	 if [ $(BUSQ2) -gt 0 ] ; then mv src/*.o obj/ ; fi
	 if [ $(BUSQ2M) -gt 0 ] ; then mv src/Menus/*.o obj/Menus/ ; fi
	 if [ $(BUSQ2P) -gt 0 ] ; then mv src/Personajes/*.o obj/Personajes/ ; fi
	 if [ $(BUSQ2E) -gt 0 ] ; then mv src/Enemigos/*.o obj/Enemigos/ ; fi
	 if [ $(BUSQ2J) -gt 0 ] ; then mv src/Jugando/*.o obj/Jugando/ ; fi
	 if [ $(BUSQ2PU) -gt 0 ] ; then mv src/Puzzles/*.o obj/Puzzles/ ; fi
	 if [ $(BUSQ2O) -gt 0 ] ; then mv src/Objetos/*.o obj/Objetos/ ; fi
	 if [ $(BUSQ2A) -gt 0 ] ; then mv src/Armas/*.o obj/Armas/ ; fi
	 if [ $(BUSQ2MO) -gt 0 ] ; then mv src/Motores/*.o obj/Motores/ ; fi

$(LG):
	@echo -e '\e[45m Iniciando Compilacion Libreria Grafica \e[0m'; \
	cd librerias/catopengl/; make; \
	echo -e '\e[45m Compilacion Libreria Grafica Correcta :) \e[0m'; \

#main: main.o MotorGrafico.o
#le decimos que clase depende de irrlicht
#obj/clase.o: $(irrlicht)

# Limpia los .o y el ejecutable creado, si se ponen archivos autogenerados deben ponerse aqui para que se quiten
clean:
	rm -f $(EXEC) $(OSOURCESV2) $(OSOURCESPV2) $(OSOURCESEV2) $(OSOURCESJV2) $(OSOURCESMV2) $(OSOURCESPU2) $(OSOURCESO2) $(OSOURCESA2) $(OSOURCESMO2)
	rm -f src/*.o
	cd librerias/catopengl/; make clean; \
	
# si ejecutas "make run" despues de compilar ejecutara automaticamente el ejecutable
run: $(BEGIN)
	#ADVERTENCIA: las librerias exportadas solo sirven para esta ejecucion si quiere que esten hay durante la sesion debe ejecuta el comando manualmente desde una consola propia
	export LD_LIBRARY_PATH="$(LIBRERIAS_CARPETAS)";\
	./$(EXEC)

val: $(BEGIN)
	#CUIDADO hay que tener valgrind para instalarlo "sudo pacman -S valgrind"
	#ADVERTENCIA: las librerias exportadas solo sirven para esta ejecucion si quiere que esten hay durante la sesion debe ejecuta el comando manualmente desde una consola propia
	export LD_LIBRARY_PATH="$(LIBRERIAS_CARPETAS)";\
	valgrind --error-limit=no ./$(EXEC)
		
