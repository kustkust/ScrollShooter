#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "Animation.h"

template <class T>
class DataStorage {
	std::map<std::string, T>data;
	const std::string path;
	const std::string ext;
	std::function<bool(T&, const std::string&)> loadFromFile;
public:
	DataStorage(
		const std::string& path,
		const std::string& ext,
		const std::function<bool(T&, const std::string&)>& loadFromFile =
		[](T& data, const std::string& path)->bool { return data.loadFromFile(path); }) :
		path(path), ext(ext), loadFromFile(loadFromFile) {}
	T& get(const std::string& dataName) {
		auto it = data.find(dataName);
		if (it == data.end()) {
			loadFromFile(data[dataName], path + dataName + ext);
		}
		return data[dataName];
	}
	T& operator[](const std::string& dataName) {
		return get(dataName);
	}
	void load(const std::string& dataName) {
		data[dataName].loadFromFile(path + dataName + ext);
	}
	typename std::map<std::string, T>::iterator begin() {
		return data.begin();
	}
	typename std::map<std::string, T>::iterator end() {
		return data.end();
	}
	void clear() {
		data.clear();
	}
};

extern DataStorage<sf::Texture>TextureStorage;
extern DataStorage<Animations>AnimationStorage;
extern DataStorage<MySprite>SpriteStorage;
extern DataStorage<sf::SoundBuffer>SoundBufferStorage;
extern DataStorage<sf::Sound>SoundStorage;

