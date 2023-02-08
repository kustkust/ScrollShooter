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
	Animations(const SpriteContainer& frames, duration dellay);

	void load(json& animjson);
	bool loadFromFile(const std::string& path);

	const Animations getTegAnimation(const std::string& tagnaem) const;
	const Animations operator[](const std::string& tagname) const;

	void start();
	void stop();
	void pause();
	void restart();

	void setAnim(const std::string& animName);
	void setAnim(int i);
	void setProgress(double t);

	void setFrame(int index);
	void setCurrentAnimFrame(int index);

	void setAssociation(const std::vector<std::string>& assoc);
	void setAssociation(const std::map<size_t, std::string>& assoc);

	void scale(const gm::Vector& newScale) override;
	void setScale(const gm::Vector& scale);
	const gm::Vector getScale()const;

	void setSize(const gm::Size& newSize) override;
	virtual const gm::Vector getSize() const override;

	void setHorizontalSide(double side_);
	void reverseHorizontalSide();
	void setVerticalSide(double side_);
	void reverseVerticalSide();

	void setOrigin(const gm::Vector& pos);
	void setOrigin();

	void rotate(gm::angle a);
	void setRotation(const gm::angle a);

	void setColor(const sf::Color& color);

	// ������������ ����� BaseScreenObject
	virtual void draw(sf::RenderTarget& ren, sf::RenderStates states) const override;

	virtual void move(const gm::Vector& off) override;
	virtual const gm::Vector getPosition() const override;

	virtual const int interact(const sf::Event& ev, const gm::Vector& pos = gm::NV) override;
	virtual const int update() override;

	void setTimes(int times_);
	int getTimes() const;
	bool finish() const;

	MySprite& operator[](size_t index);
	const MySprite& at(size_t index)const;
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
		duration duration;
	};
	std::vector<AnimFrame>frames{};
	int currentFrame{};
	BackTimer timer = BackTimer(0ms, BaseScreenObject::defaultInterfaceClock);
	std::string currentAnim{};
	std::map<std::string, Tag>tags{};
	std::vector<std::string>associationStr{};
	gm::Coord pos{};
	int times = -1; // how many times prefoem animation, -1 for inf
};
