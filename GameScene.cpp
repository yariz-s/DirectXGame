#include "GameScene.h"

using namespace KamataEngine;

void GameScene::Initialize() {
	textureHandle_ = TextureManager::Load("uvChecker.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	camera_.Initialize();
	player_ = new Player();
	player_->Initialize( model_, textureHandle_, &camera_);
}

void GameScene::Update() {
	player_->Update();
};

void GameScene::Draw() {
	
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Model::PreDraw(dxCommon->GetCommandList());
	player_->Draw();
	//model_->Draw(worldTransform_, camera_, textureHandle_);
	Model::PostDraw();

}