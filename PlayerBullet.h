#pragma once
#include "Model.h"
#include "WorldTransform.h"
class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position);

	void Updarte();

	void Draw(const ViewProjection& view);

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_ ;
};
