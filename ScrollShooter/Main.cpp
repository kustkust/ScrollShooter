#include "pch.h"
#include "Game.h"
#include "QuadTree.h"

void testQuadTree() {
	QuadTree<Test> tree({ 0,0,100,100 }, 2);
	std::string cmd;
	gm::real x, y, w, h;
	int i;
	while (true) {
		std::cin >> cmd;
		if (cmd == "i") {
			std::cin >> x >> y >> w >> h;
			tree.pushBack(Test(gm::Rectangle(x, y, w, h)));
		} else if (cmd == "l") {
			i = 0;
			/*for (auto& rect : tree) {
				std::cout << i++ << ":" << rect.rect.getPosition() << " " << rect.rect.getSize() << "\n";
			}*/
			for (auto it = tree.begin(); it != tree.end(); ++it) {
				std::cout << i++ << ":" << it->rect.getPosition() << " " << it->rect.getSize() << "\n";
			}
		} else if (cmd == "r") {
			std::cin >> i; 
			auto b = tree.begin();
			std::advance(b, i);
			tree.erase(b);
		} else if (cmd == "rf") {
			std::cin >> x >> y >> w >> h;
			gm::Rectangle rect{ x,y,w,h };
			tree.erase(tree.contains_(&rect).begin());
		} else if (cmd == "m") {
			std::cin >> i;
			std::cin >> x >> y >> w >> h;
			auto b = tree.begin();
			std::advance(b, i);
			b->rect = { x,y,w,h };
			tree.update(b);
		} else if (cmd == "cont") {
			std::cin >> x >> y >> w >> h;
			i = 0;
			gm::Rectangle rect{ x,y,w,h };
			for (auto& rect : tree.contains(&rect)) {
				std::cout << i++ << ":" << rect.rect.getPosition() << " " << rect.rect.getSize() << "\n";
			}
		} else if (cmd == "coll") {
			std::cin >> x >> y >> w >> h;
			i = 0;
			gm::Rectangle rect{ x,y,w,h };
			for (auto& rect : tree.collide(&rect)) {
				std::cout << i++ << ":" << rect.rect.getPosition() << " " << rect.rect.getSize() << "\n";
			}
		}
	}
}

struct Kek {
	int i;
};

decltype(auto) f() {
	std::list<Kek> list = { {1},{2},{3} };
	return std::views::transform(list, [](Kek& i) ->int& {return i.i; });
}

void testView() {
	std::list<Kek> list = { {1},{2},{3} };
	std::ranges::transform_view rep(list, [](Kek& i) ->int& {return i.i; });
	list.push_back({ 4 });
	for (auto&i : rep) {
		++i;
		std::cout << i;
	}
}

int main() {
	// testQuadTree();
	// testView();

	Arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	auto game = std::make_shared<Game>();
	game->init();
	game->mainLoop();
}
