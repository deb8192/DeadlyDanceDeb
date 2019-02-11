# Declaration of variables
CC_FLAGS = -w #comandos extras para el compilador
RUTACPP = src/ #variable donde iran las clases que utilizamos
# $(CXX) - Es la variable de entorno del compilador si estas con g++ o gcc te lo detecta solo+
CXXFLAGS = -g -Wall # lo que hace es que crea archivos debug para que se pueda comprobar la informacion
CABECERAS =-I"../glew/inc/" -I"../glad/inc/" -I"../glfw/inc/" -I"../stb_image/inc/" -I"../glm/" #nos dice donde estan los includes
LIBRERIAS =-L"../glew/lib/" -L"../glad/lib/" -L"../glfw/lib/" #nos dice donde estan las librerias
LIBRERIAS_ESPECIFICAS = ../glew/lib/libGLEW.a ../glad/lib/libglad.a ../glfw/lib/libglfw3.a #librerias necesarias
irrlichtN =  -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor -lGL -lIrrlicht   #porque nombre llamarla
SHELL = /bin/bash
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

BUSQ = $(shell find ./obj -name "*.o" | wc -l)

BUSQ2 = $(shell find ./src -name "*.o" | wc -l)

# Aqui es donde se hace la magia y se unifican las clases en una sola, basicamente se le pasa las clases de objeto (.o) para unificarlas
$(BEGIN):
	make libreria

$(PRECA):
	if [ $(BUSQ2) -gt 0 ] ; then mv src/*.o obj/ ; fi

$(RECUR):
	if [ $(BUSQ) -gt 0 ] ; then mv obj/*.o src/ ; fi

# si los cpp cambian los .o tambien cambiara (basicamente dice eso), luego si cambian los vuelve a crear

%.o: %.cpp %.hpp #para las clases normales
	#Compilacion objeto con cabecera
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(CABECERAS)
	#mv $@ obj/

%.o: %.cpp #esto es para el main sobretodo
	#Compilacion objeto sin cabecera
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(CABECERAS)
	#mv $@ obj/

$(RECUR2):
	 if [ $(BUSQ2) -gt 0 ] ; then mv src/*.o obj/ ; fi

# Limpia los .o y el ejecutable creado, si se ponen archivos autogenerados deben ponerse aqui para que se quiten
clean:
	rm -f src/*.o
	rm -f obj/*.o

libreria: $(RECUR) $(OBJECTS) $(PRECA)
	#vamos a construir la libreria
	ar -rv lib/libcatopengl.a $(OSOURCESV2)
	#copiamos cabeceras en inc
	cp src/*.hpp inc 