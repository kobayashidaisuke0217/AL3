#pragma once
#include"3d/Model.h"
#include "3d/WorldTransform.h"
#include "3d/ViewProjection.h"
class SkyDome {
public:
	void Initialize( Model* model);

	void Update();

	void Draw(const ViewProjection& viewPrijection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	
};
