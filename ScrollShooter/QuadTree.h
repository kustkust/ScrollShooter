#pragma once
#include "Rectangle.h"
#include "Utility.h"

struct Test {
	Test() = default;
	Test(const Test&) = default;
	Test(Test&&) = default;
	Test(const gm::Rectangle& rect) :rect(rect) {

	}
	gm::Rectangle rect;
	gm::Rectangle getBounds() const {
		return rect;
	}
};
#if 0
using T = Test;
#else
template<class T>
#endif
class QuadTree {
public:

	/*
	* 0|1
	* ---
	* 2|3
	*/

	using GetBounds = std::function<gm::Rectangle(const T&)>;

private:
	class Node;
	struct Item;
	using Items = std::list<Item>;
	using NodeItem = Items::iterator;
	using NodeItems = std::list<NodeItem>;

public:
	class Iterator /* :public std::iterator<std::random_access_iterator_tag, T>*/ {
		friend QuadTree;
		NodeItem iter;
		Iterator(NodeItem item) :iter(item) {

		}
	public:
		using iterator_category = std::list<Item>::iterator::iterator_category;
		using value_type = T;
		using difference_type = std::list<Item>::iterator::difference_type;
		using pointer = std::list<Item>::iterator::pointer;
		using reference = std::list<Item>::iterator::reference;

		DEFAULT_CLASS(Iterator);
		bool operator==(const Iterator& other) const {
			return iter == other.iter;
		}
		bool operator!=(const Iterator& other) const {
			return iter != other.iter;
		}
		T& operator*() {
			return **iter;
		}
		const T& operator*() const {
			return **iter;
		}
		T* operator->() {
			return &**iter;
		}
		const T* operator->() const {
			return &**iter;
		}
		Iterator& operator++() {
			++iter;
			return *this;
		}
		Iterator operator++(int) {
			Iterator tmp = *this;
			iter++;
			return tmp;
		}
		Iterator& operator--() {
			--iter;
			return *this;
		}
		Iterator operator--(int) {
			Iterator tmp = *this;
			iter--;
			return tmp;
		}

	};

private:
	struct Item {
	public:
		T* operator->() {
			return &item;
		}
		T& operator*() {
			return item;
		}
		const T& operator*() const {
			return item;
		}
		T item;
		//private:
		template<class... Args>
		Item(Args... args) : item(args...) {

		}
		Item(const T& item) : item(item) {

		}
		Item(T&& item) : item(std::forward<T>(item)) {

		}
		QuadTree::NodeItems* nodeList = nullptr;
		NodeItems::iterator it;
		friend class QuadTree;
		friend class Node;
		~Item() = default;
	};

	class Node {

		int depth;
		int maxDepth;
		gm::Rectangle bounds;
		std::array<std::unique_ptr<Node>, 4> children;
		NodeItems items;

		int getContainIndex(gm::Rectangle bound) {
			auto center = bounds.getCenter();
			if (bound.getBottom() <= center.y) {
				if (bound.getRight() <= center.x) {
					return 0;
				} else if (bound.getLeft() >= center.x) {
					return 1;
				}
			} else if (bound.getTop() >= center.y) {
				if (bound.getRight() <= center.x) {
					return 2;
				} else if (bound.getLeft() >= center.x) {
					return 3;
				}
			}
			return 4;
		}

		gm::Rectangle getChildBounds(int i) {
			return (i == 0) ? gm::Rectangle{ bounds.getLeftTop(), bounds.getSize() / 2 } :
				i == 1 ? gm::Rectangle{ bounds.getTopCenter(), bounds.getSize() / 2 } :
				i == 2 ? gm::Rectangle{ bounds.getLeftCenter(), bounds.getSize() / 2 } :
				gm::Rectangle{ bounds.getCenter(), bounds.getSize() / 2 };
		}

		std::optional<NodeItem> getLast() {
			if (items.empty()) {
				return std::nullopt;
			}
			return items.back();
		}

	public:
		Node() = default;
		Node(int depth, int maxDepth, const gm::Rectangle& bounds) :
			depth(depth), maxDepth(maxDepth), bounds(bounds) {

		}

		NodeItem insert(
			const T& item, gm::Rectangle bounds, Items& list, NodeItem after
		) {
			auto ind = getContainIndex(bounds);
			if (ind == 4 || depth + 1 == maxDepth) {
				items.push_back(list.insert(after, { item }));
				items.back()->nodeList = &items;
				items.back()->it = --items.end();
				return items.back();
			}
			if (!children[ind]) {
				children[ind] = std::make_unique<Node>(depth + 1, maxDepth, getChildBounds(ind));
			}
			auto newAfter = after;
			for (int i = ind; i >= 0; --i) {
				if (children[i]) {
					if (auto tmp = children[i]->getLast()) {
						newAfter = *tmp;
						break;
					}
				}
			}
			return children[ind]->insert(item, bounds, list, newAfter);
		}


