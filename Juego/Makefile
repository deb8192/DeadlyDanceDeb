# Declaration of variables
CC_FLAGS = -w #comandos extras para el compilador
RUTACPP = src/ #variable donde iran las clases que utilizamos
# $(CXX) - Es la variable de entorno del compilador si estas con g++ o gcc te lo detecta solo+
CXXFLAGS = -g -Wall # lo que hace es que crea archivos debug para que se pueda comprobar la informacion
irrlicht =-I/usr/include/irrlicht #nos dice donde estan los includes
irrlichtN = -l Irrlicht #porque nombre llamarla

# ${CXXFLAGS} - Son las opciones del compilador
#pwd

# File names
EXEC = Ejecutable
SOURCES = $(wildcard src/*.cpp)
SOURCESHEADER = $(wildcard src/*.hpp)
OSOURCES = $(wildcard obj/*.o)
OBJECTS = $(SOURCES:.cpp=.o)

# direcorio de librerias de fmod
INCLUDE_DIRS = \
    -Ifmod/lowlevel/inc \
    -Ifmod/studio/inc

LOWLEVEL_LIB = -Ifmod/lowlevel/lib/x86_64/libfmod.so
STUDIO_LIB = -Ifmod/studio/lib/x86_64/libfmodstudio.so

# Aqui es donde se hace la magia y se unifican las clases en una sola, basicamente se le pasa las clases de objeto (.o) para unificarlas
$(EXEC): $(OBJECTS)
	$(CXX) $(OSOURCES) -o $(EXEC) $(irrlicht) $(irrlichtN) $(LOWLEVEL_LIB) $(STUDIO_LIB) $(INCLUDE_DIRS)

# si los cpp cambian los .o tambien cambiara (basicamente dice eso), luego si cambian los vuelve a crear
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(irrlicht) $(irrlichtN) $(LOWLEVEL_LIB) $(STUDIO_LIB) $(INCLUDE_DIRS)
	mv src/*.o obj/

#main: main.o MotorGrafico.o
#le decimos que clase depende de irrlicht
#obj/clase.o: $(irrlicht)

# Limpia los .o y el ejecutable creado, si se ponen archivos autogenerados deben ponerse aqui para que se quiten
clean:
	rm -f $(EXEC) $(OSOURCES)
# si ejecutas "make run" despues de compilar ejecutara automaticamente el ejecutable
run: $(EXEC)
	./$(EXEC)
