#include "body.h"

#define PLANET_COUNT 9

body::body(float distance, float size, float speed, ofColor* color, BodyType bodyType)
{
	// Setup the body variables
	_distance = distance;
	_size = size;
	_speed = speed;
	_bodyColor = color;
	// Setup the position
	glm::vec2 vPos(0, distance * -1);
	_position = vPos;
	_bodyType = bodyType;

	// Setup the body (and it's sub-bodies)
	createSolarSystem();
}

bool body::createSolarSystem()
{
	int mDist = 0;
	switch (_bodyType)
	{
	case Sun:
		_bodyCount = 8;
		_bodies = new body[_bodyCount];
		mDist = 57;
		_bodies[0].setBodyAttributes(  // Mercury
			mDist = ofMap(57, 57, 4500, 30, 500),
			ofMap(2440, 2440, 69911, 3, 30),
			ofMap(47.87, 5.43, 47.87, 0.001, 0.08),
			new ofColor(137, 137, 137),
			Planet);

		_bodies[1].setBodyAttributes(  // Venus
			mDist = ofMap(108, 57, 4500, 30, 500),
			ofMap(6052, 2440, 69911, 3, 30),
			ofMap(35.02, 5.43, 47.87, 0.001, 0.08),
			new ofColor(206, 126, 46),
			Planet);

		_bodies[2].setBodyAttributes(  // Earth
			mDist = ofMap(150, 57, 4500, 30, 500),
			ofMap(6371, 2440, 69911, 3, 30),
			ofMap(29.78, 5.43, 47.87, 0.001, 0.08),
			new ofColor(22, 87, 178),
			MoonPlanet);

		_bodies[3].setBodyAttributes(  // Mars
			mDist = ofMap(228, 57, 4500, 30, 500),
			ofMap(3390, 2440, 69911, 3, 30),
			ofMap(24.077, 5.43, 47.87, 0.001, 0.08),
			new ofColor(214, 134, 35),
			Planet);

		_bodies[4].setBodyAttributes(  // Jupiter
			mDist = ofMap(779, 57, 4500, 30, 500),
			ofMap(69911, 2440, 69911, 3, 30),
			ofMap(13.07, 5.43, 47.87, 0.001, 0.08),
			new ofColor(246, 206, 144),
			MoonPlanet);

		_bodies[5].setBodyAttributes(  // Saturn
			mDist = ofMap(1430, 57, 4500, 30, 500),
			ofMap(58232, 2440, 69911, 3, 30),
			ofMap(9.69, 5.43, 47.87, 0.001, 0.08),
			new ofColor(244, 238, 179),
			RingPlanet);

		_bodies[6].setBodyAttributes(  // Uranus
			mDist = ofMap(2880, 57, 4500, 30, 500),
			ofMap(25362, 2440, 69911, 6, 50),
			ofMap(6.81, 5.43, 47.87, 0.001, 0.08),
			new ofColor(175, 247, 253),
			Planet);

		_bodies[7].setBodyAttributes(  // Neptune
			mDist = ofMap(4500, 57, 4500, 30, 500),
			ofMap(24622, 2440, 69911, 6, 50),
			ofMap(5.43, 5.43, 47.87, 0.001, 0.08),
			new ofColor(28, 21, 238),
			Planet);
		break;
	case MoonPlanet:
		_bodyCount = 1;
		_bodies = new body[_bodyCount];
		mDist = 4;    // Distance between planets
		_bodies[0].setBodyAttributes(   // Moon
			mDist + _size,
			2, // Body Size
			-.04, // Body Velocity
			new ofColor(155, 155, 155), Empty);
		break;
	case RingPlanet:
		ofSetLineWidth(5.0);
		new ofColor(155, 155, 155); //216, 210, 140
		ofDrawLine(-50, 50, 20, -20);
	default:
		_bodyCount = 0;
		_bodies = NULL;
		break;
	}

	return true;
}

bool body::setBodyAttributes(int distance, int size, float speed, ofColor* color, BodyType bt)
{
	_distance = distance;
	_size = size;
	_speed = speed;
	_bodyColor = color;
	glm::vec2 vPos(0, distance * -1);
	_position = vPos;
	_bodyType = bt;
	createSolarSystem();

	return true;
}

// Draw the body
void body::draw()
{
	ofPushMatrix();

	ofSetColor(*_bodyColor);
	ofTranslate(_position);
	ofDrawCircle(0.0, 0.0, _size);

	for (int i = 0; i < _bodyCount; i++)
		_bodies[i].draw();

	ofPopMatrix();
}

// Calculate the body's position
void body::calc()
{
	// calc the new position of this body
	_position.x = cos(ofGetFrameNum() * _speed) * _distance;
	_position.y = sin(ofGetFrameNum() * _speed) * _distance;

	// Calculate all the sub items of this body
	for (int i = 0; i < _bodyCount; i++)
		_bodies[i].calc();
}