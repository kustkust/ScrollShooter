#include "pch.h"
#include "Animation.h"
#include "Rectangle.h"
#include "Names.h"
#include "Clock.h"
#include "Utility.h"
#include "DataStorage.h"

Animations::Animations() {}

Animations::Animations(json& animjson) {
	load(animjson);
}

Animations::Animations(const SpriteContainer& frames_, Duration dellay) {
	for (auto& f : frames_) {
		frames.push_back({ f,dellay });
	}
	currentAnim = "default";
	tags[currentAnim].from = 0;
	tags[currentAnim].to = static_cast<int>(frames.size() - 1);
	tags[currentAnim].direction = Tag::Forward;
	currentFrame = 0;
	stop();
}

void Animations::load(json& animjson) {
	auto& texture = TextureStorage.get(dropExt(static_cast<std::string>(animjson[Name::Meta][Name::Image])));
	for (auto& frame : animjson[Name::Frames]) {
		frames.push_back({ {texture, jsonRect(frame[Name::Frame])}, Duration(frame[Name::Duration]) });
	}
	for (auto& frameTagjson : animjson[Name::Meta][Name::FrameTags]) {
		tags[frameTagjson[Name::Name]] = Tag(frameTagjson);
	}
	if (tags.empty()) {
		tags["default"] = { 0, static_cast<int>(frames.size() - 1), Tag::Forward };
	}
	currentAnim = tags.begin()->first;
	stop();
}

bool Animations::loadFromFile(const std::string& path) {
	std::ifstream fin(path);
	json animjson;
	fin >> animjson;
	fin.close();
	load(animjson);
	return true;
}

void Animations::setTimes(int times_) {
	times = times_;
}

int Animations::getTimes() const {
	return times;
}

bool Animations::finish() const {
	return times == 0;
}

void Animations::restart() {
	if (tags[currentAnim].direction == Tag::Reverse) {
		currentFrame = tags[currentAnim].to;
	} else {
		currentFrame = tags[currentAnim].from;
	}
	timer.restart(frames[currentFrame].duration);
}

void Animations::restart(int times) {
	setTimes(times);
	restart();
}

void Animations::restart(const std::string& tag) {
	setAnim(tag);
	restart();
}

void Animations::restart(const std::string& tag, int times) {
	setAnim(tag);
	setTimes(times);
	restart();
}

bool Animations::restartIfFinish(int times) {
	if (finish()) {
		restart(times);
		return true;
	}
	return false;
}

bool Animations::restartIfFinish(const std::string& tag, int times) {
	if (finish()) {
		restart(tag, times);
		return true;
	}
	return false;
}

void Animations::pause() {
	timer.pause();
}

void Animations::resume() {
	timer.restart();
}

void Animations::stop() {
	currentFrame = tags[currentAnim].from;
	if (tags[currentAnim].direction == Tag::Reverse) {
		currentFrame = tags[currentAnim].to;
	}
	timer.restart(frames[currentFrame].duration);
	timer.pause();
}

void Animations::setFrameDuration(Duration d) {
	for (auto& frame : frames) {
		frame.duration = d;
	}
}

void Animations::setCurAnimFrameDuration(Duration d) {
	setFrameDuration(currentAnim, d);
}

void Animations::setFrameDuration(const std::string& tag, Duration d) {
	auto& t = tags[tag];
	for (int i = t.from; i <= t.to; ++i) {
		frames[i].duration = d;
	}
}

void Animations::setAnimTime(Duration d) {
	d /= frames.size();
	for (auto& frame : frames) {
		frame.duration = d;
	}
}

void Animations::setCurAnimTime(Duration d) {
	setAnimTime(currentAnim, d);
}

void Animations::setAnimTime(const std::string& tag, Duration d) {
	auto& t = tags[tag];
	if (t.direction == Tag::Ping_Pong) {
		d /= static_cast<int64_t>(t.to - t.from + 1) * 2;
	} else {
		d /= static_cast<int64_t>(t.to - t.from + 1);
	}
	for (int i = t.from; i <= t.to; ++i) {
		frames[i].duration = d;
	}
}

Duration Animations::getFrameDuration() const {
	return frames.front().duration;
}

Duration Animations::getFrameDuration(const std::string& tag) const {
	auto& t = tags.at(tag);
	if (t.direction == Tag::Reverse) {
		return frames[t.to].duration;
	}
	return frames[t.from].duration;
}

Duration Animations::getAnimTime() const {
	Duration d = 0ms;
	for (auto& frame : frames) {
		d += frame.duration;
	}
	return d;
}

Duration Animations::getAnimTime(const std::string& tag) const {
	Duration d = 0ms;
	auto& t = tags.at(tag);
	for (int i = t.from; i <= t.to; ++i) {
		d += frames[i].duration;
	}
	return t.direction == Tag::Ping_Pong ? d * 2 : d;
}

void Animations::setAnim(const std::string& animName) {
	currentAnim = animName;
	currentFrame = tags[currentAnim].from;
}

void Animations::setAnim(int i) {
	setAnim(associationStr[i]);
}

void Animations::setProgress(double t) {
	auto& tag = tags[currentAnim];
	if (tag.direction == Tag::Reverse ||
		tag.direction == Tag::Ping_Pong && tag.pingPongDir == -1) {
		t = 1. - t;
	}
	currentFrame = static_cast<int>(floor((tag.to - tag.from + 1) * t)) + tag.from;
	setMin(currentFrame, tag.to);
}

void Animations::setFrame(int index) {
	currentFrame = index;
}

void Animations::setCurrentAnimFrame(int index) {
	currentFrame = tags[currentAnim].from + index;
}

