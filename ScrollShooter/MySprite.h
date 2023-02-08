#pragma once
#include "BaseScreenObject.h"

//�������� ��� �������
class MySprite : public BaseScreenObject {
	sf::Sprite spr;
public:
	MySprite();
	MySprite(const sf::Texture&tex);
	MySprite(const sf::Texture&tex, const sf::IntRect&rect);
	MySprite(const sf::Texture&tex, const gm::Rectangle&rect);
	MySprite(const sf::Sprite&spr_);

	const int interact(
		const sf::Event&ev,
		const gm::Vector&pos
	) override;
	void draw(sf::RenderTarget&ren, sf::RenderStates states) const override;

	void move(const gm::Vector& off) override;
	void setPosition(const gm::Vector& pos_) override;
	const gm::Vector getPosition() const override;

	const gm::Rectangle getGlobalBounds() const override;
	void setSize(const gm::Size& newSize) override;
	const gm::Vector getSize() const override;
	const int update() override;
	operator sf::Sprite();

	bool loadFromFile(const std::string& path);

	void rotate(gm::angle ang);
	void setRotation(gm::angle angOff);
	const gm::angle getRotation()const;

	void setScale(const gm::Vector&scale);
	const gm::Vector getScale()const;
	void scale(const gm::Vector& scale_);

	void setOrigin(const gm::Vector&orig);
	const gm::Vector getOrigin()const;

	void setColor(const sf::Color& color);
};
