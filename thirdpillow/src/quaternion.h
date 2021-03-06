/*
 * quaternion.h
 *
 *  Created on: Apr 13, 2014
 *      Author: jwpilly
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <stdio.h>
#include <math.h>

class quaternion {
public:
	quaternion();
	quaternion(float x, float y, float z, float w);
	void set_x(float x);
	void set_y(float y);
	void set_z(float z);
	void set_w(float w);
	float get_x();
	float get_y();
	float get_z();
	float get_w();
	float magnitude();
	void normalize();
	virtual ~quaternion();
	void conjugate();
	void multiply(quaternion* q);
	void multiply(float v_x, float v_y, float v_z);

	void print();
	quaternion* clone();
private:
	float x;
	float y;
	float z;
	float w;
};

#endif /* QUATERNION_H_ */
