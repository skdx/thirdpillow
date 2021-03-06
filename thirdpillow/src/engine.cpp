/*
 * engine.cpp
 *
 *  Created on: Apr 7, 2014
 *      Author: jwpilly
 */

#include "engine.h"

camera* cam;

world* engine::get_scene() {
	return &this->scene;
}

void engine::cleanup() {
	printf("cleaning up\n");
	delete this->frame;
}

float engine::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void engine::initialize() {
	printf("engine initializing\n");
	color* default_color = new color(1, 0, 0, 1);
	rast = new rasterizer(default_color);
	player = new transform();
	cam = new camera(this->frame->get_width(), this->frame->get_height());
	transform::set_camera(cam);
	vector3* start = new vector3(-20, 0, 0);
	cam->set_position(start);
	transform::set_projection((float)70, (float) this->frame->get_width(), this->frame->get_height(), (float) 1, (float)1000);
	mesh* m = new mesh();
	m->from_obj("res/testalduinsmall.obj");
	//m->from_obj("res/teststeve.obj");
	image* texture = new image();
	texture->from_ppm_raw("res/alduin_lod.ppm");
	//texture->from_ppm_raw("res/teststeve.ppm");
	thing* t = new thing();
	t->set_mesh(m);
	t->set_texture(texture);
	t->t.set_scale(1, 1, 1);
	this->scene.things.push_back(t);
}

void engine::start() {
	printf("engine started\n");
	this->initialize();
}

void engine::stop() {
	this->cleanup();
}

void engine::render() {
	this->frame->cls();
	for (int i = 0; i < this->scene.things.size(); i++) {
		thing* t = this->scene.things[i];
		mesh* m = t->get_mesh();
		image* texture = t->get_texture();
		matrix4* mt = t->t.get_projected_transformation();
		this->rast->draw_mesh_textured(this->frame, m, t->get_texture(), mt);
		delete mt;
	}
}

float* engine::get_render_buffer() {
	return this->frame->get_buffer();
}

engine::engine(int render_width, int render_height) {
	printf("engine created (%d, %d)\n", render_width, render_height);
	this->frame = new screen(render_width, render_height);
}

engine::~engine() {
	printf("stopping engine\n");
	this->stop();
}

