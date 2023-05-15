#pragma once
#include "Vector3Calc.h"
#include "Model.h"
#include "WorldTransform.h"
class Enemy {
public:
	void Initialize(Model* model,const Vector3&position,const Vector3& velocity );
	void Update();
	void Draw(const ViewProjection& view);

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	Vector3 velocity_;
};
