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
	bool isDebugcameraActive_ = false;
	uint32_t textyreHandle_ = 0;
	std::unique_ptr<Model> model_ = nullptr;
	ViewProjection viewprojection_;
	std::unique_ptr<Model> groundModel_ = nullptr;
	std::unique_ptr<Model> skyDomeModel_ = nullptr;
	std::unique_ptr<Model> playerModel_ = nullptr;
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr;
	//Player* player_ = nullptr;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Ground> ground_;
	std::unique_ptr<SkyDome> skyDome_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
