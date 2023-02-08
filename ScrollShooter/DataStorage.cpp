#include "pch.h"
#include "DataStorage.h"

DataStorage<sf::Texture>TextureStorage("res/", ".png");
DataStorage<Animations>AnimationStorage("res/", ".json");
DataStorage<sf::SoundBuffer>SoundBufferStorage("res/", ".wav");
DataStorage<sf::Sound>SoundStorage("", "", [](sf::Sound& sound, const std::string& path)->bool {
	sound.setBuffer(SoundBufferStorage.get(path)); return true; });
DataStorage<MySprite>SpriteStorage("", "");
