#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include"Input.h"

#include"ViewProjection.h"
class Player 
{
public:
	void Initialize(Model* modelHead, Model* modelBody, Model* modelRarm, Model* modelLarm);


void Update();

void Draw(ViewProjection view);
const WorldTransform& GetWorldTransformBody() { return worldTransformBody_; }
const WorldTransform& GetWorldTransformBase() { return worldTransformBase_; }
void SetViewProjection(const ViewProjection* view) { viewProjection_ = view; }

private:
WorldTransform worldTransformBase_;
WorldTransform worldTransformHead_;
WorldTransform worldTransformLarm_;
WorldTransform worldTransformRarm_;
WorldTransform worldTransformBody_;
	Model* model_ = nullptr;
Model* modelHead_ = nullptr;
	Model* modelBody_ = nullptr;
Model* modelLarm_ = nullptr;
Model* modelRarm_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;
	float floatingParametor_ = 0.0f;


private:
	void Move();
	void SetParent(const WorldTransform* parent);
	void ModelUpdateMatrix();
	void InitializeFloatGimmick();
	void UpdateFloatGimmick();
};
