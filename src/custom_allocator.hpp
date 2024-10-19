#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class CustomAllocator {
public:
    using value_type = T;
    
    CustomAllocator(size_t initial_capacity = 10)
        : capacity(initial_capacity), allocated(0) {
        data = reinterpret_cast<T*>(::operator new(capacity * sizeof(T)));
    }

    ~CustomAllocator() {
        ::operator delete(data);
    }

    template <typename U>
    CustomAllocator(const CustomAllocator<U>&) noexcept {}

    T* allocate(size_t n) {
        if (allocated + n > capacity) {
            // Расширение
            size_t new_capacity = capacity * 2;
            T* new_data = reinterpret_cast<T*>(::operator new(new_capacity * sizeof(T)));

            // Копируем старые данные
            for (size_t i = 0; i < allocated; ++i) {
                new (new_data + i) T(std::move(data[i]));
            }

            // Освобождаем старую память
            ::operator delete(data);
            data = new_data;
            capacity = new_capacity;
        }
        T* result = data + allocated;
        allocated += n;
        return result;
    }

    void deallocate(T* p, size_t n) {
        // Память поэлементно не освобождаем в упрощенном примере
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) {
        p->~U();
    }

private:
    T* data;
    size_t capacity;
    size_t allocated;
};

template <typename T, typename U>
bool operator==(const CustomAllocator<T>&, const CustomAllocator<U>&) { return true; }

template <typename T, typename U>
bool operator!=(const CustomAllocator<T>&, const CustomAllocator<U>&) { return false; }
