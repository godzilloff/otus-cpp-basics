#include <iostream>

template <typename T> class ContainerSerial {
  public:
    ContainerSerial() : data_(nullptr), size_(0), capacity_(0) {}
    ~ContainerSerial() {
        delete[] data_;
    }

    void push_back(const T& v) {
        check_capacity();

        data_[size_] = v; // добавление нового элемента
        size_++; // обновление информации о размере
    }

    bool insert(const size_t pos, const T& v) {
        if (pos >= size_) {
            // invalid position
            return false;
        }

        check_capacity();

        // need to move all element after 'pos' to one position to the right
        for (size_t i = size_; i > pos; --i) {
            data_[i] = data_[i - 1];
        }
        data_[pos] = v;
        size_++;
        return true;
    }

    bool erase(const size_t pos) {
        if (pos >= size_) {
            // invalid position
            return false;
        }
        // need to move all element after 'pos' to one position to the left
        for (size_t i = pos; i < size_; ++i) {
            data_[i] = data_[i + 1];
        }
        size_--;
        return true;
    }

    size_t size() const {
        return size_;
    }

    T operator[](size_t index) const {
        if (index >= size_)
            return 0; // invalid position
        else
            return data_[index];
    }

  private:
    bool check_capacity() {
        if (size_ == capacity_) {
            // Расширение массива
            capacity_ = std::max(size_t(2), capacity_ * 2);
            T* newData = new T[capacity_]; // новая область памяти

            for (int i = 0; i < size_; ++i) {
                newData[i] = data_[i]; // копирование элементов
            }
            delete[] data_;  // удаление старой области
            data_ = newData; // сохранение новой в мембер
        }
        return true;
    }

    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template <typename T>
void print_container(const ContainerSerial<T>& container) {
    for (size_t i = 0; i < container.size(); ++i) {
        if (i != 0)
            std::cout << ' ';

        std::cout << container[i];
    }
}
