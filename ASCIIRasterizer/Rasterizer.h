#pragma once

#include <vector>

#include "Vector.h"

class Wireframe
{
private:
	std::vector<std::pair<Vector_3d, Vector_3d>> wires{};
	Vector_3d center = {0,0,0};
	double angle_x = 0;
	double angle_y = 0;
	double angle_z = 0;
public:
	//void initRectangularPrism(double width, double height, double depth, Vector_3d center_pos = { 0,0,0 });
	//void initPyramid(double base_width, double base_height, double height, Vector_3d center = { 0,0,0 });
	void initCube(double side_length=2.0, Vector_3d center_pos = { 0,0,0 });
	//void initPyramid(double sidelength, Vector_3d center_pos = { 0,0,0 });

	void turnX(double angle_x_axis);//WARNING: this changes Wireframe::wires
	void turnY(double angle_y_axis);//WARNING: this changes Wireframe::wires
	void turnZ(double angle_z_axis);//WARNING: this changes Wireframe::wires

	double getAngleZ() { return angle_z; }

	void moveByVector(Vector_3d vector);
	void setPos(Vector_3d pos);
	void setAngleX(double angle_x);
	void setAngleZ(double angle_x);
	Vector_3d getRealPos(Vector_3d point);
	std::vector<std::pair<Vector_3d, Vector_3d>> getWiresToDraw();

	Vector_3d getCenterPos() { return center;  };
};

namespace Rasterizer
{
	int getScreenX(const Vector_3d& camera, const Vector_3d& camera_direction, double viewport_distance, const Vector_3d& point);
	int getScreenY(const Vector_3d& camera, const Vector_3d& camera_direction, double viewport_distance, const Vector_3d& point);
	void drawWireframe(std::vector<std::pair<Vector_3d, Vector_3d>> wireframe_to_draw, const Vector_3d& camera, const Vector_3d& camera_direction, double viewport_distance);
	//void moveCube(std::vector<std::pair<Vector_3d, Vector_3d>>& cube, const Vector_3d& move);
}