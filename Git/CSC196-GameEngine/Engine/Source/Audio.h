#pragma once
#include <fmod.hpp>
#include <map>
class Audio
{
public:
	Audio() = default;
	~Audio() = default;

	bool Initialize();
	void Shutdown();

	void Update();
	
	bool AddSound(const std::string& name);
	bool PlaySound(const std::string& name);

private:
	FMOD::System* m_audio{ nullptr };
	FMOD::map<std::string, FMOD::Sound*> m_sounds;
};