#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

/// <summary>
///  Kierunki kamery.
/// </summary>
enum Camera_Movement {
	FORWARD, BACKWARD, LEFT, RIGHT
};

class Camera
{
private:
	glm::vec3 position; // Pozycja kamery.
	glm::vec3 front;    // Prz�d Kamery.
	glm::vec3 up;       // G�ra kamery.
	glm::vec3 right;    // Prawa strona kamery.
	glm::vec3 worldUp;  // Wektor g�ry wed�ug �wiata.

	GLfloat yaw;	// Y axis - Odchylenie - Eulerowiskie k�ty.
	GLfloat pitch;  // X axis - Pochylenie - Eulerowskie k�ty.

	GLfloat movementSpeed;    // Szybko�� poruszania si�.
	GLfloat mouseSensitivity; // Czu�o�� myszki.
	GLfloat zoom;			  // Przybli�enie.

public:
	/// <summary>
	/// Konstruktor podstawowy oraz niestandardowy.
	/// </summary>
	/// <param name="position"> Pozycja kamery. </param>
	/// <param name="up"> Wektor wskazujace gore wzgl�dem �wiata. </param>
	/// <param name="yaw"> Odchylenie wzgl�dem osi Y. </param>
	/// <param name="pitch"> Pochylenie wzgl�dem osi X.</param>
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);

	/// <summary>
	/// Uzyskaj macierz widoku kamery.
	/// </summary>
	/// <returns></returns>
	glm::mat4 getViewMatrix();

	/// <summary>
	/// Uzyskaj macierz widoku kamery, kt�ra zosta�a stworzona niestandardowo.
	/// </summary>
	/// <returns></returns>
	glm::mat4 getViewMatrix_CUSTOM();

	/// <summary>
	/// Obs�u� kamer� - ruch u�ywaj�c przycisk�w klawiatury.
	/// </summary>
	/// <param name="direction"> Kierunek.</param>
	/// <param name="deltaTime">Ilo�� czasu up�yni�tego pomi�dzy ostatni� klatk�.</param>
	void processKeyboard(Camera_Movement direction, float deltaTime);

	/// <summary>
	/// Obs�u� kamer� - obracanie czyli dodawanie odpowiednich warto�ci do kat�w: nachylenia (pitch) oraz odchylenia (yaw).
	/// </summary>
	/// <param name="xOffset"></param>
	/// <param name="yOffset"></param>
	/// <param name="constainPitch"></param>
	void processMouseMovement(float xOffset, float yOffset, GLboolean constainPitch = true);

private:
	/// <summary>
	/// Aktualizuj parametry kamery.
	/// </summary>
	void updateCameraVectors();
};

