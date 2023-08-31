#pragma once
#include<Charactor/BaseCharactor.h>
#include "Manager/Collider/Collider.h"
#include "Manager/Collider/CollisionConfig.h"
#include "EnemyBullet.h"

class GameScene;
class Player;
class Enemy:public BaseCharactor,public Collider {
public:
	void Initialize(const std::vector<Model*>& models, const Vector3& pos) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;

	Vector3 GetWorldPos() override;
	void OnCollision() override;
	void SetPlayer(Player* player) { player_ = player; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	bool IsAlive() { return isAlive_; }

private:
	bool isAlive_;
	Player* player_ = nullptr;
	GameScene* gameScene_ = nullptr;
	int count;

private:
	void Fire();
};
