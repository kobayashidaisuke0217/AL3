#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include"Input.h"
#include "math/MyMath.h"
#include"ViewProjection.h"
class Player 
{
public:
	void Initialize(Model* model);


void Update();

void Draw(ViewProjection view);
const WorldTransform& GetWorldtransform() { return worldTransform_; }
void SetViewProjection(const ViewProjection* view) { viewProjection_ = view; }

private:
WorldTransform worldTransform_;
	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;

private:
	void Move();
};
