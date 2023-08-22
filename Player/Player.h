#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include"Input.h"
#include<Charactor/BaseCharactor.h>
#include"ViewProjection.h"
#include <optional>
class Player :public BaseCharactor
{
public:
	void Initialize(const std::vector<Model*>& models) override;


void Update()override;

void Draw(const ViewProjection& view)override;
const WorldTransform& GetWorldTransformBody() { return worldTransformBody_; }
const WorldTransform& GetWorldTransformBase() { return worldTransformBase_; }
void SetViewProjection(const ViewProjection* view) { viewProjection_ = view; }

private:
	enum class Behavior {
		kRoot,
		kAttack,
};
WorldTransform worldTransformBase_;
WorldTransform worldTransformHead_;
WorldTransform worldTransformLarm_;
WorldTransform worldTransformRarm_;
WorldTransform worldTransformBody_;
WorldTransform worldTransformHammer_;
	/*Model* model_ = nullptr;
Model* modelHead_ = nullptr;
	Model* modelBody_ = nullptr;
Model* modelLarm_ = nullptr;
Model* modelRarm_ = nullptr;*/
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;
	float floatingParametor_ = 0.0f;
	int animationFrame;
	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

private:
	void Move();
	void SetParent(const WorldTransform* parent);
	void ModelUpdateMatrix();
	void InitializeFloatGimmick();
	void UpdateFloatGimmick();
	void BehaviorRootUpdate();
	void BehaviorAtackUpdate();
	void BehaviorRootInitialize();
	void BehaviorAtackInitialize();
	
};
