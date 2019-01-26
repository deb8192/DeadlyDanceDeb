#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Define varias opciones posibles para el movimiento de la cámara. Utilizado como abstracción para mantenerse alejado de
// los métodos de entrada específicos del sistema de ventanas
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Valores de la camara por defecto
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camara
{
    public:
        // Atributos de la camara
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // Angulos de Euler
        float Yaw;
        float Pitch;
        // Opciones de Camara
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        //Constructor con vectores
        Camara(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
        //Constructor con valores escalares
        Camara(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
        //Desctructor
        ~Camara();

        // Devuelve la matriz de vista calculada usando los angulos de Euler con lookAt
        glm::mat4 GetViewMatrix();

        // Procesa el input recibido desde el teclado
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        // Procesa el input recibido desde el raton
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

        // Procesa el input recibido desde la la rueda del raton
        void ProcessMouseScroll(float yoffset);

    private:
        // Calcula el vector frontal desde la camara
        void updateCameraVectors();
};

#endif
