#pragma once
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <cassert>
#include <cmath>
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
Vector3 Add(Vector3 a, Vector3 b);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(float scalar, const Vector3& v);
float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Normalise(const Vector3& v);
Vector3 Slerp(float t, const Vector3& s, const Vector3& e);
Vector3 Lerp(float t, const Vector3& s, const Vector3& e);
Matrix4x4 MakeRotateXMatrix(float theta);
Matrix4x4 MakeRotateYMatrix(float theta);

Matrix4x4 MakeRotateZMatrix(float theta);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4
    MakeViewportMatrix(float left, float top, float width, float height, float min, float max);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);