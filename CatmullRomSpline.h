#pragma once
#include "math/MyMath.h"
#include<vector>
#include<PrimitiveDrawer.h>
#include "ViewProjection.h"
class CatmullRomSpline {
public:
	void Initialize(const ViewProjection& view);

	void Update();

	void Draw();

private:
	std::vector<Vector3> controlPoints_;
	PrimitiveDrawer* primitiveDrawer_;
	std::vector<Vector3> pointsDrawing_;
	size_t pointCount_;
	Vector3 Catmull_Rom(std::vector<Vector3> points, float t);
};
