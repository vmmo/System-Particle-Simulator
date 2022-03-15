#pragma once
#include "ofMain.h"

enum particleMode{//kiwi
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE,
	PARTICLE_MODE_PAUSE,
	PARTICLE_IS,
	PARTICLE_DS,
	PARTICLE_DV, //vmmo
	PARTICLE_IV
};

class Particle{

	public:
		Particle();
		
		void setMode(particleMode newMode);	
		void setAttractPoints( vector <glm::vec3> * attract );
		void attractToPoint(int, int);
		void repelFromPoint(int, int);
		void reset();
		void update();
		void draw();		
		
		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;
		glm::vec3 newVel; // vmmo
		
		float drag; 
		float uniqueVal;
		float scale;
		double changeVel; // vmmo

		particleMode mode;
		particleMode previousMode;
		
		vector <glm::vec3> * attractPoints; 
};
