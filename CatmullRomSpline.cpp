#include "CatmullRomSpline.h"

void CatmullRomSpline::Initialize(const ViewProjection& view) {
	controlPoints_ = {
	    {0, 0, 0,},
		{10, 10, 0},
		{10, 15, 0},
		{20, 15, 0},
		{20, 0, 0},
		{30, 0, 0},

	};
	pointCount_ = 100;
	primitiveDrawer_->GetInstance()->SetViewProjection(&view);
}

void CatmullRomSpline::Update() {
	
		
	
	for (size_t i = 0; i < pointCount_ + 1; i++) {
		float t = 1.0f / pointCount_ * i;
		Vector3 pos = Catmull_Rom(controlPoints_, t);
		pointsDrawing_.push_back(pos);
	}
}

void CatmullRomSpline::Draw() {
	for (uint32_t i = 0; i < pointCount_-1; i++) {
		
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		    pointsDrawing_[i], pointsDrawing_[i+1], { 1.0f, 0.0f, 0.0f, 1.0f });
	}

}

Vector3 CatmullRomSpline::Catmull_Rom(std::vector<Vector3> controlPoints, float t) {

	int n = (int)controlPoints.size();
	int segment = static_cast<int>(t * (n - 1));
	float tSegment = t * (n - 1) - segment;

	Vector3 p0 = controlPoints[segment > 0 ? segment - 1 : 0];
	Vector3 p1 = controlPoints[segment];
	Vector3 p2 = controlPoints[segment < n - 1 ? segment + 1 : n - 1];
	Vector3 p3 = controlPoints[segment < n - 2 ? segment + 2 : n - 1];

	Vector3 interpolatedPoint;
	interpolatedPoint.x =
	    0.5f * ((2.0f * p1.x) + (-p0.x + p2.x) * tSegment +
	            (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * (tSegment * tSegment) +
	            (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * (tSegment * tSegment * tSegment));
	interpolatedPoint.y =
	    0.5f * ((2.0f * p1.y) + (-p0.y + p2.y) * tSegment +
	            (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * (tSegment * tSegment) +
	            (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * (tSegment * tSegment * tSegment));
	interpolatedPoint.z =
	    0.5f * ((2.0f * p1.z) + (-p0.z + p2.z) * tSegment +
	            (2.0f * p0.z - 5.0f * p1.z + 4.0f * p2.z - p3.z) * (tSegment * tSegment) +
	            (-p0.z + 3.0f * p1.z - 3.0f * p2.z + p3.z) * (tSegment * tSegment * tSegment));

	return interpolatedPoint;
}

