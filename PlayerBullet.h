#pragma once
#include "Model.h"
class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection& view);
};
