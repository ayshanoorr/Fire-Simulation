#include "Particle.h"
#include <random>
#include <time.h>
#include <vecmath.h>
#include <iostream>
#include <GL/glew.h>
using namespace std;

int w_range = 275;
int h_range = 50;

// obtain color depending on position i.e center will have yellowish color edges will have reddish color
Vector4f Particle::calculateColor()
{
	float sum = w_width + w_height;
	float diff = (w_width - m_position.x()) + (w_height - m_position.y());
	float scaling_factor = diff / sum;
	sum = sum / 2;
	m_direction = (2 * M_PI * rand()) / RAND_MAX; // direction is the angle
	return Vector4f(1.0, scaling_factor * (diff / sum), 0.1, 1.0);
}


// obtain color depending on position i.e center will have yellowish color edges will have reddish color
float Particle::maxPosition()
{
	float sum = w_width + w_height;
	
	float diff;
	if (m_position.x() <= w_width / 2)
	{
		diff = m_position.x();
	}
	else
	{
		diff = (w_width / 2) - (m_position.x() - (w_width / 2));
	}
	
	return diff / (w_width / 2);
}


//contructor giving a random starting position (within range)
Particle::Particle()
{
	m_lifetime = 20;
	m_velocity = Vector3f(0,0,0);
	m_position = Vector3f(rand() % 50 + w_range, rand() % 150 + h_range, 100);
	m_color = calculateColor();
	m_radius = 40;
}


// returns the magnitude of vector minus the direction factor
float Particle::Magnitude(Vector3f _vector)
{
	return (_vector.x() * _vector.x())+(_vector.y() * _vector.y())+(_vector.z() * _vector.z());
}


// reitinialize after lifetime is over
void Particle::ReInitialize()
{
	m_lifetime = 20;
	m_velocity = Vector3f(0,0,0);
	m_position = Vector3f(rand() % 50 + 275, rand() % 150 + 50, 100);
	m_color = calculateColor();
}


//update loop goes through all particles within some range of itself and either accelerates towards or away from them depending on density
void Particle::Update(int delta_time)
{
	Vector3f acceleration;
	acceleration.y() += 0.6f;
	
	//lifetime of the particle decreased
	m_lifetime--;
	
	// update values
	int add_min = rand() % 2;
	if (add_min == 1)
		m_position.x() += (rand() % 7 + 1) * ((float)delta_time / 10000.0f);
	else
		m_position.x() -= (rand() % 7 + 1) * ((float)delta_time / 10000.0f);
		
	add_min = rand() % 100;
	if (add_min > 90 && m_position.y() > 170)
		m_position.y() *= maxPosition();
	else
		m_position.y() = m_position.y();
		
	/*if (m_position.x() > 350 || m_position.x() < 250)
		ReInitialize();
	else if (m_position.y() > 400)
		ReInitialize();*/
	
	m_velocity += acceleration * ((float)delta_time / 10000.0f);
	m_position += m_velocity * ((float)delta_time / 10000.0f);
	m_color = calculateColor();
	
}
