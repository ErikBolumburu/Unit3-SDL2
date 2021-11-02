#include <Transform.hpp>
#include <Game.hpp>
#include <iostream>


void Transform::SetTransform(Transform newTransform){
    position = newTransform.position; // Set position to the newTransform.position
}

void Transform::SetPosition(Vector2 newPosition){
    position = newPosition; //Set position to the newPosition
}

void Transform::Move(Vector2 direction){
    // Add the direction vector to the position vector
    // Multply by game.deltaTime to ensure that regardless of FPS, the player will move at a consistent speed.
    position.x += direction.x * game.deltaTime;
    position.y += direction.y * game.deltaTime;
}