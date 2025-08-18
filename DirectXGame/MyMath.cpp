#include "MyMath.h"
#include "numbers"
#include <cmath>

using namespace KamataEngine;
using namespace MathUtility;

Matrix4x4 KamataEngine::MakeAffineMatrix(const Vector3& scale, const Vector3& rotation, const Vector3& translation) {
    Matrix4x4 matScale = MakeScaleMatrix(scale);

    Matrix4x4 matRotX = MakeRotateXMatrix(rotation.x);
    Matrix4x4 matRotY = MakeRotateYMatrix(rotation.y);
    Matrix4x4 matRotZ = MakeRotateZMatrix(rotation.z);
    Matrix4x4 matRot = matRotZ * matRotX * matRotY;

    Matrix4x4 matTrans = MakeTranslateMatrix(translation);

    Matrix4x4 matWorld = matScale * matRot * matTrans;

    return matWorld;
}

float EaseInOut(float x1, float x2, float t) {
    float easedT = -(std::cosf(std::numbers::pi_v<float> *t) - 1.0f) / 2.0f;
    return Lerp(x1, x2, easedT);
}
