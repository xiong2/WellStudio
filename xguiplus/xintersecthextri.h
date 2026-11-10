#pragma once
#include <cmath>
#include <array>

#define XABS(a) (a) > 0 ? (a) : -(a)
#define XMAX(a, b) (a) > (b) ? (a) : (b)
#define XMIN(a, b) (a) > (b) ? (b) : (a)

struct Vec3 {
	double x, y, z;

	Vec3 operator-(const Vec3& v) const {
		return { x - v.x, y - v.y, z - v.z };
	}

	Vec3 operator+(const Vec3& v) const {
		return { x + v.x, y + v.y, z + v.z };
	}

	Vec3 operator*(double s) const {
		return { x * s, y * s, z * s };
	}
};

inline Vec3 cross(const Vec3& a, const Vec3& b) {
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

inline double dot(const Vec3& a, const Vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline double length(const Vec3& v) {
	return std::sqrt(dot(v, v));
}

struct Triangle {
	Vec3 v0, v1, v2;
};

struct Hexahedron {
	std::array<Vec3, 8> vertices;  // Assumes V0-V7 ordered like a cube
};

// Ray-triangle intersection using Möller–Trumbore algorithm
inline bool segmentIntersectsTriangle(const Vec3& p0, const Vec3& p1, const Triangle& tri) {
	Vec3 dir = p1 - p0;
	Vec3 edge1 = tri.v1 - tri.v0;
	Vec3 edge2 = tri.v2 - tri.v0;
	Vec3 h = cross(dir, edge2);
	double a = dot(edge1, h);
	if (std::fabs(a) < 1e-6f) return false;

	double f = 1.0f / a;
	Vec3 s = p0 - tri.v0;
	double u = f * dot(s, h);
	if (u < 0.0f || u > 1.0f) return false;

	Vec3 q = cross(s, edge1);
	double v = f * dot(dir, q);
	if (v < 0.0f || u + v > 1.0f) return false;

	double t = f * dot(edge2, q);
	return t >= 0.0f && t <= 1.0f;
}

// Check if point is inside convex hexahedron using face normals
inline bool pointInsideHexahedron(const Vec3& p, const Hexahedron& hex) {
	const std::array<std::array<int, 4>, 6> faces = { {
		{0,1,2,3}, {4,5,6,7}, {0,1,5,4},
		{2,3,7,6}, {1,2,6,5}, {0,3,7,4}
	} };
	for (const auto& face : faces) {
		Vec3 a = hex.vertices[face[0]];
		Vec3 b = hex.vertices[face[1]];
		Vec3 c = hex.vertices[face[2]];
		Vec3 n = cross(b - a, c - a);
		if (dot(n, p - a) > 0) return false;
	}
	return true;
}

// Hex face triangulated → test triangle vs triangle intersection
inline bool triangleIntersectsHexahedron(const Triangle& tri, const Hexahedron& hex) {
	// Step 1: Vertex containment
	if (pointInsideHexahedron(tri.v0, hex) ||
		pointInsideHexahedron(tri.v1, hex) ||
		pointInsideHexahedron(tri.v2, hex)) return true;

	// Step 2: Hex faces intersect triangle
	const std::array<std::array<int, 4>, 6> faces = { {
		{0,1,2,3}, {4,5,6,7}, {0,1,5,4},
		{2,3,7,6}, {1,2,6,5}, {0,3,7,4}
	} };

	for (const auto& face : faces) {
		Triangle f1 = { hex.vertices[face[0]], hex.vertices[face[1]], hex.vertices[face[2]] };
		Triangle f2 = { hex.vertices[face[0]], hex.vertices[face[2]], hex.vertices[face[3]] };
		if (segmentIntersectsTriangle(tri.v0, tri.v1, f1) ||
			segmentIntersectsTriangle(tri.v1, tri.v2, f1) ||
			segmentIntersectsTriangle(tri.v2, tri.v0, f1) ||
			segmentIntersectsTriangle(tri.v0, tri.v1, f2) ||
			segmentIntersectsTriangle(tri.v1, tri.v2, f2) ||
			segmentIntersectsTriangle(tri.v2, tri.v0, f2))
			return true;
	}

	// Step 3: Hex edge intersection
	const std::array<std::pair<int, int>, 12> edges = { {
		{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}
	} };
	for (const auto& edge : edges) {
		if (segmentIntersectsTriangle(hex.vertices[edge.first], hex.vertices[edge.second], tri))
			return true;
	}

	return false;
}

inline bool tooFar(const Triangle& tri, double dS, double x, double y, double z)
{
	double dX = XABS(tri.v0.x - x);
	double dY = XABS(tri.v0.y - y);
	double dZ = XABS(tri.v0.z - z);
	double dL = XMAX(XMAX(dX, dY), dZ);

	if (dL > dS)
		return true;
	else
		return false;
}