void Animations::setAssociation(const std::vector<std::string>& assoc) {
	if (assoc.size() == tags.size()) {
		associationStr = assoc;
	}
}

void Animations::setAssociation(const std::map<size_t, std::string>& assoc) {
	if (assoc.size() == tags.size()) {
		associationStr.resize(tags.size());
		for (auto& a : assoc) {
			associationStr[a.first] = a.second;
		}
	}
}

MySprite& Animations::operator[](size_t index) {
	return frames[index].spr;
}

const MySprite& Animations::at(size_t index) const {
	return frames[index].spr;
}

const Animations Animations::operator[](const std::string& tagname) const {
	return getTegAnimation(tagname);
}

const Animations Animations::getTegAnimation(const std::string& tagname) const {
	Animations newAnim;
	auto& tag = tags.at(tagname);
	newAnim.currentAnim = tagname;
	for (int i = tag.from; i <= tag.to; i++) {
		newAnim.frames.push_back(frames[i]);
	}
	for (auto& tag_ : tags) {
		if (tag_.second.from >= tag.from && tag_.second.to <= tag.to) {
			newAnim.tags[tag_.first] = tag_.second;
			newAnim.tags[tag_.first].from -= tag.from;
			newAnim.tags[tag_.first].to -= tag.to;
		}
	}
	newAnim.currentAnim = tagname;
	newAnim.stop();
	return newAnim;
}

const int Animations::interact(const sf::Event& ev, const gm::Vector& pos) {
	return 0;
}

const int Animations::update() {
	if (timer.restartIfFinish(frames[currentFrame].duration)) {
		auto& tag = tags[currentAnim];
		switch (tag.direction) {
		case Tag::Forward:
			if (currentFrame < tag.to) {
				currentFrame++;
			} else {
				times -= times > 0;
				if (times == 0) {
					timer.pause();
				} else {
					currentFrame = tag.from;
				}
			}
			break;
		case Tag::Reverse:
			if (currentFrame > tag.from) {
				currentFrame--;
			} else {
				if (times > 0) {
					--times;
				}
				if (times == 0) {
					timer.pause();
				} else {
					currentFrame = tag.to;
				}
			}
			break;
		case Tag::Ping_Pong:
			currentFrame += tag.pingPongDir;
			if (currentFrame == tag.to) {
				tag.pingPongDir = -1;
			} else if (currentFrame == tag.from) {
				if (times > 0) {
					--times;
				}
				if (times == 0) {
					timer.pause();
				}
				tag.pingPongDir = 1;
			}
			break;
		}
	}
	return NothingHappend;
}

void Animations::draw(sf::RenderTarget& ren, sf::RenderStates states) const {
	ren.draw(frames[currentFrame].spr);
}

void Animations::setColor(const sf::Color& color) {
	for (auto& frame : frames) {
		frame.spr.setColor(color);
	}
}

void Animations::scale(const gm::Vector& newScale) {
	for (auto& frame : frames) {
		frame.spr.scale(newScale);
	}
}

void Animations::setScale(const gm::Vector& scale) {
	for (auto& s : frames) {
		s.spr.setScale(scale);
	}
}

const gm::Vector Animations::getScale() const {
	return frames[currentFrame].spr.getScale();
}

void Animations::setSize(const gm::Size& newSize) {
	for (auto& frame : frames) {
		frame.spr.setSize(newSize);
	}
}

const gm::Vector Animations::getSize() const {
	return frames[currentFrame].spr.getSize();
}

const gm::Rectangle Animations::getLocalBounds() const {
	return frames[currentFrame].spr.getLocalBounds();
}

void Animations::setHorizontalSide(double side_) {
	auto sc = getScale();
	setScale({ side_ * abs(sc.x),sc.y });
}

void Animations::reverseHorizontalSide() {
	setHorizontalSide(-sgn(getScale().x));
}

void Animations::setVerticalSide(double side_) {
	auto sc = getScale();
	setScale({ sc.x, side_ * abs(sc.y) });
}

void Animations::reverseVerticalSide() {
	setHorizontalSide(-sgn(getScale().y));
}

void Animations::setOrigin(const gm::Vector& pos) {
	for (auto& s : frames) {
		s.spr.setOrigin(pos);
	}
}

void Animations::setOrigin() {
	setOrigin(frames[currentFrame].spr.getSize() / 2.);
}

const gm::Coord Animations::getOrigin() const {
	return frames.front().spr.getOrigin();
}

void Animations::rotate(gm::angle a) {
	for (auto& s : frames) {
		s.spr.rotate(a);
	}
}

void Animations::setRotation(const gm::angle a) {
	for (auto& s : frames) {
		s.spr.setRotation(a);
	}
}

gm::angle Animations::getRotation() const {
	return frames.front().spr.getRotation();
}

void Animations::move(const gm::Vector& off) {
	pos += off;
	for (auto& frame : frames) {
		frame.spr.move(off);
	}
}

const gm::Vector Animations::getPosition() const {
	return pos;
}


Animations::Tag::Tag() {}

Animations::Tag::Tag(json& tagjson) :
	from(tagjson[Name::From]),
	to(tagjson[Name::To]) {
	auto& strDir = tagjson[Name::Direction];
	if (strDir == "forward") {
		direction = Forward;
	} else if (strDir == "reverse") {
		direction = Reverse;
	} else if (strDir == "ping-pong") {
		direction = Ping_Pong;
	}
}

Animations::Tag::Tag(int from, int to, decltype(direction) dir) :
	from(from), to(to), direction(dir) {}
