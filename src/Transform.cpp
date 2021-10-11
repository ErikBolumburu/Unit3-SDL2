#include <Transform.hpp>
#include <iostream>


void Transform::SetTransform(Transform newTransform){
    position = newTransform.position;
}

void Transform::SetPosition(Vector2 newPosition){
    position = newPosition;
}

void Transform::Move(Vector2 direction){
    position.x += direction.x;
    position.y += direction.y;
}