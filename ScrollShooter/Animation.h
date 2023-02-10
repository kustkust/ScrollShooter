#pragma once
#include "SpriteContainer.h"
#include "MySprite.h"
#include "BackTimer.h"
#include "Utility.h"

class Animations :public BaseScreenObject {
public:
	Animations();
	Animations(const Animations&) = default;
	Animations& operator=(const Animations&) = default;
	Animations(json& animjson);
	Animations(const SpriteContainer& frames, Duration dellay);

	void load(json& animjson);
	bool loadFromFile(const std::string& path);

	void setTimes(int times_);
	int getTimes() const;
	bool finish() const;
	void restart();
	void restart(int times);
	void restart(const std::string& tag);
	void restart(const std::string& tag, int times);
	bool restartIfFinish(int times = 1);
	bool restartIfFinish(const std::string& tag, int times = 1);
	void pause();
	void resume();
	void stop();

	void setFrameDuration(Duration d);
	void setCurAnimFrameDuration(Duration d);
	void setFrameDuration(const std::string& tag, Duration d);
	void setAnimTime(Duration d);
	void setCurAnimTime(Duration d);
	void setAnimTime(const std::string& tag, Duration d);

	Duration getFrameDuration() const;
	Duration getFrameDuration(const std::string& tag) const;
	Duration getAnimTime() const;
	Duration getAnimTime(const std::string& tag) const;

	void setAnim(const std::string& animName);
	void setAnim(int i);
	void setProgress(double t);

	void setFrame(int index);
	void setCurrentAnimFrame(int index);

	void setAssociation(const std::vector<std::string>& assoc);
	void setAssociation(const std::map<size_t, std::string>& assoc);

	MySprite& operator[](size_t index);
	const MySprite& at(size_t index)const;
	const Animations operator[](const std::string& tagname) const;
	const Animations getTegAnimation(const std::string& tagnaem) const;

	virtual const int interact(const sf::Event& ev, const gm::Vector& pos = gm::NV) override;
	virtual const int update() override;

	virtual void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;
	void setColor(const sf::Color& color);

	void scale(const gm::Vector& newScale) override;
	void setScale(const gm::Vector& scale);
	const gm::Vector getScale()const;

	void setSize(const gm::Size& newSize) override;
	virtual const gm::Vector getSize() const override;
	const gm::Rectangle getLocalBounds() const override;

	void setHorizontalSide(double side_);
	void reverseHorizontalSide();
	void setVerticalSide(double side_);
	void reverseVerticalSide();

	void setOrigin(const gm::Vector& pos);
	void setOrigin();
	const gm::Coord getOrigin() const;

	void rotate(gm::angle a);
	void setRotation(const gm::angle a);
	gm::angle getRotation() const;

	virtual void move(const gm::Vector& off) override;
	virtual const gm::Vector getPosition() const override;

protected:
	class Tag {
	public:
		int from{}, to{};
		enum {
			Forward,
			Reverse,
			Ping_Pong,
		}direction{};
		int pingPongDir{};
		Tag();
		Tag(json& tagjson);
		Tag(int from, int to, decltype(direction) dir);
	};
	class AnimFrame {
	public:
		MySprite spr;
		Duration duration;
	};
	std::vector<AnimFrame>frames{};
	int currentFrame{};
	BackTimer timer = BackTimer(0ms, BaseScreenObject::defaultInterfaceClock);
	std::string currentAnim{};
	std::map<std::string, Tag>tags{};
	std::vector<std::string>associationStr{};
	gm::Coord pos{};
	int times = -1; // how many times perform animation, -1 for inf
};
