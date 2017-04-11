#include "Sphere.h"



Sphere::Sphere(glm::mat4 aTransformation, float scale) : SceneNode(aTransformation, scale)
{

}

void Sphere::draw(float scale)
{
	
	// Draw Sphere here using circles
	//Parent Node
	Circle c = Circle(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)), scale);
	c.render();

	for (float theta = 0.0f; theta < 3.141/2.0f ; theta += 0.1)
	{
		
		float newScale = scale * cos(theta);
		float translation_value = scale * sin(theta);
		Circle top_circle = Circle(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, translation_value)), newScale);
		Circle bottom_circle = Circle(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -translation_value)), newScale);
		c.addChild(&top_circle);
		c.addChild(&bottom_circle);
		top_circle.render();
		bottom_circle.render();


	}

	
}


