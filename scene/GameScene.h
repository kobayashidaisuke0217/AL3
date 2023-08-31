#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player/Player.h"
#include <memory>
#include"skyDome/SkyDome.h"
#include"ground/Ground.h"
#include"DebugCamera.h"
#include "Camera/FollowCamera.h"
#include<vector>
#include"Enemy/Enemy.h"
#include "Manager/Collider/CollisionManager.h"
#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Finalize();
	void AddEnemyBullet(EnemyBullet* enemyBullet);
	void AddEnemyCount() { enemyCount += 1; };

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	bool isDebugcameraActive_ = false;
	uint32_t textyreHandle_ = 0;
	uint32_t ClearTexhandle = 0;
	uint32_t gameOverTexhandle = 0;
	uint32_t MissionTexhandle = 0;
	std::unique_ptr<Model> model_ = nullptr;
	ViewProjection viewprojection_;
	std::unique_ptr<Model> enemyModel_ = nullptr;
	std::unique_ptr<Model> groundModel_ = nullptr;
	std::unique_ptr<Model> skyDomeModel_ = nullptr;
	std::unique_ptr<Model> playerModel_ = nullptr;
	std::unique_ptr<Model> playerHeadModel = nullptr;
	std::unique_ptr<Model> playerBodyModel = nullptr;
	std::unique_ptr<Model> playerL_armModel = nullptr;
	std::unique_ptr<Model> playerR_armModel = nullptr;
	std::unique_ptr<Model> playerHammerModel = nullptr;
	std::unique_ptr<Model> enemyBulletModel_ = nullptr;
	std::vector<Model*> playerModels;
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr;
	//Player* player_ = nullptr;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Enemy> enemy_;
	std::list<Enemy*> enemys_;
	std::unique_ptr<Ground> ground_;
	std::unique_ptr<SkyDome> skyDome_;
	std::unique_ptr<FollowCamera> followCamera_;

	std::unique_ptr<CollisionManager> collisionManager_;
	
std::unique_ptr<Sprite> titlesprite_;
	std::unique_ptr<Sprite> Clearsprite_;
std::unique_ptr<Sprite> GameOversprite_;
	std::unique_ptr<Sprite> Missionsprite_;
	std::list<EnemyBullet*> enemyBullets_;
	std::vector<Model*> enemyModels;
	std::stringstream enemyPopCommands;
	int sceneNum;
	int enemyCount;
	int pressCount;
	int missionCount;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	/// 
	private:
	void EnemySpawn(Vector3 pos);
	    void EnemyPopData();
	    void UpdateEnemyPopCommands();
};
