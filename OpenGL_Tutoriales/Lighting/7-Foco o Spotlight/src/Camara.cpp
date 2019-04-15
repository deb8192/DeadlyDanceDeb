#include "Camara.hpp"

// Constructor con vectores
Camara::Camara(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
    Position = position;
    WorldUp = up;
    Front = glm::vec3(0.0f, 0.0f, -1.0f);

    Yaw = yaw;
    Pitch = pitch;
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Zoom = ZOOM;

    updateCameraVectors();
}
// Constructor con valores escalares
Camara::Camara(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Front = glm::vec3(0.0f, 0.0f, -1.0f);

    Yaw = yaw;
    Pitch = pitch;
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Zoom = ZOOM;

    updateCameraVectors();
}

// Devuelve la matriz de vista calculada usando los angulos de Euler con lookAt
glm::mat4 Camara::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

// Procesa el input recibido desde el teclado
void Camara::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

// Procesa el input recibido desde el raton
void Camara::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    // Asegúrese de que cuando el Pitch está fuera de los límites, la pantalla no se gire.
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // Update de los vectores Front, Right y Up
    updateCameraVectors();
}

// Procesa el input recibido desde la la rueda del raton
void Camara::ProcessMouseScroll(float yoffset)
{
    if (Zoom >= 1.0f && Zoom <= 90.0f)
        Zoom -= yoffset;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 90.0f)
        Zoom = 90.0f;
}

// Calcula el vector frontal desde la camara
void Camara::updateCameraVectors()
{
    // Calcula el nuevo vector frontal
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // Ademas de calcular el right y el up
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalizar los vectores, porque su longitud se acerca a 0 cuanto más se mira hacia arriba o hacia abajo, lo que resulta en un movimiento más lento.
    Up    = glm::normalize(glm::cross(Right, Front));
}
