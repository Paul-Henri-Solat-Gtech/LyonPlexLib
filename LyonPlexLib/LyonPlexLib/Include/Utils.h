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

	inline float sqr(float x) { return x * x; }

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

	// Creation du "generateur aleatoire" necessaire ÅEla generation de nombres aleatoires
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
	struct Vector2
	{
		float x;
		float y;
		float z;

		// Constructors
		Vector2() : x(0), y(0) {}
		Vector2(float x, float y) : x(x), y(y) {}

		// Unary minus
		Vector2 operator-() const {
			return Vector2(-x, -y);
		}

		// Addition
		Vector2 operator+(const Vector2& other) const {
			return Vector2(x + other.x, y + other.y);
		}
		Vector2& operator+=(const Vector2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		// Subtraction
		Vector2 operator-(const Vector2& other) const {
			return Vector2(x - other.x, y - other.y);
		}
		Vector2& operator-=(const Vector2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		// Scalar multiplication
		Vector2 operator*(float scalar) const {
			return Vector2(x * scalar, y * scalar);
		}
		Vector2& operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}

		// Scalar division
		Vector2 operator/(float scalar) const {
			return Vector2(x / scalar, y / scalar);
		}
		Vector2& operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
			return *this;
		}

		// Dot product
		float dot(const Vector2& other) const {
			return x * other.x + y * other.y;
		}

		// Length (magnitude)
		float length() const {
			return std::sqrt(x * x + y * y);
		}

		// Normalize (in-place)
		Vector2& normalize() {
			float len = length();
			if (len > 0.0f) {
				(*this) /= len;
			}
			return *this;
		}

		// Return normalized copy
		Vector2 normalized() const {
			float len = length();
			if (len > 0.0f) {
				return *this / len;
			}
			return Vector2();
		}

		// Static zero vector
		static Vector2 zero() {
			return Vector2(0, 0);
		}

		// Static unit vectors
		static Vector2 unitX() { return Vector2(1, 0); }
		static Vector2 unitY() { return Vector2(0, 1); }
	};

	inline Vector2 operator*(float scalar, const Vector2& v) {
		return v * scalar;
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

	// Lecture simple díun fichier texte (retrourne un string complet)
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

	/// Ajoute (accredite) ÅEla rotation actuelle un increment defini
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
		//    (equivalent ÅE"tourner p autour de X, puis y autour de Y, puis r autour de Z")
		XMVECTOR incQv = XMQuaternionRotationRollPitchYaw(p, y, r);

		// 3) Charger le quaternion actuel (x,y,z,w) dans un XMVECTOR
		XMVECTOR curQv = XMLoadFloat4(&t.rotation);

		// 4) Composer les deux quaternions : newQ = incQ * curQ
		//    (l'ordre importe : ici on applique incQ **avant** la rotation actuelle,
		//     ce qui correspond Åa un repere local).
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

	inline bool IsAbove(const TransformComponent& a, const TransformComponent& b)
	{
		// Calcul des bornes pour l'objet A (haut et bas en Y)
		float aMinY = a.position.y - a.scale.y / 2;

		// Calcul des bornes pour l'objet B
		float bMaxY = b.position.y + b.scale.y / 2;

		// Verification du chevauchement en X et Z (necessaire pour qu'on considere "au-dessus")
		float aMinX = a.position.x - a.scale.x / 2;
		float aMaxX = a.position.x + a.scale.x / 2;
		float aMinZ = a.position.z - a.scale.z / 2;
		float aMaxZ = a.position.z + a.scale.z / 2;

		float bMinX = b.position.x - b.scale.x / 2;
		float bMaxX = b.position.x + b.scale.x / 2;
		float bMinZ = b.position.z - b.scale.z / 2;
		float bMaxZ = b.position.z + b.scale.z / 2;

		bool overlapX = (aMaxX > bMinX) && (aMinX < bMaxX);
		bool overlapZ = (aMaxZ > bMinZ) && (aMinZ < bMaxZ);

		if (!(overlapX && overlapZ))
			return false;

		// Calcul de la penetration verticale entre la face inferieure de A et la face superieure de B
		float penetrationY = aMinY - bMaxY;

		// Definir un seuil epsilon (ajustable en fonction de l'echelle de vos objets)
		const float epsilon = 1.0f;

		// Retourne true si la penetration est quasi nulle (touchant)
		return (a.position.y > b.position.y && penetrationY <= 0 /*&& abs(penetrationY) < epsilon*/);
	}


	inline bool IsBelow(const TransformComponent& a, const TransformComponent& b)
	{
		// Calcul des bornes pour l'objet A (haut et bas en Y)
		float aMaxY = a.position.y + a.scale.y / 2;

		// Calcul des bornes pour l'objet B
		float bMinY = b.position.y - b.scale.y / 2;

		// Verification du chevauchement en X et Z (necessaire pour qu'on considere "au-dessus")
		float aMinX = a.position.x - a.scale.x / 2;
		float aMaxX = a.position.x + a.scale.x / 2;
		float aMinZ = a.position.z - a.scale.z / 2;
		float aMaxZ = a.position.z + a.scale.z / 2;

		float bMinX = b.position.x - b.scale.x / 2;
		float bMaxX = b.position.x + b.scale.x / 2;
		float bMinZ = b.position.z - b.scale.z / 2;
		float bMaxZ = b.position.z + b.scale.z / 2;

		bool overlapX = (aMaxX > bMinX) && (aMinX < bMaxX);
		bool overlapZ = (aMaxZ > bMinZ) && (aMinZ < bMaxZ);

		if (!(overlapX && overlapZ))
			return false;

		// Calcul de la penetration verticale entre la face inferieure de A et la face superieure de B
		float penetrationY = bMinY - aMaxY;

		// Definir un seuil epsilon (ajustable en fonction de l'echelle de vos objets)
		const float epsilon = 1.0f;

		// Retourne true si la penetration est quasi nulle (touchant)
		return (a.position.y < b.position.y && penetrationY <= 0 /*&& abs(penetrationY) < epsilon*/);
	}

	inline bool IsStandingOnOBB(
		TransformComponent const& tPlayer,        // transform du joueur
		AABBCollider     const& playerAabb,       // demi?tailles du joueur (AABB)
		TransformComponent const& tObb,           // transform de líobjet sol
		OBBCollider      const& obb,              // donnÈes OBB (halfSize, offset, orientation)
		float              maxDistance = 0.1f,
		float              maxSlopeDeg = 45.0f)
	{
		// 1) Origine du rayon : placer juste sous les pieds du joueur
		//    on prend la position Y du joueur, moins sa demi?hauteur AABB
		XMVECTOR origin = XMVectorSet(
			tPlayer.position.x,
			tPlayer.position.y - playerAabb.halfSize.y,
			tPlayer.position.z,
			1.0f
		);
		XMVECTOR dir = XMVectorSet(0, -1, 0, 0);

		// 2) Calculer le centre monde de líOBB
		//    obb.offset est expressÈ en local?: on le tourne puis on líajoute ‡ tObb.position
		XMVECTOR obbCenter = XMLoadFloat3(&tObb.position)
			+ XMVector3Rotate(XMLoadFloat3(&obb.offset),
				XMLoadFloat4(&obb.orientation));

		// 3) Passer le rayon en espace local de líOBB
		XMVECTOR q = XMLoadFloat4(&obb.orientation);
		q = XMQuaternionNormalize(q);
		XMVECTOR iq = XMQuaternionInverse(q);

		XMVECTOR localO = XMVector3Rotate(origin - obbCenter, iq);
		XMVECTOR localD = XMVector3Rotate(dir, iq);

		// 4) Slab?method pour box centrÈe ‡ líorigine locale
		float tMin = 0.0f, tMax = maxDistance;
		XMVECTOR faceN = XMVectorZero();
		for (int i = 0; i < 3; ++i) {
			float o = ((float*)&localO)[i];
			float d = ((float*)&localD)[i];
			float h = ((float*)&obb.halfSize)[i];

			if (fabs(d) < 1e-6f) {
				// rayon parallËle aux plans i : síil est hors tranche, pas díintersection
				if (o < -h || o > +h) return false;
			}
			else {
				float t1 = (-h - o) / d;
				float t2 = (+h - o) / d;
				if (t1 > t2) std::swap(t1, t2);
				if (t1 > tMin) {
					tMin = t1;
					// normale locale de la face touchÈe sur líaxe i
					XMVECTOR n = XMVectorZero();
					((float*)&n)[i] = (d > 0 ? -1.0f : +1.0f);
					faceN = n;
				}
				tMax = (((tMax) < (t2)) ? (tMax) : (t2));
				if (tMin > tMax) return false;
			}
		}
		// pas de sol si intersection hors de [0,maxDistance]
		if (tMin < 0.0f || tMin > maxDistance) return false;

		// 5) Tester la pente ? maxSlopeDeg
		XMVECTOR normalW = XMVector3Rotate(faceN, q);
		float cosA = XMVectorGetY(normalW);
		float minCos = cosf(XMConvertToRadians(maxSlopeDeg));
		return cosA >= minCos;
	}

	inline DirectX::XMVECTOR ResolveAabbAabbCollider(
		DirectX::XMFLOAT3 p1, AABBCollider const& a1,
		DirectX::XMFLOAT3 p2, AABBCollider const& a2)
	{
		using namespace DirectX;
		// calcule les centres prenant en compte offsets
		float x1 = p1.x + a1.offset.x, y1 = p1.y + a1.offset.y, z1 = p1.z + a1.offset.z;
		float x2 = p2.x + a2.offset.x, y2 = p2.y + a2.offset.y, z2 = p2.z + a2.offset.z;

		// distances centre?‡?centre
		float dx = x2 - x1, dy = y2 - y1, dz = z2 - z1;
		float px = (a1.halfSize.x + a2.halfSize.x) - std::abs(dx);
		float py = (a1.halfSize.y + a2.halfSize.y) - std::abs(dy);
		float pz = (a1.halfSize.z + a2.halfSize.z) - std::abs(dz);

		// si pas de recouvrement, retourne zÈro
		if (px <= 0 || py <= 0 || pz <= 0)
			return XMVectorZero();

		// trouve líaxe de pÈnÈtration minimale
		if (px < py && px < pz) {
			// on repousse selon X
			return XMVectorSet((dx < 0 ? -px : px), 0, 0, 0);
		}
		else if (py < pz) {
			// on repousse selon Y
			return XMVectorSet(0, (dy < 0 ? -py : py), 0, 0);
		}
		else {
			// on repousse selon Z
			return XMVectorSet(0, 0, (dz < 0 ? -pz : pz), 0);
		}
	}

	inline XMVECTOR ResolveAABBCollision(const TransformComponent& a, const TransformComponent& b)
	{
		// Calculer les bornes pour lobjet A
		float aMinX = a.position.x - a.scale.x / 2;
		float aMaxX = a.position.x + a.scale.x / 2;
		float aMinY = a.position.y - a.scale.y / 2;
		float aMaxY = a.position.y + a.scale.y / 2;
		float aMinZ = a.position.z - a.scale.z / 2;
		float aMaxZ = a.position.z + a.scale.z / 2;

		// Calculer les bornes pour lobjet B
		float bMinX = b.position.x - b.scale.x / 2;
		float bMaxX = b.position.x + b.scale.x / 2;
		float bMinY = b.position.y - b.scale.y / 2;
		float bMaxY = b.position.y + b.scale.y / 2;
		float bMinZ = b.position.z - b.scale.z / 2;
		float bMaxZ = b.position.z + b.scale.z / 2;

		// Calcul des profondeurs de penetration sur chaque axe
		// On calcule combien lobjet B setend au dela de lobjet A sur chaque cote
		float penX1 = bMaxX - aMinX; // penetration si B est a droite de A
		float penX2 = aMaxX - bMinX; // penetration si A est a droite de B

		float penY1 = bMaxY - aMinY;
		float penY2 = aMaxY - bMinY;

		float penZ1 = bMaxZ - aMinZ;
		float penZ2 = aMaxZ - bMinZ;

		// On prend la penetration minimale pour chaque axe
		float penX = (penX1 < penX2) ? penX1 : penX2;
		float penY = (penY1 < penY2) ? penY1 : penY2;
		float penZ = (penZ1 < penZ2) ? penZ1 : penZ2;

		// On trouve l'axe ou la penetration est la moins importante
		float minPenetration = penX;
		DirectX::XMVECTOR correction = DirectX::XMVectorSet((penX1 < penX2 ? -penX1 : penX2), 0.0f, 0.0f, 0.0f);

		if (penY < minPenetration)
		{
			minPenetration = penY;
			correction = DirectX::XMVectorSet(0.0f, (penY1 < penY2 ? -penY1 : penY2), 0.0f, 0.0f);
		}
		if (penZ < minPenetration)
		{
			minPenetration = penZ;
			correction = DirectX::XMVectorSet(0.0f, 0.0f, (penZ1 < penZ2 ? -penZ1 : penZ2), 0.0f);
		}

		// On peut choisir d'appliquer la moitie de la correction a chaque objet
		//DirectX::XMVECTOR correction = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		return DirectX::XMVectorScale(correction, 1.f);
	}


	inline XMVECTOR ResolveObbCollision(XMFLOAT3 p1, OBBCollider b1, XMFLOAT3 p2, OBBCollider b2) {

		// 1. Normalisation quaternion + matrice
		XMVECTOR q1 = XMLoadFloat4(&b1.orientation);
		q1 = XMQuaternionNormalize(q1);
		XMMATRIX M1 = XMMatrixRotationQuaternion(q1);

		XMVECTOR q2 = XMLoadFloat4(&b2.orientation);
		q2 = XMQuaternionNormalize(q2);
		XMMATRIX M2 = XMMatrixRotationQuaternion(q2);

		// 2. Extraction DES COLONNES comme axes locaux
		XMVECTOR A[3];
		A[0] = XMVector3TransformNormal(XMVectorSet(1, 0, 0, 0), M1);
		A[1] = XMVector3TransformNormal(XMVectorSet(0, 1, 0, 0), M1);
		A[2] = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), M1);

		XMVECTOR B[3];
		B[0] = XMVector3TransformNormal(XMVectorSet(1, 0, 0, 0), M2);
		B[1] = XMVector3TransformNormal(XMVectorSet(0, 1, 0, 0), M2);
		B[2] = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), M2);

		// matrice des dot products et valeurs absolues (+epsilon)
		float R_[3][3], AbsR[3][3];
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				R_[i][j] = XMVectorGetX(XMVector3Dot(A[i], B[j]));
				AbsR[i][j] = std::abs(R_[i][j]) + 1e-6f;
			}
		}

		// 3. Calcul des centres (offset tournÈ par le quaternion normalisÈ)
		XMVECTOR C1 = XMLoadFloat3(&p1) + XMVector3Rotate(XMLoadFloat3(&b1.offset), q1);
		XMVECTOR C2 = XMLoadFloat3(&p2) + XMVector3Rotate(XMLoadFloat3(&b2.offset), q2);

		// vecteur distance projetÈ sur A[]
		XMVECTOR tvec = C2 - C1;
		float t[3] = {
			XMVectorGetX(XMVector3Dot(tvec, A[0])),
			XMVectorGetX(XMVector3Dot(tvec, A[1])),
			XMVectorGetX(XMVector3Dot(tvec, A[2]))
		};

		float minDepth = FLT_MAX;
		XMVECTOR minAxis = XMVectorZero();

		auto testAxis = [&](XMVECTOR axis, float ra, float rb, float tVal) {
			float depth = ra + rb - std::abs(tVal);
			// on ignore toute "sÈparation" nÈgative, sans quitter la boucle
			if (depth <= 0.0f) return true;

			// mise ‡ jour du MTV
			if (depth < minDepth) {
				minDepth = depth;
				// s'assurer qu'on stocke un axe unitaire
				axis = XMVector3Normalize(axis);
				minAxis = (tVal < 0 ? -axis : axis);
			}
			return true;
			};

		struct AxisInfo { std::string name; float ra, rb, depth; };
		std::vector<AxisInfo> infos;

		// 1ñ3 : axes A0..A2
		for (int i = 0; i < 3; ++i) {
			XMVECTOR axis = A[i];
			float ra = (&b1.halfSize.x)[i];
			float rb = b2.halfSize.x * AbsR[i][0]
				+ b2.halfSize.y * AbsR[i][1]
				+ b2.halfSize.z * AbsR[i][2];

			float depth = ra + rb - std::abs(t[i]);
			infos.push_back({ "A" + std::to_string(i), ra, rb, depth });

			if (!testAxis(axis, ra, rb, t[i])) return XMVectorZero();
		}
		// 4ñ6 : axes B0..B2
		for (int j = 0; j < 3; ++j) {
			XMVECTOR axis = B[j];
			float ra = b1.halfSize.x * AbsR[0][j]
				+ b1.halfSize.y * AbsR[1][j]
				+ b1.halfSize.z * AbsR[2][j];
			float tj = XMVectorGetX(XMVector3Dot(tvec, axis));
			float rb = (&b2.halfSize.x)[j];

			float depth = ra + rb - std::abs(t[j]);
			infos.push_back({ "B" + std::to_string(j), ra, rb, depth });

			if (!testAxis(axis, ra, rb, tj)) return XMVectorZero();
		}

		// 7ñ15 : A_i ◊ B_j
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				// axe de sÈparation candidat
				XMVECTOR cross = XMVector3Cross(A[i], B[j]);

				// si cross trop petit, on l'ignore
				float axisLen = XMVectorGetX(XMVector3Length(cross));
				if (axisLen < 1e-4f) continue;
				cross = XMVectorScale(cross, 1.0f / axisLen);

				// pro≠je≠ctions
				float ra = (&b1.halfSize.x)[(i + 1) % 3] * AbsR[(i + 2) % 3][j]
					+ (&b1.halfSize.x)[(i + 2) % 3] * AbsR[(i + 1) % 3][j];
				float rb = (&b2.halfSize.x)[(j + 1) % 3] * AbsR[i][(j + 2) % 3]
					+ (&b2.halfSize.x)[(j + 2) % 3] * AbsR[i][(j + 1) % 3];

				// **attention** : on doit utiliser tij ici, pas t[i] !
				float tij = XMVectorGetX(XMVector3Dot(tvec, cross));
				float depth = ra + rb - std::abs(tij);
				infos.push_back({ "A" + std::to_string(i) + "xB" + std::to_string(j),
								  ra, rb, depth });

				//testAxis(cross, ra, rb, tij);
				if (!testAxis(cross, ra, rb, tij)) return XMVectorZero();
			}
		}

		return XMVectorScale(XMVector3Normalize(minAxis), minDepth);
	}

	inline XMVECTOR ResolveAabbObbCollision(XMFLOAT3 pa, AABBCollider a, XMFLOAT3 pb, OBBCollider b)
	{
		XMVECTOR mtv = ResolveObbCollision(
			pb, b,
			pa, OBBCollider{ a.halfSize, a.offset, {0,0,0,1} }
		);
		return XMVectorNegate(mtv);
	}


	/// Sweep test AABB moving vs static AABB.
