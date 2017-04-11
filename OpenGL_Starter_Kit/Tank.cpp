#include "Tank.h"




Tank::Tank(glm::mat4 aTransformation, float scale) : SceneNode(aTransformation, scale)
{

}

void Tank::draw(float scale)
{
	Square body = Square(glm::mat4(1.0f), scale);
	body.setColor(r, g, b);
	
	
	float wheel_offset = scale / 2.0f;
	Square w1 = Square(glm::translate(glm::mat4(1.0), glm::vec3(-wheel_offset, -wheel_offset, 0.0f)), scale/5.0f);
	w1.setColor(r, g, b);
	Square w2 = Square(glm::translate(glm::mat4(1.0), glm::vec3(wheel_offset, wheel_offset, 0.0f)), scale / 5.0f);
	w2.setColor(r, g, b);
	Square w3 = Square(glm::translate(glm::mat4(1.0), glm::vec3(-wheel_offset, wheel_offset, 0.0f)), scale / 5.0f);
	w3.setColor(r, g, b);
	Square w4 = Square(glm::translate(glm::mat4(1.0), glm::vec3(wheel_offset, -wheel_offset, 0.0f)), scale / 5.0f);
	w4.setColor(r, g, b);
	

	body.addChild(&w1);
	body.addChild(&w2);
	body.addChild(&w3);
	body.addChild(&w4);

	body.render();




}


