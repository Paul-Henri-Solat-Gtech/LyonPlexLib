#pragma once

#include <cmath>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>
#include <fstream> 
#include <filesystem>
#include <debugapi.h>


namespace Utils
{

	// ----------------------------------------
	// 1. Maths
	// ----------------------------------------

	constexpr float PI = 3.14159265358979323846f;



	// Fonction de limitation (fourchette de valeurs)
	inline float clamp(float v, float minVal, float maxVal)
	{
		return (v < minVal) ? minVal : (v > maxVal) ? maxVal : v;
	}
	template<typename T>
	constexpr T clamp(const T& v, const T& minVal, const T& maxVal) {
		return (v < minVal) ? minVal : (v > maxVal) ? maxVal : v;
	}


	// Interpolation lineaire
	inline float lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}
	template<typename T>
	constexpr T lerp(const T& a, const T& b, float t) {
		return static_cast<T>(a + (b - a) * t);
	}

	inline float smoothstep(float edge0, float edge1, float x)
	{
		// Ajuste x dans [0,1]
		float t = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
		// Fonction specifique smooth
		return t * t * (3.0f - 2.0f * t);
	}

	inline float degToRad(float degrees)
	{
		return degrees * (PI / 180.0f);
	}

	inline float radToDeg(float radians)
	{
		return radians * (180.0f / PI);
	}

	// Creation du "generateur aleatoire" necessaire ・la generation de nombres aleatoires
	static std::mt19937& rng()
	{
		static std::mt19937 s_rng{ std::random_device{}() };
		return s_rng;
	}

	// Utilisation du "generateur aleatoire" rng() pour FLOAT
	inline float randomFloat(float minVal = 0.0f, float maxVal = 1.0f)
	{
		std::uniform_real_distribution<float> dist(minVal, maxVal);
		return dist(rng());
	}

	// Utilisation du "generateur aleatoire" rng() pour FLOAT
	inline int randomInt(int minVal, int maxVal)
	{
		std::uniform_int_distribution<int> dist(minVal, maxVal);
		return dist(rng());
	}


	// ----------------------------------------
	// 2. Operations sur vecteurs simples (exemple Vec3)
	// ----------------------------------------
	struct Vector3
	{
		float x;
		float y;
		float z;

		// Constructors
		Vector3() : x(0), y(0), z(0) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		// Unary minus
		Vector3 operator-() const {
			return Vector3(-x, -y, -z);
		}

		// Addition
		Vector3 operator+(const Vector3& other) const {
			return Vector3(x + other.x, y + other.y, z + other.z);
		}
		Vector3& operator+=(const Vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		// Subtraction
		Vector3 operator-(const Vector3& other) const {
			return Vector3(x - other.x, y - other.y, z - other.z);
		}
		Vector3& operator-=(const Vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		// Scalar multiplication
		Vector3 operator*(float scalar) const {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}
		Vector3& operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		// Scalar division
		Vector3 operator/(float scalar) const {
			return Vector3(x / scalar, y / scalar, z / scalar);
		}
		Vector3& operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		// Dot product
		float dot(const Vector3& other) const {
			return x * other.x + y * other.y + z * other.z;
		}

		// Cross product
		Vector3 cross(const Vector3& other) const {
			return Vector3(
				y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x
			);
		}

		// Length (magnitude)
		float length() const {
			return std::sqrt(x * x + y * y + z * z);
		}

		// Normalize (in-place)
		Vector3& normalize() {
			float len = length();
			if (len > 0.0f) {
				(*this) /= len;
			}
			return *this;
		}

		// Return normalized copy
		Vector3 normalized() const {
			float len = length();
			if (len > 0.0f) {
				return *this / len;
			}
			return Vector3();
		}

		// Static zero vector
		static Vector3 zero() {
			return Vector3(0, 0, 0);
		}

		// Static unit vectors
		static Vector3 unitX() { return Vector3(1, 0, 0); }
		static Vector3 unitY() { return Vector3(0, 1, 0); }
		static Vector3 unitZ() { return Vector3(0, 0, 1); }
	};

	inline Vector3 operator*(float scalar, const Vector3& v) {
		return v * scalar;
	}

	// Produit scalaire
	inline float dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	// Produit vectoriel
	inline Vector3 cross(const Vector3& a, const Vector3& b)
	{
		return Vector3
		{
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		};
	}

	// ----------------------------------------
	// 3. Gestion de fichiers (exemple basique)
	// ----------------------------------------
	inline bool fileExists(const std::string& path)
	{
		return std::filesystem::exists(path);
	}

	inline std::string getFileName(const std::string& fullPath)
	{
		return std::filesystem::path(fullPath).filename().string();
	}

	inline std::string getExtension(const std::string& fullPath)
	{
		return std::filesystem::path(fullPath).extension().string();
	}

	// Lecture simple d置n fichier texte (retrourne un string complet)
	inline bool readFileToString(const std::string& path, std::string& out)
	{
		if (!fileExists(path)) return false;
		std::ifstream file(path, std::ios::in | std::ios::binary);
		if (!file) return false;
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		file.seekg(0, std::ios::beg);
		out.resize(size);
		file.read(&out[0], size);
		file.close();
		return true;
	}

	// ----------------------------------------
	// 4. Temps / horloge
	// ----------------------------------------
	inline double getTimeSeconds()
	{
		using namespace std::chrono;
		static auto start = high_resolution_clock::now();
		auto now = high_resolution_clock::now();
		duration<double> elapsed = now - start;
		return elapsed.count();
	}

	inline uint64_t getTimeMillis()
	{
		using namespace std::chrono;
		static auto start = high_resolution_clock::now();
		auto now = high_resolution_clock::now();
		auto elapsed = duration_cast<milliseconds>(now - start);
		return static_cast<uint64_t>(elapsed.count());
	}

	// ----------------------------------------
	// 5. Logging basique
	// ----------------------------------------
	enum class LogLevel { Info, Warning, Error };

	inline void log(const std::string& msg, LogLevel level = LogLevel::Info)
	{
		std::string lvl = "";
		switch (level) {
		case LogLevel::Info:
			lvl = "[INFO] ";
			break;
		case LogLevel::Warning:
			lvl = "[WARNING] ";
			break;
		case LogLevel::Error:
			lvl = "[ERROR] ";
			break;
		}
		OutputDebugStringA((lvl + msg + "\n").c_str());
	}

	// ----------------------------------------
	// 6. Transform
	// ----------------------------------------

	/// Ajoute (accredite) ・la rotation actuelle un increment defini
	/// par trois angles Euler (en degres) autour des axes X (pitch), Y (yaw), Z (roll).

	// AddRotation<TransformComponent>(tComp, a, b, c)
	template<typename T>
	inline void AddRotation(T& t, float deltaPitchDeg, float deltaYawDeg, float deltaRollDeg)
	{
		// 1) Convertir l'increment d'angles en radians
		float p = XMConvertToRadians(deltaPitchDeg);
		float y = XMConvertToRadians(deltaYawDeg);
		float r = XMConvertToRadians(deltaRollDeg);

		// 2) Construire le quaternion de l'increment de rotation
		//    (equivalent ・"tourner p autour de X, puis y autour de Y, puis r autour de Z")
		XMVECTOR incQv = XMQuaternionRotationRollPitchYaw(p, y, r);

		// 3) Charger le quaternion actuel (x,y,z,w) dans un XMVECTOR
		XMVECTOR curQv = XMLoadFloat4(&t.rotation);

		// 4) Composer les deux quaternions : newQ = incQ * curQ
		//    (l'ordre importe : ici on applique incQ **avant** la rotation actuelle,
		//     ce qui correspond ・un repere local).
		XMVECTOR newQv = XMQuaternionMultiply(incQv, curQv);

		// 5) Normaliser (eviter la derive numerique)
		newQv = XMQuaternionNormalize(newQv);

		// 6) Stocker de retour dans le composant
		XMStoreFloat4(&t.rotation, newQv);

		// 7) Marquer comme dirty pour que le TransformSystem recalcule la matrice monde
		t.dirty = true;
	}

	// SetRotation<TransformComponent>(tComp, a, b, c)
	template<typename T>
	inline void SetRotation(T& t, float pitchDeg, float yawDeg, float rollDeg)
	{
		float p = XMConvertToRadians(pitchDeg);
		float y = XMConvertToRadians(yawDeg);
		float r = XMConvertToRadians(rollDeg);
		XMVECTOR qv = XMQuaternionRotationRollPitchYaw(p, y, r);
		XMStoreFloat4(&t.rotation, qv);
		t.dirty = true;
	}




	// ----------------------------------------
	// 7. (ﾉventuel) Extensions futures・
	// ----------------------------------------
	// Vous pouvez ajouter ici : gestion des threads, alignement memoire, etc.
}

