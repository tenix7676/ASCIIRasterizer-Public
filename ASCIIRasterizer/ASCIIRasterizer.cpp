#include <vector>
#include <iostream>

#include <sstream>
#include <Windows.h>
#include <conio.h>
#include <chrono>
using namespace std::chrono;
#include <numbers>//for pi
using namespace std;

#include "DrawLineASCII.h"
#include "Vector.h"
#include "Screen.h"
#include "ScreenSize.h"
#include "Rasterizer.h"
#include "Menu.h"
#include "Input.h"


//Camera and viewport
Vector_3d camera{ 0, 0, 0 };
double viewport_distance{ 2.2 };
Vector_3d camera_direction{ 1, 0, 0 };

const int TICKS_PER_SECOND = 1'000'000; //1 sec is 10^6 microseconds (ticks), measured with duration_cast<microseconds>
const int FPS = 60;
const int FRAME = TICKS_PER_SECOND / FPS;

void writeFPS(double fps, double real_fps)
{
	stringstream ss;
	ss << "fps: " << fps << "     ";
	ss << "real fps: " << real_fps;
	Screen::writeStringOneLine(0, Screen::SCREEN_HEIGHT - 1, ss.str());
}
void writeEnter()
{
	stringstream ss;
	ss << "Press enter to exit";
	Screen::writeStringOneLine(Screen::SCREEN_WIDTH / 2, Screen::SCREEN_HEIGHT - 1, ss.str());
}

void addDelayToGetExpectedFPS(steady_clock::time_point start_time, steady_clock::time_point end_time, double& fps, double& real_fps)
{
	auto duration = duration_cast<microseconds>(end_time - start_time);
	int delta_time = static_cast<int>(duration.count());

	fps = TICKS_PER_SECOND / double(delta_time);
	
	

	//Busy loop until frame takes as much time as it should
	while(delta_time < FRAME)
	{
		end_time = high_resolution_clock::now();
		duration = duration_cast<microseconds>(end_time - start_time);
		delta_time = static_cast<int>(duration.count());
	}

	//real fps
	real_fps = TICKS_PER_SECOND / double(delta_time);
}

void playAnimation1()
{
	Wireframe cube;

	cube.initCube();
	cube.turnX(45 * numbers::pi / 180.0);
	cube.setPos({ 4.1,0,0 });

	cube.setAngleX(45 * numbers::pi / 180.0);

	double anglez{ 0 };
	double delta_angz{ 1 };

	bool anglexminus{ false };

	double fps{};
	double real_fps{};

	Screen::EnableVTMode();
	Screen::makeCursorInvisible();

	while(true)
	{
		auto start_time = high_resolution_clock::now();

		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		Screen::reset();
		Rasterizer::drawWireframe(cube.getWiresToDraw(), camera, camera_direction, viewport_distance);

		cube.setAngleZ(anglez * numbers::pi / 180.0);

		anglez += delta_angz;
		if(anglez >= 180)
			anglez = -180;


		writeFPS(fps, real_fps);
		writeEnter();
		

		Screen::makeCursorInvisible();
		Screen::print();

		auto end_time = high_resolution_clock::now();
		addDelayToGetExpectedFPS(start_time, end_time, fps, real_fps);
	}
}


void playAnimation2()
{
	Wireframe cube;

	cube.initCube();
	cube.turnX(45 * numbers::pi / 180.0);
	cube.turnY(45 * numbers::pi / 180.0);
	cube.setPos({ 4.1,0,0 });

	double anglez{ 0 };
	double delta_angz{ 1 };

	bool anglexminus{ false };

	double fps{};
	double real_fps{};

	Screen::EnableVTMode();
	Screen::makeCursorInvisible();

	while(true)
	{
		auto start_time = high_resolution_clock::now();

		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		Screen::reset();
		Rasterizer::drawWireframe(cube.getWiresToDraw(), camera, camera_direction, viewport_distance);

		cube.setAngleZ(anglez * numbers::pi / 180.0);

		anglez += delta_angz;
		if(anglez >= 180)
			anglez = -180;

		writeFPS(fps, real_fps);
		writeEnter();

		Screen::makeCursorInvisible();
		Screen::print();

		auto end_time = high_resolution_clock::now();
		addDelayToGetExpectedFPS(start_time, end_time, fps, real_fps);
	}
}


void playAnimation3()
{
	Wireframe cube;

	cube.initCube();
	//cube.turnX(45 * numbers::pi / 180.0);
	//cube.turnY(45 * numbers::pi / 180.0);
	cube.setPos({ 4.1,0,0 });

	double anglez{ 0 };
	double delta_angz{ 1 };

	double anglex{ 0 };
	double delta_angx{ 1 };

	bool anglexminus{ false };

	double fps{};
	double real_fps{};

	Screen::EnableVTMode();
	Screen::makeCursorInvisible();

	while(true)
	{
		auto start_time = high_resolution_clock::now();

		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		Screen::reset();
		Rasterizer::drawWireframe(cube.getWiresToDraw(), camera, camera_direction, viewport_distance);

		cube.setAngleZ(anglez * numbers::pi / 180.0);

		anglez += delta_angz;
		if(anglez >= 180)
			anglez = -180;

		if(anglexminus)
		{
			anglex -= delta_angx;
			cube.turnX(-delta_angx * numbers::pi / 180.0);
		}
		else
		{
			anglex += delta_angx;
			cube.turnX(delta_angx * numbers::pi / 180.0);
		}
		if(anglex >= 25)
			anglexminus = true;
		if(anglex < -25)
			anglexminus = false;

		writeFPS(fps, real_fps);
		writeEnter();

		Screen::makeCursorInvisible();
		Screen::print();

		auto end_time = high_resolution_clock::now();
		addDelayToGetExpectedFPS(start_time, end_time, fps, real_fps);
	}
}


