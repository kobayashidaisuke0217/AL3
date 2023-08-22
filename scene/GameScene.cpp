#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textyreHandle_ = TextureManager::Load("sample.png");
	model_.reset(Model::Create());
	skyDomeModel_.reset(Model::CreateFromOBJ("skyDome",true));
	groundModel_.reset(Model::CreateFromOBJ("ground", true));
	playerModel_.reset(Model::CreateFromOBJ("Player", true));
	playerBodyModel.reset(Model::CreateFromOBJ("float_Body"));
	playerHeadModel.reset(Model::CreateFromOBJ("float_head"));
	playerL_armModel.reset(Model::CreateFromOBJ("float_L_arm"));
	playerR_armModel.reset(Model::CreateFromOBJ("float_R_arm"));
	viewprojection_.Initialize();
	debugCamera_ = std::make_unique<DebugCamera>(1280,720);
	player_ = std::make_unique<Player>();
	player_->Initialize(playerHeadModel.get(),playerBodyModel.get(),playerR_armModel.get(),playerL_armModel.get());
	skyDome_ = std::make_unique<SkyDome>();
	skyDome_->Initialize(skyDomeModel_.get());
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(groundModel_.get());
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransformBase());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
}

void GameScene::Update() { 
	player_->Update();
	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugcameraActive_ = true;
	} 
#endif
	// カメラの処理
	if (isDebugcameraActive_ == true) {
		debugCamera_->Update();
		viewprojection_.matView = debugCamera_->GetViewProjection().matView;
		viewprojection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewprojection_.TransferMatrix();
	} else {
		viewprojection_.UpdateMatrix();
	}
	followCamera_->Update();
	viewprojection_.matView = followCamera_->GetViewProjection().matView;
	viewprojection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewprojection_.TransferMatrix();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	skyDome_->Draw(viewprojection_);
	ground_->Draw(viewprojection_);
	player_->Draw(viewprojection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
