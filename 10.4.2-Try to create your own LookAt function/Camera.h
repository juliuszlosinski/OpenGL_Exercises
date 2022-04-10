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
	glm::vec3 front;    // Przód Kamery.
	glm::vec3 up;       // Góra kamery.
	glm::vec3 right;    // Prawa strona kamery.
	glm::vec3 worldUp;  // Wektor góry wed³ug œwiata.

	GLfloat yaw;	// Y axis - Odchylenie - Eulerowiskie k¹ty.
	GLfloat pitch;  // X axis - Pochylenie - Eulerowskie k¹ty.

	GLfloat movementSpeed;    // Szybkoœæ poruszania siê.
	GLfloat mouseSensitivity; // Czu³oœæ myszki.
	GLfloat zoom;			  // Przybli¿enie.

public:
	/// <summary>
	/// Konstruktor podstawowy oraz niestandardowy.
	/// </summary>
	/// <param name="position"> Pozycja kamery. </param>
	/// <param name="up"> Wektor wskazujace gore wzglêdem œwiata. </param>
	/// <param name="yaw"> Odchylenie wzglêdem osi Y. </param>
	/// <param name="pitch"> Pochylenie wzglêdem osi X.</param>
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);

	/// <summary>
	/// Uzyskaj macierz widoku kamery.
	/// </summary>
	/// <returns></returns>
	glm::mat4 getViewMatrix();

	/// <summary>
	/// Uzyskaj macierz widoku kamery, która zosta³a stworzona niestandardowo.
	/// </summary>
	/// <returns></returns>
	glm::mat4 getViewMatrix_CUSTOM();

	/// <summary>
	/// Obs³u¿ kamerê - ruch u¿ywaj¹c przycisków klawiatury.
	/// </summary>
	/// <param name="direction"> Kierunek.</param>
	/// <param name="deltaTime">Iloœæ czasu up³yniêtego pomiêdzy ostatni¹ klatk¹.</param>
	void processKeyboard(Camera_Movement direction, float deltaTime);

	/// <summary>
	/// Obs³u¿ kamerê - obracanie czyli dodawanie odpowiednich wartoœci do katów: nachylenia (pitch) oraz odchylenia (yaw).
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

