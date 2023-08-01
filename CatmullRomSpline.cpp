#include "CatmullRomSpline.h"

void CatmullRomSpline::Initialize(ViewProjection* view) {
	controlPoints_ = {
	    {0, 0, 0,},
		{10, 10, 0},
		{10, 15, 0},
		{20, 15, 0},
		{20, 0, 0},
		{30, 0, 0},

	};
	pointCount_ = 10;
	
	primitiveDrawer_->GetInstance()->SetViewProjection(view);
	
}

void CatmullRomSpline::Update() {
	/*for (size_t i = 0; i < pointCount_ + 1; i++) {
		float t = 1.0f / pointCount_ * i;
		Vector3 pos = Catmull_Rom(controlPoints_, t);
		pointsDrawing_.push_back(pos);
	
	}*/
	
}

void CatmullRomSpline::Draw() {
	for (uint32_t i = 0; i < pointsDrawing_.size()-1; i++) {
		
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		    pointsDrawing_[i], pointsDrawing_[i+1], { 1.0f, 0.0f, 0.0f, 1.0f });
	}

}

Vector3 CatmullRomSpline::Catmull_Rom(std::vector<Vector3> points, float t) {
	int p1, p2, p3, p0;
	p1 = (int)t + 1;
	p2 = p1 + 1;
	p3 = p2 + 1;
	p0 = p1 - 1;
	t = t - (int)t;
	return {
	    0.5f * ((-points[p0].x + 3 * points[p1].x - 3 * points[p2].x + points[p3].x) * (t * t * t) +
	            (2 * points[p0].x - 5 * points[p1].x + 4 * points[p2].x - points[p3].x) * (t * t) +
	            (-points[p0].x + points[p2].x) * t + 2 * points[p1].x),
	    0.5f * ((-points[p0].y + 3 * points[p1].y - 3 * points[p2].y + points[p3].y) * (t * t * t) +
	            (2 * points[p0].y - 5 * points[p1].y + 4 * points[p2].y - points[p3].y) * (t * t) +
	            (-points[p0].y + points[p2].y) * t + 2 * points[p1].y),
	    0.5f * ((-points[p0].z + 3 * points[p1].z - 3 * points[p2].z + points[p3].z) * (t * t * t) +
	            (2 * points[p0].z - 5 * points[p1].z + 4 * points[p2].z - points[p3].z) * (t * t) +
	            (-points[p0].z + points[p2].z) * t + 2 * points[p1].z)
	};
}

