#include <iostream>

template <typename T> class ContainerList {
  public:
    ContainerList() {}
    ~ContainerList() {
        for (int ii = 0; ii < size_;)
            erase(0);
    }

    explicit ContainerList(const ContainerList& container) {
        size_t sz = container.size();
        for (size_t ii = 0; ii < sz; ii++) {
            this->push_back(container[ii]);
        }
    }

    void push_back(const T& v) {
        Node* new_node = new Node(
            v); // создание нового узла и сохраняем пользовательские данные
        new_node->prev = last_; // предыдущим элементом станет последний
        new_node->next = nullptr; // следующего элемента пока нет

        if (size_ == 0)
            first_ = new_node;

        if (last_ != nullptr)
            last_->next = new_node;

        last_ = new_node; // обновляем указатель на последний
        size_++; // обновляем размер
    }

    void push_front(const T& v) {
        insert(0, v);
    }

    T pop_back(){
        T tmp_v = last_->data;
        erase(size_ - 1);
        return tmp_v;
    }

    T operator[](std::size_t index) const {
        // Проверка индекса
        if (index >= size_) {
            return 0;
        }

        Node* current = first_;
        int i = 0;
        for (current = first_; current != nullptr && i < index;
             current = current->next) {
            i++;
        }

        return ((current == nullptr) ? 0 : current->data);
    }

    bool erase(const size_t index) {
        // Проверка индекса
        if (index >= size_) {
            return false;
        }

        // Поиск позиции для удаления
        Node* current = nullptr;
        int i = 0;
        for (current = first_; current != nullptr && i < index;
             current = current->next) {
            i++;
        }

        if (current == nullptr)
            return false;
        else {
            // Удаление текущего узла
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else { // Удаляем первый элемент
                first_ = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }

            // Освобождение памяти
            current->data.~T();
            delete current;

            // Обновление размера списка
            size_--;
            return true;
        }
    }

    void insert(const size_t index, const T& v) {
        // Проверка индекса
        if (index > size_) {
            return;
        }

        Node* current = nullptr;

        // Создание нового узла
        Node* newNode = new Node(v);

        // Поиск позиции для вставки
        int i = 0;
        for (current = first_; current != nullptr && i < index;
             current = current->next) {
            i++;
        }

        if (current == nullptr)
            return;
        else {
            if (index == 0)
                first_ = newNode;

            // Вставка нового узла перед текущим узлом
            if (current->prev != nullptr)
                newNode->prev = current->prev;
            if (current != nullptr)
                newNode->next = current;

            if (index != 0)
                if (current->prev != nullptr)
                    current->prev->next = newNode;
            current->prev = newNode;

            // Обновление размера списка
            size_++;
        }
    }

    bool empty() const {
        return (size_ > 0) ? false : true;
    }

    size_t size() const {
        return size_;
    }

    ContainerList& operator=(const ContainerList &other){
        if (this == &other)
            return* this;

        size_t sz = other.size();
        for (size_t ii=0; ii < sz; ii++){
            this->push_back(other[ii]);
        }
        return *this;
    }

    bool operator==(const ContainerList& other) const {

        if (other.size() != size_)
            return false;

        Node* current = first_;
        int ii = 0;
        for (current = first_; current != nullptr && ii < size_;
                current = current->next) {

            if (other[ii] != current->data) {
                return false;
            }
            ii++;
        }

        return true;
    }

  private:
    struct Node {
        Node* prev = nullptr;
        Node* next = nullptr;
        T data{};

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* first_ = nullptr;
    Node* last_ = nullptr;
    size_t size_ = 0;
};

template <typename T> void print_container(const ContainerList<T>& container) {
    for (size_t i = 0; i < container.size(); ++i) {
        if (i != 0)
            std::cout << ' ';

        std::cout << container[i];
    }
}
