#include <iostream>
#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class CustomContainer {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = size_t;
    using iterator = T*;

    CustomContainer(size_t initial_capacity = 10)
        : capacity(initial_capacity), size(0), allocator(Allocator()) {
        data = allocator.allocate(capacity);
    }

    ~CustomContainer() {
        clear();
        allocator.deallocate(data, capacity);
    }

    void push_back(const T& value) {
        if (size == capacity) {
            // Расширение
            reserve(capacity * 2);
        }
        allocator.construct(data + size, value);
        ++size;
    }

    size_type getSize() const { return size; }
    bool empty() const { return size == 0; }

    iterator begin() { return data; }
    iterator end() { return data + size; }

    void clear() {
        for (size_t i = 0; i < size; ++i) {
            allocator.destroy(data + i);
        }
        size = 0;
    }

private:
    void reserve(size_t new_capacity) {
        T* new_data = allocator.allocate(new_capacity);

        for (size_t i = 0; i < size; ++i) {
            allocator.construct(new_data + i, std::move(data[i]));
            allocator.destroy(data + i);
        }

        allocator.deallocate(data, capacity);
        data = new_data;
        capacity = new_capacity;
    }

    T* data;
    size_type capacity;
    size_type size;
    Allocator allocator;
};
