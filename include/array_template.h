#pragma once
#include <memory>
#include <stdexcept>

template <class T>
class Array {
private:
    size_t capacity;
    size_t count;
    std::shared_ptr<T[]> data;
    
public:
    Array() : capacity(0), count(0), data(nullptr) {}
    
    explicit Array(size_t cap) : capacity(cap), count(0), data(std::shared_ptr<T[]>(new T[cap])) {}
    
    void Push(const T& item) {
        if (count >= capacity) {
            Resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[count++] = item;
    }
    
    void Push(T&& item) {
        if (count >= capacity) {
            Resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[count++] = std::move(item);
    }
    
    void Remove(size_t index) {
        if (index >= count) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < count - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --count;
    }
    
    T& operator[](size_t index) {
        if (index >= count) throw std::out_of_range("Index out of range");
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= count) throw std::out_of_range("Index out of range");
        return data[index];
    }
    
    size_t Size() const { return count; }
    size_t Capacity() const { return capacity; }
    
private:
    void Resize(size_t new_capacity) {
        std::shared_ptr<T[]> new_data(new T[new_capacity]);
        for (size_t i = 0; i < count; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = new_data;
        capacity = new_capacity;
    }
};
