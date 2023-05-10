#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
class Player {
public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection view);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;
	// �L�[�{�[�h����
	Input* input_ = nullptr;
};