void turnWireframeWASD(Wireframe& wireframe)
{
	const double delta_angle{ 1 * numbers::pi / 180.0 }; //5 deegres
	
	double angle_z{ 0.0 };

	while(true)
	{
		auto start_time = high_resolution_clock::now();
		double fps, real_fps;
		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		if(Input::isDown(W) or Input::isHeld(W))
			wireframe.turnX(delta_angle);
		if(Input::isDown(S) or Input::isHeld(S))
			wireframe.turnX(-delta_angle);

		if(Input::isDown(A) or Input::isHeld(A))
			angle_z += delta_angle;
		if(Input::isDown(D) or Input::isHeld(D))
			angle_z -= delta_angle;
		wireframe.setAngleZ(angle_z);


		//Show the wireframe
		Screen::reset();
		writeEnter();
		Rasterizer::drawWireframe(wireframe.getWiresToDraw(), camera, camera_direction, viewport_distance);
		Screen::print();

		auto end_time = high_resolution_clock::now();
		addDelayToGetExpectedFPS(start_time, end_time, fps, real_fps);
	}
}



void turnWireframeX(Wireframe& wireframe)
{
	double angle{ 0 };

	angle = Input::inDouble("Turn in the X axis by [Deegres]: ");

	wireframe.turnX(angle * numbers::pi / 180.0);
	
	while(true)
	{
		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		Screen::reset();
		Rasterizer::drawWireframe(wireframe.getWiresToDraw(), camera, camera_direction, viewport_distance);
		Screen::print();

		writeEnter();
	}
}

void turnWireframeY(Wireframe& wireframe)
{
	double angle{ 0 };

	angle = Input::inDouble("Turn in the Y axis by [Deegres]: ");

	wireframe.turnY(angle * numbers::pi / 180.0);

	while(true)
	{
		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		Screen::reset();
		Rasterizer::drawWireframe(wireframe.getWiresToDraw(), camera, camera_direction, viewport_distance);
		Screen::print();

		writeEnter();
	}
}

void turnWireframeZ(Wireframe& wireframe)
{
	double angle{ 0 };

	angle = Input::inDouble("Turn in the Z axis by [Deegres]: ");

	wireframe.turnZ(angle * numbers::pi / 180.0);

	while(true)
	{
		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		Screen::reset();
		Rasterizer::drawWireframe(wireframe.getWiresToDraw(), camera, camera_direction, viewport_distance);
		Screen::print();

		writeEnter();
	}
}


void changeWireframePos(Wireframe& wireframe)
{
	double x, y, z;
	Input::in3Double("Set wireframe pos [x, y, z]: ", x, y, z);

	wireframe.setPos({ x,y,z });

	while(true)
	{
		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		Screen::reset();
		writeEnter();
		Rasterizer::drawWireframe(wireframe.getWiresToDraw(), camera, camera_direction, viewport_distance);
		Screen::print();
	}
}

void changeCameraPos(Wireframe& wireframe)
{
	double x, y, z;
	Input::in3Double("Set wireframe pos [x, y, z]: ", x, y, z);

	camera = { x,y,z };

	while(true)
	{
		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		Screen::reset();
		writeEnter();
		Rasterizer::drawWireframe(wireframe.getWiresToDraw(), camera, camera_direction, viewport_distance);
		Screen::print();
	}
}

void playAnimation(Wireframe& wireframe)
{
	double anglez{ 0 };
	double delta_angz{ 1 };

	double starting_angle_z{ wireframe.getAngleZ() };

	bool anglexminus{ false };

	double fps{};
	double real_fps{};

	Screen::EnableVTMode();
	Screen::makeCursorInvisible();

	while(true)
	{
		auto start_time = high_resolution_clock::now();

		Input::updateKeyboard();
		if(Input::isDown(ENTER))
			return;

		Screen::reset();
		Rasterizer::drawWireframe(wireframe.getWiresToDraw(), camera, camera_direction, viewport_distance);

		wireframe.setAngleZ(starting_angle_z + anglez * numbers::pi / 180.0);

		anglez += delta_angz;
		if(anglez >= 180)
			anglez = -180;


		writeFPS(fps, real_fps);
		writeEnter();


		Screen::makeCursorInvisible();
		Screen::print();

		auto end_time = high_resolution_clock::now();
		addDelayToGetExpectedFPS(start_time, end_time, fps, real_fps);
	}
}

void openMenuAndRunOption()
{
	MenuOptions option = Menu::openMenu();
	switch(option)
	{
	case ANIM1:
		playAnimation1();
		return;
	case ANIM2:
		playAnimation2();
		return;
	case AMIM3:
		playAnimation3();
		return;
	case SETUP:
		break;
	}

	Wireframe cube{};
	cube.initCube(2.0, { 4, 0, 0 });

	while(true)
	{
		SubMenuOptions sub_option = Menu::openSubMenu();

		switch(sub_option)
		{
		case WASD:
			turnWireframeWASD(cube);
			break;
		case TURN_X:
			turnWireframeX(cube);
			break;
		case TURN_Y:
			turnWireframeY(cube);
			break;
		case TURN_Z:
			turnWireframeZ(cube);
			break;
		case WIREFRAME_POS:
			changeWireframePos(cube);
			break;
		case CAMERA_POS:
			changeCameraPos(cube);
			break;
		case PLAY_ANIM:
			playAnimation(cube);
			return;
		}
	}
}


int main()
{
	openMenuAndRunOption();
}


