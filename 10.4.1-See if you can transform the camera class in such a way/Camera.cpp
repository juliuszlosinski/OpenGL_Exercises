#include "Camera.h"

/// <summary>
/// Konstruktor podstawowy oraz niestandardowy.
/// </summary>
/// <param name="position"> Pozycja kamery. </param>
/// <param name="up"> Wektor wskazujace gore wzglêdem œwiata. </param>
/// <param name="yaw"> Odchylenie wzglêdem osi Y. </param>
/// <param name="pitch"> Pochylenie wzglêdem osi X.</param>
Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
{
	movementSpeed = SPEED;
	mouseSensitivity = SENSITIVITY;
	zoom = ZOOM;

	this->position = position;
	this->worldUp = up;
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->yaw = yaw;
	this->pitch = pitch;

	updateCameraVectors();
}

/// <summary>
/// Uzyskaj macierz widoku kamery.
/// </summary>
/// <returns></returns>
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

/// <summary>
/// Obs³u¿ kamere - ruch u¿ywaj¹c przycisków klawiatury.
/// </summary>
/// <param name="direction"> Kierunek.</param>
/// <param name="deltaTime">Iloœæ czasu up³yniêtego pomiêdzy ostatni¹ klatk¹.</param>
void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;

	position.y = 0.0f;
}

/// <summary>
/// Obs³u¿ kamêrê - poprostu od starej pozycji myszy odejmuj now¹ pozycjê myszy, dodaj t¹ ró¿nicê do odpowiednich k¹tów (pitch - nachylenia, yaw - odchylenia).
/// </summary>
/// <param name="xOffset"></param>
/// <param name="yOffset"></param>
/// <param name="constainPitch"></param>
void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constainPitch)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (constainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		/*
		if (yaw > -45.0f)
			yaw = -45.0f;
		if (yaw < -135.0f)
			yaw = -135.0f;
		*/
	}

	updateCameraVectors();
}

/// <summary>
/// Aktualizuj parametry kamery.
/// </summary>
void Camera::updateCameraVectors()
{
	float x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	float y = sin(glm::radians(this->pitch));
	float z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(glm::vec3(x, y, z));
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}