/// @param start      Centre de l'AABB mobile en world-space.
/// @param disp       DÈplacement projetÈ de cet AABB (delta position).
/// @param mover      AABBCollider du mobile (halfSize + offset local).
/// @param tStatic    TransformComponent du AABB statique.
/// @param staticCol  AABBCollider du AABB statique.
/// @param normalOut  (sortie) normale du plan touchÈ en cas d'impact.
/// @returns t ? [0,1] du premier impact; 1.0f s'il n'y a pas de collision.
	inline float SweepAabbVsAabb(
		DirectX::XMFLOAT3           start,
		DirectX::XMFLOAT3           disp,
		AABBCollider         const& mover,
		TransformComponent   const& tStatic,
		AABBCollider         const& staticCol,
		DirectX::XMVECTOR& normalOut)
	{
		using namespace DirectX;
		// 1) Origine et dir en world
		XMVECTOR origin = XMLoadFloat3(&start);
		XMVECTOR dir = XMLoadFloat3(&disp);

		// 2) Centre monde du AABB statique
		XMVECTOR staticCenter = XMLoadFloat3(&tStatic.position)
			+ XMLoadFloat3(&staticCol.offset);

		// 3) Passage en espace local (axes alignÈs, on soustrait juste)
		XMVECTOR localO = origin - staticCenter;
		XMVECTOR localD = dir;

		// 4) …tendre la box statique des demi tailles du mobile
		XMFLOAT3 ext;
		ext.x = staticCol.halfSize.x + mover.halfSize.x;
		ext.y = staticCol.halfSize.y + mover.halfSize.y;
		ext.z = staticCol.halfSize.z + mover.halfSize.z;

		// 5) Slab method alignee
		float tMin = 0.0f;
		float tMax = 1.0f;
		bool hit = false;
		XMVECTOR faceN = XMVectorZero();

		for (int i = 0; i < 3; ++i) {

			XMFLOAT3 lo; XMStoreFloat3(&lo, localO);
			XMFLOAT3 ld; XMStoreFloat3(&ld, localD);
			XMFLOAT3 e = ext;               // dÈj‡ un XMFLOAT3

			float o = (i == 0 ? lo.x : (i == 1 ? lo.y : lo.z));
			float d = (i == 0 ? ld.x : (i == 1 ? ld.y : ld.z));
			float h = (i == 0 ? e.x : (i == 1 ? e.y : e.z));

			if (fabs(d) < 1e-6f) {
				// parallËle ? si hors intervalle, pas d'intersection
				if (o < -h || o > +h) {
					normalOut = XMVectorZero();
					return 1.0f;
				}
			}
			else {
				float t1 = (-h - o) / d;
				float t2 = (+h - o) / d;
				if (t1 > t2) std::swap(t1, t2);
				if (t1 > tMin) {
					tMin = t1;
					// normale locale sur l'axe i
					XMVECTOR n = XMVectorZero();
					//reinterpret_cast<float*>(&n)[i] = (d > 0 ? -1.0f : +1.0f);
					if (i == 0) n = XMVectorSet((d > 0 ? -1.f : +1.f), 0, 0, 0);
					if (i == 1) n = XMVectorSet(0, (d > 0 ? -1.f : +1.f), 0, 0);
					if (i == 2) n = XMVectorSet(0, 0, (d > 0 ? -1.f : +1.f), 0);
					faceN = n;
				}
				tMax = tMax < t2 ? tMax : t2;
				if (tMin > tMax) {
					normalOut = XMVectorZero();
					return 1.0f;
				}
				hit = true;
			}
		}

		if (!hit || tMin < 0.0f || tMin > 1.0f) {
			normalOut = XMVectorZero();
			return 1.0f;
		}

		// 6) Sortie : tMin et normale
		normalOut = faceN;  // axes alignÈs, pas besoin de retransformer
		return tMin;
	}


	/// Sweep test AABB moving vs static OBB.
