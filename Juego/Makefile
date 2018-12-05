# Declaration of variables
CC_FLAGS = -w #comandos extras para el compilador
RUTACPP = src/ #variable donde iran las clases que utilizamos
# $(CXX) - Es la variable de entorno del compilador si estas con g++ o gcc te lo detecta solo+
CXXFLAGS = -g -Wall # lo que hace es que crea archivos debug para que se pueda comprobar la informacion
irrlicht =-I/usr/include/irrlicht #nos dice donde estan los includes
irrlichtN = -l Irrlicht #porque nombre llamarla
SHELL = /bin/bash
# ${CXXFLAGS} - Son las opciones del compilador
#pwd

# File names
EXEC = Ejecutable
BEGIN = Comienzo
SOURCES = $(wildcard src/*.cpp)
SOURCESHEADER = $(wildcard src/*.hpp)
#OSOURCES = $(wildcard obj/*.o) #se elimina por problemas de no refrescarse
OSOURCESV2 = $(shell ls obj/*.o)
OBJECTS = $(SOURCES:.cpp=.o)
RECUR = Recursiva
RECUR2 = Recursiva2
PRECA = Precaucion
BUSQ = $(shell find ./obj -name "*.o" | wc -l)
BUSQ2 = $(shell find ./src -name "*.o" | wc -l)

INCLUDE_DIRS = \
    -Ilibrerias/fmod/lowlevel/inc \
		-Ilibrerias/fmod/studio/inc

LOWLEVEL_LIB = librerias/fmod/lowlevel/lib/x86_64/libfmod.so
STUDIO_LIB = librerias/fmod/studio/lib/x86_64/libfmodstudio.so

# Aqui es donde se hace la magia y se unifican las clases en una sola, basicamente se le pasa las clases de objeto (.o) para unificarlas
$(BEGIN): $(PRECA) $(RECUR) $(OBJECTS) $(RECUR2) $(EXEC)
	#Finalizado Comprobaciones

$(EXEC): $(OSOURCESV2)
	#Comprobando ejecutable si esta actualizado
	$(CXX) $(OSOURCESV2) -pthread -o $(EXEC) $(irrlicht) $(irrlichtN) -Wl,-rpath=\$$ORIGIN/$(dir $(LOWLEVEL_LIB)) -Wl,-rpath=\$$ORIGIN/$(dir $(STUDIO_LIB)) $(INCLUDE_DIRS) $(STUDIO_LIB) $(LOWLEVEL_LIB)
	#Ejecutable Actualizado

$(PRECA):
	if [ $(BUSQ2) -gt 0 ] ; then mv src/*.o obj/ ; fi

$(RECUR):
	if [ $(BUSQ) -gt 0 ] ; then mv obj/*.o src/ ; fi

# si los cpp cambian los .o tambien cambiara (basicamente dice eso), luego si cambian los vuelve a crear
%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -pthread -o $@ $(irrlicht) $(irrlichtN) -Wl,-rpath=\$$ORIGIN/$(dir $(LOWLEVEL_LIB)) -Wl,-rpath=\$$ORIGIN/$(dir $(STUDIO_LIB)) $(INCLUDE_DIRS) $(STUDIO_LIB) $(LOWLEVEL_LIB)
	mv $@ obj/

$(RECUR2):
	 if [ $(BUSQ2) -gt 0 ] ; then mv src/*.o obj/ ; fi

#main: main.o MotorGrafico.o
#le decimos que clase depende de irrlicht
#obj/clase.o: $(irrlicht)

# Limpia los .o y el ejecutable creado, si se ponen archivos autogenerados deben ponerse aqui para que se quiten
clean:
	rm -f $(EXEC) $(OSOURCESV2)
	rm -f src/*.o
# si ejecutas "make run" despues de compilar ejecutara automaticamente el ejecutable
run: $(BEGIN)
	./$(EXEC)

val: $(BEGIN)
	#CUIDADO hay que tener val
	valgrind ./$(EXEC)
