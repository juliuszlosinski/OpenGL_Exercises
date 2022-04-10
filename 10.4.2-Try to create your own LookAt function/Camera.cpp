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
/// Uzyskaj macierz widoku kamery, która zosta³a stworzona w sposób niestandardowy.
/// </summary>
/// <returns></returns>
glm::mat4 Camera::getViewMatrix_CUSTOM()
{
	glm::mat4 translation = glm::mat4(1.0f); 
	translation[3][0] = -position.x;
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;

	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = right.x; 
	rotation[1][0] = right.y;
	rotation[2][0] = right.z;

	rotation[0][1] = up.x; 
	rotation[1][1] = up.y;
	rotation[2][1] = up.z;

	rotation[0][2] = -front.x; 
	rotation[1][2] = -front.y;
	rotation[2][2] = -front.z;
	
	return rotation * translation; 
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