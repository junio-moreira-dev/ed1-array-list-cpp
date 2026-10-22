//
// Created by Junio Moreira on 24/09/26.
//

#ifndef ED1_ARRAY_LIST_CPP_ARRAYLIST_H
#define ED1_ARRAY_LIST_CPP_ARRAYLIST_H

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename T>
class ArrayList : public List<T> {
private:
    T* items;
    int count;
    int capacity;

    const int NOT_FOUND = -1;
    const std::string DOES_NOT_EXIST = "Position does not exist.";
    const std::string LIST_FULL = "Error: List is full!";
    const std::string LIST_EMPTY = "List is empty.";

    bool positionDoesNotExist(int position) const {
        return !(position >= 0 && position < count);
    }

public:
    explicit ArrayList(int capacity) {
        this->capacity = capacity;
        this->items = new T[this->capacity];
        this->count = 0;
    }

    // Destructor to deallocate dynamic contiguous memory
    ~ArrayList() override {
        delete[] items;
    }

    bool isFull() const {
        return count == capacity;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const override {
        return count;
    }

    // Inserts a new item at the beginning of the list (delegates to insertAt)
    void addFirst(const T& item) override {
        insertAt(0, item);
    }

    // Appends a new item to the end of the array
    void addLast(const T& item) override {
        if (isFull()) {
            std::cout << LIST_FULL << std::endl;
            return;
        }
        items[count++] = item;
    }

    // Inserts a new item at a specific index by shifting elements to the right
    void insertAt(int index, const T& item) override {
        if (isFull()) {
            std::cout << LIST_FULL << std::endl;
            return;
        }
        if (index < 0 || index > count) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }

        for (int j = count; j > index; j--) {
            items[j] = items[j - 1];
        }
        items[index] = item;
        count++;
    }

    // Inserts a new item in ascending sorted order (requires operator '<' for type T)
    void addSorted(const T& item) override {
        if (isFull()) {
            std::cout << LIST_FULL << std::endl;
            return;
        }

        int index = 0;
        while (index < count && items[index] < item) {
            index++;
        }
        insertAt(index, item);
    }

    // Removes and returns the first element of the list
    T removeFirst() override {
        return removeAt(0);
    }

    // Removes and returns the last element of the list
    T removeLast() override {
        if (isEmpty()) {
            throw std::runtime_error(LIST_EMPTY);
        }
        T removedItem = items[count - 1];
        count--;
        return removedItem;
    }

    // Removes and returns the element at a specific index by shifting elements to the left
    T removeAt(int index) override {
        if (positionDoesNotExist(index)) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }

        T removedItem = items[index];

        for (int j = index; j < count - 1; j++) {
            items[j] = items[j + 1];
        }

        count--;
        return removedItem;
    }

    // Removes the first occurrence of the specified item
    bool remove(const T& item) override {
        int position = find(item);

        if (position == NOT_FOUND) {
            return false;
        }

        removeAt(position);
        return true;
    }

    // Logically resets the list to an empty state
    void clear() override {
        count = 0;
    }

    // Performs a linear search and returns the index of the item, or NOT_FOUND (-1)
    int find(const T& item) const override {
        for (int i = 0; i < count; i++) {
            if (items[i] == item) {
                return i;
            }
        }
        return NOT_FOUND;
    }

    // Retrieves the item stored at a specific index
    T get(int index) const override {
        if (positionDoesNotExist(index)) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }
        return items[index];
    }

    // Updates the item stored at a specific index
    void set(int index, const T& item) override {
        if (positionDoesNotExist(index)) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }
        items[index] = item;
    }

    // Generates a string representation of the list in array format [item1, item2, ...]
    std::string toString() const {
        if (count == 0) {
            return "[]";
        }

        std::ostringstream builder;
        builder << "[";
        for (int i = 0; i < count; i++) {
            builder << items[i];
            if (i < count - 1) {
                builder << ", ";
            }
        }
        builder << "]";
        return builder.str();
    }
};

#endif // ED1_ARRAY_LIST_CPP_ARRAYLIST_H