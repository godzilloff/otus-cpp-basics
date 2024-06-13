#include <iostream>

template <typename T> class ContainerSerial {
  public:
    ContainerSerial() : data_(nullptr), size_(0), capacity_(0) {}
    ~ContainerSerial() {
        clear();
        delete[] data_;
    }

    explicit ContainerSerial(const ContainerSerial& other) {
        if (this != &other) {
            size_ = other.size_;
            capacity_ = size_;
            data_ = new T[capacity_];

            for (size_t ii = 0; ii < size_; ii++)
                data_[ii] = other.data_[ii];
        }
    }

    explicit ContainerSerial(ContainerSerial&& other) noexcept
        : data_(std::move(other.data_)), size_(std::move(other.size_)),
          capacity_(size_) {

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    void push_back(const T& v) {
        check_capacity();

        data_[size_] = v; // добавление нового элемента
        size_++; // обновление информации о размере
    }

    void push_front(const T& v) {
        insert(0, v);
    }

    T pop_back() {
        size_--;
        return data_[size_];
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

        data_[pos].~T(); // clear element

        // need to move all element after 'pos' to one position to the left
        for (size_t i = pos; i < size_; ++i) {
            data_[i] = data_[i + 1];
        }
        size_--;
        return true;
    }

    void clear() {
        for (size_t ii = 0; ii < size_; ii++)
            data_[ii].~T();
    }

    bool empty() const {
        return (size_ > 0) ? false : true;
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

    ContainerSerial& operator=(const ContainerSerial& other) {
        if (this != &other) {
            if (size_ > 0)
                delete data_;

            size_ = other.size();
            capacity_ = size_;
            T* newData = new T[capacity_]; // новая область памяти

            for (int i = 0; i < size_; ++i) {
                newData[i] = other.data_[i]; // копирование элементов
            }
            data_ = newData; // сохранение новой в мембер
        }
        return *this;
    }

    ContainerSerial& operator=(ContainerSerial&& other) noexcept {
        if (this != &other) {
            for (size_t ii = 0; ii < size_; ii++)
                data_[ii].~T();
            delete[] data_;

            data_ = std::move(other.data_);
            size_ = std::move(other.size_);
            capacity_ = size_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        return *this;
    }

    bool operator==(const ContainerSerial& other) const {

        if (other.size() != size_)
            return false;

        for (size_t ii = 0; ii < size_; ii++) {
            if (other[ii] != data_[ii]) {
                return false;
            }
        }

        return true;
    }

  private:
    bool check_capacity() {
        if (size_ == capacity_) {
            // Расширение массива
            capacity_ = std::max(size_t(2), capacity_ * 2);
            T* newData = new T[capacity_]; // новая область памяти

            for (int i = 0; i < size_; ++i)
                newData[i] = data_[i]; // копирование элементов

            for (size_t ii = 0; ii < size_; ii++)
                data_[ii].~T();

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
