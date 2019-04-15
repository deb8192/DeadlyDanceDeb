# Declaration of variables
CC_FLAGS = -w #comandos extras para el compilador
RUTACPP = src/ #variable donde iran las clases que utilizamos
# $(CXX) - Es la variable de entorno del compilador si estas con g++ o gcc te lo detecta solo+
CXXFLAGS = -g -Wall # lo que hace es que crea archivos debug para que se pueda comprobar la informacion   librerias/freetype/inc/ft2build.h
CABECERAS =-I"../glew/inc/" -I"../glad/inc/" -I"../glfw/inc/" -I"../stb_image/inc/" -I"../glm/" -I"../assimp/inc/" -I"../freetype/inc/" #nos dice donde estan los includes
LIBRERIAS =-L"../glew/lib/" -L"../glad/lib/" -L"../glfw/lib/" -L"../assimp/lib/" -L"../freetype/lib/" #nos dice donde estan las librerias
LIBRERIAS_ESPECIFICAS = ../glew/lib/libGLEW.a ../glad/lib/libglad.a ../glfw/lib/libglfw3.a ../assimp/lib/libIrrXML.a  ../freetype/lib/libfreetype.a#librerias necesarias
irrlichtN =  -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor -lGL -lIrrlicht -lfreetype #porque nombre llamarla
SHELL = /bin/bash
CPUCOUNT=$(shell grep -c "^processor" /proc/cpuinfo)
# ${CXXFLAGS} - Son las opciones del compilador
#pwd

# File names
EXEC = Ejecutable
BEGIN = Comienzo

SOURCES = $(shell ls src/*.cpp)

SOURCESHEADER = $(shell ls src/*.hpp)

OSOURCESV2 = $(shell ls obj/*.o)

OBJECTS = $(SOURCES:.cpp=.o)

RECUR = Recursiva
RECUR2 = Recursiva2
PRECA = Precaucion
PARAL = Paralelo
LIB = Lib

BUSQ = $(shell find ./obj -name "*.o" | wc -l)

BUSQ2 = $(shell find ./src -name "*.o" | wc -l)

# Aqui es donde se hace la magia y se unifican las clases en una sola, basicamente se le pasa las clases de objeto (.o) para unificarlas
$(BEGIN):
	make libreria

$(PRECA):
	if [ $(BUSQ2) -gt 0 ] ; then mv src/*.o obj/ ; ls obj/*.o ; fi

$(RECUR):
	if [ $(BUSQ) -gt 0 ] ; then mv obj/*.o src/ ; fi

$(PARAL): $(OBJECTS) |

$(LIB):
	#vamos a construir la libreria
	ar -rv lib/libcatopengl.a $(OSOURCESV2)
	#copiamos cabeceras en inc
	cp src/*.hpp inc

# si los cpp cambian los .o tambien cambiara (basicamente dice eso), luego si cambian los vuelve a crear

%.o: %.cpp %.hpp #para las clases normales
	#Compilacion objeto con cabecera
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(CABECERAS)

%.o: %.cpp #esto es para el main sobretodo
	#Compilacion objeto sin cabecera
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(CABECERAS)

$(RECUR2):
	 if [ $(BUSQ2) -gt 0 ] ; then mv src/*.o obj/ ; fi

# Limpia los .o y el ejecutable creado, si se ponen archivos autogenerados deben ponerse aqui para que se quiten
clean:
	@echo Limpiando objetos de libreria grafica
	rm -f src/*.o
	rm -f obj/*.o
	rm -f lib/*

libreria:

	@echo -e '\e[41m Paso 1 Recuperacion de objetos \e[0m';
	$(MAKE) $(RECUR)
	@echo -e '\e[41m Paso 2 Compilacion de objetos \e[0m';
	$(MAKE) -j$(CPUCOUNT) $(PARAL)
	@echo -e '\e[41m Paso 3 Reestructurar \e[0m';
	$(MAKE) $(PRECA)
	@echo -e '\e[41m Paso 3 Construyendo libreria \e[0m';
	$(MAKE) $(LIB)
