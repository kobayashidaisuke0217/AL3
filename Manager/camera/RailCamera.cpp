#include "RailCamera.h"

void RailCamera::Initialize(const Vector3& pos, const Vector3& rotation,const ViewProjection& view) {
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = pos;
	worldTransform_.rotation_ = rotation;
	rail_.Initialize(view);
	
	viewProjection_ = view;
	controlPoints_ = {
	    {5,   0, 10},
	    {10, 10, 0},
	    {10, 15, 0},
	    {20, 15, 0},
	    {20, 0, 0},
	    {5, 0, 10},
	};
	pointCount_ = 100;
	for (size_t i = 0; i < pointCount_ + 1; i++) {
          float t = 1.0f / pointCount_ * i;
		pointsDrawing_.push_back(  rail_.Update( controlPoints_, t));
	}
	indexPoint_ = 0;
	viewPoint_ = indexPoint_ + 5;
	
}

void RailCamera::Update() {

	
	Move();
	
	ImGui::Begin("camera");
	ImGui::DragFloat3("Pos", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("Rotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::Text("IndexPoint%f", &indexPoint_);
	ImGui::End();
}

void RailCamera::Draw() { 
	rail_.Draw(pointCount_,pointsDrawing_);

}

void RailCamera::Move() {
	if (indexPoint_ < 100) {
		moveTime_ += 0.1f;
	} else {
		indexPoint_ = 0;
		
	}
	if (viewPoint_ >= 100) {
		viewPoint_ = 0;
	}
	if (moveTime_ >= 1.0f) {
		moveTime_ = 0.0f;
		if (indexPoint_ < 100) {
			indexPoint_++;
		} 
		if (viewPoint_ < 100) {

			viewPoint_++;
		}
	}
	/*Vector3 eye = pointsDrawing_[0];
	Vector3 target = pointsDrawing_[3];*/
	if (indexPoint_ < 100) {

		 eye = learp(moveTime_, pointsDrawing_[indexPoint_], pointsDrawing_[indexPoint_ + 1]);
	}
	if (viewPoint_ < 100) {
		target = learp(moveTime_, pointsDrawing_[viewPoint_], pointsDrawing_[viewPoint_+1]);

		worldTransform_.translation_ = eye;

		Vector3 toTarget = Subtract(target, eye);
		worldTransform_.rotation_.y = std::atan2(toTarget.x, toTarget.z);
		float velXZLen = Length({toTarget.x, toTarget.z, 0});
		worldTransform_.rotation_.x = std::atan2(-toTarget.y, velXZLen);
	}
	else {
		viewPoint_ = 0;
	}
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    {1.0f, 1.0f, 1.0f}, worldTransform_.rotation_, worldTransform_.translation_);
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);


}

Vector3 RailCamera::learp(float t, Vector3 s, Vector3 e) {
	Vector3 result;

	result.x = (1.0f - t) * s.x + t * e.x;
	result.y = (1.0f - t) * s.y + t * e.y;
	result.z = (1.0f - t) * s.z + t * e.z;
	return result; }
