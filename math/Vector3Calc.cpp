//#include "Vector3Calc.h"
//
//Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
//	return {
//	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
//	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][2],
//	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
//	};
//}
//Vector3 Add(Vector3 a, Vector3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
//
//Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
//	return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
//}
//Vector3 Multiply(float scalar, const Vector3& v) {
//	return {v.x * scalar, v.y * scalar, v.z * scalar};
//}
//float Dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
//float Length(const Vector3& v) { return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }
//
//Vector3 Normalise(const Vector3& v) {
//	float len = Length(v);
//	if (len != 0) {
//		return {v.x / len, v.y / len, v.z / len};
//	}
//	return v;
//}
//Vector3 Lerp(float t, const Vector3& s, const Vector3& e) {
//	Vector3 result;
//	Vector3 es = Subtract(e, s);
//	result = Add(s, Multiply(t, es));
//	return result;
//}
//Vector3 Slerp(float t, const Vector3& s, const Vector3& e) {
//	float dot = Dot(Normalise(s), Normalise(e));
//	if (std::abs(dot) > 0.999f) {
//		return Lerp(t, s, e);
//	}
//	float theta = std::acos(dot);
//	float sinTheta = std::sin(theta);
//	float t1 = std::sin((1.0f - t) * theta) / sinTheta;
//	float t2 = std::sin(t * theta) / sinTheta;
//
//	return Add(Multiply(t1, s), Multiply(t2, e));
//}