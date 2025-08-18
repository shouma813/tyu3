#include "skydome.h"

void Skydome::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	camera_ = camera;
}

void Skydome::Update() {}

void Skydome::Draw() { model_->Draw(worldTransform_, *camera_); }

