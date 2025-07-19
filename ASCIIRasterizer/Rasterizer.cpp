#include "Rasterizer.h"

#include <vector>
#include <cmath>

#include "Vector.h"
#include "ViewportSize.h"
#include "ScreenSize.h"
#include "Screen.h"



using namespace std;
using namespace Screen;
using namespace Rasterizer;

namespace Rasterizer
{
	const char POINT_CHAR{ '&' };

	int getScreenX(const Vector_3d& camera, double viewport_distance, const Vector_3d& point, bool& too_close)
	{
		if (point.x - camera.x <= viewport_distance)
		{
			too_close = true;
			return -1;
		}

		double view_pos_x = (point.y - camera.y) / (point.x - camera.x) * (viewport_distance);
		int screen_pos_x = view_pos_x * SCREEN_WIDTH / VIEW_WIDTH;

		return screen_pos_x + SCREEN_WIDTH / 2;

	}

	int getScreenY(const Vector_3d& camera, double viewport_distance, const Vector_3d& point, bool& too_close)
	{
		if (point.x - camera.x <= viewport_distance)
		{
			too_close = true;
			return -1;
		}

		double view_pos_y = (point.z - camera.z) / (point.x - camera.x) * (viewport_distance);
		int screen_pos_y = view_pos_y * SCREEN_HEIGHT / VIEW_HEIGHT;

		return -(screen_pos_y - SCREEN_HEIGHT / 2);
	}
	void drawWireframe(vector<pair<Vector_3d, Vector_3d>> wireframe_to_draw, const Vector_3d& camera, double viewport_distance)
	{
		for(const auto& line : wireframe_to_draw)
		{
			bool point0_too_close = false;
			int x0 = getScreenX(camera, viewport_distance, line.first, point0_too_close);
			int y0 = getScreenY(camera, viewport_distance, line.first, point0_too_close);
			bool point1_too_close = false;
			int x1 = getScreenX(camera, viewport_distance, line.second, point1_too_close);
			int y1 = getScreenY(camera, viewport_distance, line.second, point1_too_close);

			if(!point0_too_close and !point1_too_close)
			{
				Screen::drawLine(x0, y0, x1, y1);
				Screen::draw(x0, y0, POINT_CHAR);
				Screen::draw(x1, y1, POINT_CHAR);
			}
			else
			{
				Screen::warningTooClose();
			}
		}
	}
}

void Wireframe::initCube(double side_length, Vector_3d center_pos)
{
	wires.clear();

	center = center_pos;

	Vector_3d cube_vertices[8]{
		//Bottom of cube
		{ -1, -1, -1 },
		{ -1, +1, -1 },
		{ +1, +1, -1 },
		{ +1, -1, -1 },
		//Top of cube
	{ -1, -1, +1 },
	{ -1, +1, +1 },
	{ +1, +1, +1 },
	{ +1, -1, +1 },
	};

	//Scale the cube to the appropriate size
	for(int i{ 0 }; i < 8; ++i)
	{
		cube_vertices[i] *= side_length / 2.0;
	}

	//Bottom
	for(int i{ 0 }; i < 4; ++i)
	{
		wires.push_back({ cube_vertices[i], cube_vertices[(i + 1) % 4] });
	}

	//Top
	for(int i{ 0 }; i < 4; ++i)
	{
		wires.push_back({ cube_vertices[i + 4], cube_vertices[(i + 1) % 4 + 4] });
	}

	//Connect bottom and top
	for(int i{ 0 }; i < 4; ++i)
	{
		wires.push_back({ cube_vertices[(i + 1) % 4], cube_vertices[(i + 1) % 4 + 4] });
	}

}

void turnByAngleX(Vector_3d& point, double angle_x_axis)
{
	double pivot_length = length(point.z, point.y);
	double new_angle = atan2(point.z, point.y) + angle_x_axis;

	point.y = cos(new_angle) * pivot_length;
	point.z = sin(new_angle) * pivot_length;
}
void turnByAngleY(Vector_3d& point, double angle_y_axis)
{
	double pivot_length = length(point.x, point.z);
	double new_angle = atan2(point.x, point.z) + angle_y_axis;

	point.x = cos(new_angle) * pivot_length;
	point.z = sin(new_angle) * pivot_length;
}
void turnByAngleZ(Vector_3d& point, double angle_z_axis)
{
	double pivot_length = length(point.x, point.y);
	double new_angle = atan2(point.x, point.y) + angle_z_axis;

	point.x = cos(new_angle) * pivot_length;
	point.y = sin(new_angle) * pivot_length;
}


void Wireframe::turnX(double angle_x_axis)
{
	//Turn around the x axis
	for(auto& line : wires)
	{
		turnByAngleX(line.first, angle_x_axis);
		turnByAngleX(line.second, angle_x_axis);
	}
}
void Wireframe::turnY(double angle_y_axis)
{
	//Turn around the y axis
	for(auto& line : wires)
	{
		turnByAngleY(line.first, angle_y_axis);
		turnByAngleY(line.second, angle_y_axis);
	}
}
void Wireframe::turnZ(double angle_z_axis)
{
	//Turn around the z axis
	for(auto& line : wires)
	{
		turnByAngleZ(line.first, angle_z_axis);
		turnByAngleZ(line.second, angle_z_axis);
	}
}



void Wireframe::moveByVector(Vector_3d vector)
{
	center += vector;
}

Vector_3d Wireframe::getPos()
{
	return center;
}

void Wireframe::setPos(Vector_3d pos)
{
	center = pos;
}

void Wireframe::setAngleX(double angle)
{
	angle_x = angle;
}
void Wireframe::setAngleZ(double angle)
{
	angle_z = angle;
}

Vector_3d Wireframe::getRealPos(Vector_3d point)
{
	Vector_3d point_out{ point };

	turnByAngleZ(point_out, angle_z);
	turnByAngleX(point_out, angle_x);
	/*double new_angle_x = atan2(point.z, point.y) + angle_x;

	double yz_length = length(point.y, point.z);
	point_out.y = cos(new_angle_x) * yz_length;
	point_out.z = sin(new_angle_x) * yz_length;

	double new_angle_z = atan2(point.y, point_out.x) + angle_z;

	double xy_length = length(point.x, point.y);
	point_out.x = cos(new_angle_z) * xy_length;
	point_out.y = sin(new_angle_z) * xy_length;*/




	//double new_angle_x = atan2(point.y, point.x) + angle_x;
	//double new_angle_z = asin(point.z / length(point)) + angle_z;
	//new_angle_z = asin(point.z / length(point)) + angle_z;

	//double xy_length = cos(new_angle_z) * length(point);
	//point_out.x = cos(new_angle_x) * xy_length;
	//point_out.y = sin(new_angle_x) * xy_length;
	//point_out.z = sin(new_angle_z) * length(point);

	return point_out + center;
}

vector<pair<Vector_3d, Vector_3d>> Wireframe::getWiresToDraw()
{
	vector<pair<Vector_3d, Vector_3d>> wires_to_draw{};


	for(const auto& line : wires)
	{
		Vector_3d point0 = getRealPos(line.first);
		Vector_3d point1 = getRealPos(line.second);
		wires_to_draw.push_back({ point0, point1 });
	}

	return wires_to_draw;
}