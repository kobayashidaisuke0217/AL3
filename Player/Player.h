#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include"Input.h"
#include<Charactor/BaseCharactor.h>
#include"ViewProjection.h"
#include <optional>
#include <Sprite.h>
#include <memory>
#include "Manager/Collider/Collider.h"
#include "Manager/Collider/CollisionConfig.h"
#include"PlayerBullet.h"
#include <list>

class Player :public BaseCharactor,public Collider
{
public:
	void Initialize(const std::vector<Model*>& models,const Vector3& pos) override;
	 ~Player();

void Update()override;

void Draw(const ViewProjection& view)override;
void DrawUI();
const WorldTransform& GetWorldTransformBody() { return worldTransformBody_; }
const WorldTransform& GetWorldTransformBase() { return worldTransformBase_; }
void SetViewProjection(const ViewProjection* view) { viewProjection_ = view; }

Vector3 GetWorldPos() override;
void OnCollision() override;

const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

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
	
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;
	float floatingParametor_ = 0.0f;
	int animationFrame;
	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	/*Sprite* sprite2DReticle_ = nullptr;*/
	std::unique_ptr<Sprite> sprite2DReticle_ = nullptr;
	WorldTransform worldtransform3Dreticle_;
	bool jumpFlag;
	float jumpMove = 0.0f;
	bool AtackCountFlag ;
	int atackCount ;
    std::list<PlayerBullet*> bullets_;
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
	void ApplyGlobalVariables();
	void Jump();
	void JUmpInitialize();
	//void Atack();
	void Setreticle(const ViewProjection* view);
	void Atack();
};

