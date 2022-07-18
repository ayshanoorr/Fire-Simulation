#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include <glm/glm.hpp>
#include <vector>
#include <vecmath.h>

//particle class containing neccesary per-particle information and functions for calculating movement and distance of one particle to another
//as well as some simple get functions
class Particle
{
private:
	int m_lifetime, m_size, m_radius;
	double m_direction;
	Vector3f m_position;
	Vector3f m_velocity;
	Vector4f m_color;
	
	int w_width = 600, w_height = 500;
	
public:
	int getLifetime()
	{
		return m_lifetime;
	}
	
	Vector3f getPos()
	{ 
		return m_position;
	}
	
	Vector4f getCol()
	{ 
		return m_color;
	}
	
	Particle();
	void Update(int);
	void ReInitialize();
	float Magnitude(Vector3f _vector);
	float maxPosition();
	Vector4f calculateColor();
};

#endif
