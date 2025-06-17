#pragma once

class GameObject
{
public:
	void Init(const std::string& name);

	void SetName(const std::string& name) { m_name = name; };
	void SetTag(const std::string& tag) { m_tag = tag; };

	// Components
	void SetPosition();
	void GetPosition();
	void SetRotation();
	void GetRotation();

private:

	std::string m_name, m_tag;
};

