#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy/Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Player/Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Manager/Collider/CollisionConfig.h"
#include"Manager/Collider/CollisionManager.h"
#include "SkyDome.h"
#include "Manager/camera/RailCamera.h"
#include "CatmullRomSpline.h"
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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textyreHandle_ = 0;
	Model* model_ = nullptr;
	Model* skyDomeModel_=nullptr;
	ViewProjection viewProjection_;

	Player* player_ = nullptr;
	// デバッグカメラ有効
	bool isDebugcameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	Enemy* enemy_ = nullptr;
	CollisionManager* collisionManager_;
	SkyDome* skyDome_;
	RailCamera* railCamera_;
	//CatmullRomSpline* Spline_;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
private:
	
};