		std::pair<NodeItems*, typename NodeItems::iterator> insert(NodeItem item, gm::Rectangle bounds) {
			auto ind = getContainIndex(bounds);
			if (ind == 4 || depth == maxDepth) {
				items.push_back(item);
				return { &items, --items.end() };
			}
			if (!children[ind]) {
				children[ind] = std::make_unique<Node>(depth + 1, maxDepth, getChildBounds(ind));
			}
			return children[ind]->insert(item, bounds);
		}
		void contains(std::list<NodeItem>& result, const gm::IShape* bounds, const GetBounds& getBounds) const {
			for (auto& it : items) {
				if (getBounds(it->item).inside(bounds)) {
					result.push_back(it);
				}
			}
			for (auto& child : children) {
				if (child && bounds->collides(child->bounds)) {
					child->contains(result, bounds, getBounds);
				}
			}
		}

		void collides(NodeItems& result, gm::IShape* bounds, const GetBounds& getBounds) const {
			for (auto& it : items) {
				if (bounds->collides(getBounds(it->item))) {
					result.push_back(it);
				}
			}
			for (auto& child : children) {
				if (child && bounds->collides(child->bounds)) {
					child->collides(result, bounds, getBounds);
				}
			}
		}

		void clear() {
			items.clear();
			for (auto& child : children) {
				if (child) {
					child->clear();
					child = nullptr;
				}
			}
		}
	};

	Node root;
	Items items;
	GetBounds getBounds;
	mutable NodeItems tmpList;

	std::function<T& (NodeItem&)> transformNodeItem = [](NodeItem& item) ->T& { return **item; };
	// std::ranges::transform_view<std::ranges::ref_view<Item>, std::function<T& (Item&)>> rep;

public:
	QuadTree() = default;
	QuadTree(
		const gm::Rectangle& bounds,
		int maxDepth = 8,
		const GetBounds& getBounds = [](const T& item) {return item.getBounds(); }
	) : root(0, maxDepth, bounds), getBounds(getBounds) {

	}
	QuadTree(
		const gm::Size& size,
		int maxDepth = 8,
		const GetBounds& getBounds = [](const T& item) {return item.getBounds(); }
	) : root(0, maxDepth, { {0., 0.}, size }), getBounds(getBounds) {

	}

	Iterator pushBack(const T& item) {
		items.push_back(item);
		auto [list, it] = root.insert(--items.end(), getBounds(items.back().item));
		items.back().nodeList = list;
		items.back().it = it;
		return Iterator(--items.end());
	}

	Iterator pushBack(T&& item) {
		items.emplace_back(std::forward<T>(item));
		auto [list, it] = root.insert(--items.end(), getBounds(items.back().item));
		items.back().nodeList = list;
		items.back().it = it;
		return Iterator(--items.end());
	}

	Iterator pushFront(const T& item) {
		items.push_front(item);
		auto [list, it] = root.insert(items.begin(), getBounds(items.front().item));
		items.front().nodeList = list;
		items.front().it = it;
		return Iterator(items.begin());
	}

	Iterator pushFront(T&& item) {
		items.emplace_front(std::forward<T>(item));
		auto [list, it] = root.insert(items.begin(), getBounds(items.front().item));
		items.front().nodeList = list;
		items.front().it = it;
		return Iterator(items.begin());
	}

	template<class... Args>
	Iterator emplaceBack(Args... args) {
		items.emplace_back(args...);
		auto [list, it] = root.insert(--items.end(), getBounds(items.back().item));
		items.back().nodeList = list;
		items.back().it = it;
		return Iterator(items.begin());
	}

	Iterator erase(Iterator item) {
		item.iter->nodeList->erase(item.iter->it);
		auto res = items.erase(item.iter);
		return res;
	}

	void update(Iterator item) {
		item.iter->nodeList->erase(item.iter->it);
		auto [list, it] = root.insert(item.iter, getBounds(item.iter->item));
		item.iter->nodeList = list;
		item.iter->it = it;
	}

	void updateAll() {
		for (auto it = items.begin(); it != items.end(); ++it) {
			update(it);
		}
	}

	decltype(auto) contains(gm::IShape* bounds) {
		tmpList.clear();
		root.contains(tmpList, bounds, getBounds);
		return std::views::transform(tmpList, transformNodeItem);
	}

	decltype(auto) collide(gm::IShape* bounds) {
		tmpList.clear();
		root.collides(tmpList, bounds, getBounds);
		return std::views::transform(tmpList, transformNodeItem);
	}

	void clear() {
		items.clear();
		root.clear();
	}

	Iterator begin() {
		return items.begin();
	}

	Iterator end() {
		return items.end();
	}

};
