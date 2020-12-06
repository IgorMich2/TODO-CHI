#include <iostream>
#include <utility>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <functional>

namespace list{
	TodoList& TodoList::operator=(const TodoList& other) {
		if (this == &other) {
			return *this;
		}

		this->mItems = new item_type[other.mCapacity];
		this->mCapacity = other.mCapacity;

		std::copy(other.mItems, other.mItems + other.mSize, this->mItems);
		this->mSize = other.mSize;

		return *this;
	}
	
	template<typename... Args>

	void TodoList::addItem(Args &&... args) {
		if (mSize >= mCapacity) {
			grow();
		}

		*end() = TodoItem{ std::forward<Args>(args)... };
		++mSize;
	}
	void TodoList::addItem(TodoItem item) {
		if (mSize >= mCapacity) {
			grow();
		}

		*end() = std::move(item);
		++mSi
		ze;
	}
	
	void TodoList::grow() {
		size_type new_capacity = mCapacity != 0 ? GROW(mCapacity) : 1;
		mItems = new item_type[new_capacity];
		mCapacity = new_capacity;
	}
}