/// @param start      Position centre de l'AABB au dÈbut du mouvement.
/// @param disp       DÈplacement projetÈ de l'AABB (delta position).
/// @param aabb       DonnÈes de l'AABB (demi?tailles et offset local).
/// @param tObb       TransformComponent de l'OBB (position monde).
/// @param obb        DonnÈes de l'OBB (halfSize, offset, orientation).
/// @param normalOut  (sortie) reÁoit la normale du plan touchÈ en cas d'impact.
/// @returns t ? [0,1] du premier impact; 1.0f s'il n'y a pas de collision.
	inline float SweepAabbVsObb(
		DirectX::XMFLOAT3           start,
		DirectX::XMFLOAT3           disp,
		AABBCollider         const& aabb,
		TransformComponent   const& tObb,
		OBBCollider          const& obb,
		DirectX::XMVECTOR& normalOut)
	{

		// 1) Calculer le rayon (centre de l'AABB) et le dir en world
		XMVECTOR origin = XMLoadFloat3(&start);
		XMVECTOR dir = XMLoadFloat3(&disp);

		// 2) Calculer le centre monde de l'OBB
		XMVECTOR obbCenter = XMLoadFloat3(&tObb.position)
			+ XMVector3Rotate(XMLoadFloat3(&obb.offset),
				XMLoadFloat4(&obb.orientation));

		// 3) Passage en espace LOCAL de l'OBB
		XMVECTOR q = XMLoadFloat4(&obb.orientation); q = XMQuaternionNormalize(q);
		XMVECTOR iq = XMQuaternionInverse(q);
		XMVECTOR localO = XMVector3Rotate(origin - obbCenter, iq);
		XMVECTOR localD = XMVector3Rotate(dir, iq);

		// 4) …tendre l'OBB par les demi?tailles de l'AABB
		XMFLOAT3 ext;
		ext.x = obb.halfSize.x + aabb.halfSize.x;
		ext.y = obb.halfSize.y + aabb.halfSize.y;
		ext.z = obb.halfSize.z + aabb.halfSize.z;

		// 5) Slab?method sur box centrÈe ‡ l'origine locale, demi?tailles = ext
		float tMin = 0.0f;
		float tMax = 1.0f;  // on normalise disp en [0,1]
		bool hit = false;
		XMVECTOR faceN = XMVectorZero();

		// pour chaque axe i = 0,1,2
		for (int i = 0; i < 3; ++i) {
			float o = reinterpret_cast<float*>(&localO)[i];
			float d = reinterpret_cast<float*>(&localD)[i];
			float h = reinterpret_cast<float*>(&ext)[i];

			if (fabs(d) < 1e-6f) {
				// parallËle aux faces : si hors de la tranche, pas d'intersection
				if (o < -h || o > +h) {
					normalOut = XMVectorZero();
					return 1.0f;
				}
			}
			else {
				// calcul des entrÈes/sorties
				float t1 = (-h - o) / d;
				float t2 = (+h - o) / d;
				if (t1 > t2) std::swap(t1, t2);

				// affiner tMin/tMax
				if (t1 > tMin) {
					tMin = t1;
					// normale locale de face i
					XMVECTOR n = XMVectorZero();
					reinterpret_cast<float*>(&n)[i] = (d > 0 ? -1.0f : +1.0f);
					faceN = n;
				}
				tMax = tMax < t2 ? tMax : t2;
				if (tMin > tMax) {
					normalOut = XMVectorZero();
					return 1.0f;
				}
				hit = true;
			}
		}

		// pas de collision sur la trajectoire
		if (!hit || tMin < 0.0f || tMin > 1.0f) {
			normalOut = XMVectorZero();
			return 1.0f;
		}

		// 6) Sortie : tMin (le plus petit t d'impact) et normale en monde
		normalOut = XMVector3Rotate(faceN, q);
		return tMin;
	}
}

