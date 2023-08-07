#pragma once
#include "WorldTransform.h"
#include"ViewProjection.h"
#include"MyMath.h"
#include "ImGuiManager.h"
#include "CatmullRomSpline.h"
#include<vector>
class RailCamera {
public:
	void Initialize(const Vector3& pos, const Vector3& rotation, const ViewProjection& view);
	void Update();
	void Draw();
	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	std::vector<Vector3> pointsDrawing_;
	size_t pointCount_;
	std::vector<Vector3> controlPoints_;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	CatmullRomSpline rail_;
	float moveTime_;
	int indexPoint_;
	int viewPoint_;
	Vector3 target;
	Vector3 eye;

private:
	void Move();
	Vector3 learp(float t, Vector3 s, Vector3 e);
};
