#include "collisions.h" 
#include <math.h>
#include <iostream>

using namespace std;

//doCollisions takes the radius, position, curent velocity and mass of a pair of objects: 
void collisions::doCollisions(float radius1, float mass1, vec3 position1, vec3& velocity1, float radius2, float mass2, vec3 position2, vec3& velocity2, string type) {

	glm::vec3 vectorBetweenObjects;

	//If there is a collision then: 
	if (isCollide(radius1, position1, radius2, position2))
	{
		//If the collision is between two people: then the main character interacts with the normal character using the 3rd law of Newton. 
		// The respond time is direct. 
		if (type == "people") {
			vectorBetweenObjects = position2 - position1; // vector between the two object
			vectorBetweenObjects = glm::normalize(vectorBetweenObjects); // have a vector in same direction of length one. 

			//dot product of the vector between the two position and the velocity of the main character: 
			GLfloat xPositionOfBetweenObject1 = glm::dot(vectorBetweenObjects, velocity1);
			glm::vec3 vector1x = vectorBetweenObjects * xPositionOfBetweenObject1; // get vector for x
			glm::vec3 vector1Z = velocity1 - vector1x; // get vector for Z

			//Do the same for the main character (in opposite direction): 
			vectorBetweenObjects = vectorBetweenObjects * -1.0f;

			GLfloat xPositionOfBetweenObject2 = glm::dot(vectorBetweenObjects, velocity2);
			vec3 vector2x = vectorBetweenObjects * xPositionOfBetweenObject2;
			vec3 vector2Z = velocity2 - vector2x;

			//Calculate the final velocity vecetor for both objects: 
			vec3 finalVelocityObject1 = glm::vec3((vector1x * (mass1 - mass2) / (mass1 + mass2)) + (vector2x * (2 * mass2) / (mass1 + mass2)) + vector1Z);
			vec3 finalVelocityObject2 = glm::vec3((vector1x * (2 * mass1) / (mass1 + mass2)) + (vector2x * (mass2 - mass1) / (mass1 + mass2)) + vector2Z);

			//Update both velocities: 
			velocity1 = finalVelocityObject1;
			velocity2 = finalVelocityObject2;
		}
		//If the collision is between a building or a tree or a car with the main character then the main character cannot pass through them: 
		else if(type == "wall"){
			velocity2 += -velocity2;
		}
	}


}

bool collisions::isCollide(float radius1, vec3 position1, float radius2, vec3 position2)
{
	// xBase cest le point en bas à gauche (origine) de la box et xExtrem cest le point en haut à droite...
	bool isCollisionOnX = false;
	bool isCollisionOnY = false;
	bool isCollisionOnZ = false;
	bool collisionResult = false;

	//Check if there is an intersection between the first and second object in x, y and z: 
	isCollisionOnX = position1.x + radius1 >= position2.x && position2.x + radius2 >= position1.x;
	isCollisionOnY = position1.y + radius1 >= position2.y && position2.y + radius2 >= position1.y;
	isCollisionOnZ = position1.z + radius1 >= position2.z && position2.z + radius2 >= position1.z;

	//if there is an intersection on all axis there we have a collision.
	collisionResult = isCollisionOnX && isCollisionOnY && isCollisionOnZ;
	return collisionResult;
}