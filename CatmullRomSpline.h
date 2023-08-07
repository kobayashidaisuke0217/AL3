#pragma once
#include "math/MyMath.h"
#include<vector>
#include<PrimitiveDrawer.h>
#include "ViewProjection.h"

class CatmullRomSpline {
public:
	void Initialize(const ViewProjection& view);

	Vector3 Update(const std::vector<Vector3>& points, float t);

	void Draw(const size_t& count, const std::vector<Vector3>& drawPoints);
	
Vector3 Catmull_Rom(std::vector<Vector3> points, float t);
private:
	
	PrimitiveDrawer* primitiveDrawer_;
	
};
