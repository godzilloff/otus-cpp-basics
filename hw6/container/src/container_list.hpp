#include <iostream>

template <typename T> class ContainerList {
  private:
    struct Node;

  public:
    class iterator;
    friend class iterator; // класс итератора должен иметь доступ к полям Node

    ContainerList() {
        first_ = nullptr;
        last_ = nullptr;

        first_iterator = iterator(first_);
        last_iterator = iterator(last_);
    }

    explicit ContainerList(const ContainerList& container) {
        size_t sz = container.size();
        for (size_t ii = 0; ii < sz; ii++) {
            this->push_back(container[ii]);
        }
    }

    explicit ContainerList(ContainerList&& other) noexcept
        : first_(std::move(other.first_)), last_(std::move(other.last_)),
          size_(std::move(other.size_)),
          first_iterator(std::move(other.first_iterator)),
          last_iterator(std::move(other.last_iterator)) {

        other.first_ = nullptr;
        other.last_ = nullptr;
        other.size_ = 0;
        other.first_iterator = nullptr;
        other.last_iterator = nullptr;
    }

    ~ContainerList() {
        clear();
    }

    void clear() {
        Node* node_to_delete = first_;
        for (Node* sn = first_; sn != last_;) {
            sn = sn->next;
            node_to_delete->data.~T();
            delete node_to_delete;
            node_to_delete = sn;
        }

        delete node_to_delete;

        first_ = nullptr;
        last_ = nullptr;
        size_ = 0;
        first_iterator = nullptr;
        last_iterator = nullptr;
    }

    void push_back(const T& v) {
        Node* new_node = new Node(
            v); // создание нового узла и сохраняем пользовательские данные
        new_node->prev = last_; // предыдущим элементом станет последний
        new_node->next = nullptr; // следующего элемента пока нет

        if (size_ == 0) {
            first_ = new_node;
            first_iterator = iterator(first_);
        }

        if (last_ != nullptr)
            last_->next = new_node;

        size_++; // обновляем размер
        last_ = new_node; // обновляем указатель на последний
        last_iterator = iterator(last_->next);
    }

    void push_front(const T& v) {
        insert(0, v);
        first_iterator = iterator(first_);
    }

    T pop_front() {
        if (size_ < 1)
            return 0;

        Node* nd = first_;
        T tmp_v = nd->data;
        first_ = nd->next;

        if (first_ != nullptr) {
            first_->prev = nullptr;
        } else {
            last_ = nullptr;
        }
        first_iterator = iterator(first_);

        size_--;
        nd->data.~T();
        delete nd;
        return tmp_v;
    }

    T pop_back() {
        // T tmp_v = last_->data;
        // erase(size_ - 1);
        // return tmp_v;

        if (size_ < 1)
            return 0;

        // Node* nd = last_->prev;
        Node* nd = last_;
        if (nd->prev == nullptr)
            return pop_front();
        else {
            T tmp_v = nd->data;

            // nd->prev->next = last_;
            // last_->prev = nd->prev;
            last_ = nd->prev;
            nd->prev->next = nullptr;

            size_--;
            nd->data.~T();
            delete nd;
            return tmp_v;
        }
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
        if (index == 0)
            current = first_;
        else {
            int i = 0;
            for (current = first_; current != nullptr && i < index;
                 current = current->next) {
                i++;
            }
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

    iterator get_node(const size_t pos) const {
        if (pos == 0)
            return first_iterator;

        size_t cnt = 1;
        for (Node* nd = first_; nd != last_; nd = nd->next) {
            if (cnt++ == pos)
                return iterator(nd)
        }

        return last_iterator;
    }

    ContainerList& operator=(const ContainerList& other) {
        if (this != &other) {
            size_t sz = other.size();
            for (size_t ii = 0; ii < sz; ii++)
                this->push_back(other[ii]);
        }
        return *this;
    }

    ContainerList& operator=(ContainerList&& other) noexcept {
        // ContainerList::operator=(std::move(other));
        if (this != &other) {
            first_ = std::move(other.first_);
            last_ = std::move(other.last_);
            size_ = std::move(other.size_);
            first_iterator = std::move(other.first_iterator);
            last_iterator = std::move(other.last_iterator);

            other.first_ = nullptr;
            other.last_ = nullptr;
            other.size_ = 0;
            other.first_iterator = nullptr;
            other.last_iterator = nullptr;
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

    class iterator {
        friend class ContainerList<T>;

      public:
        // нулевой конструкрор
        iterator() : the_node(0) {}
        // здесь мы создаем итератор с указателя на узел Double_node
        iterator(Node* node_) : the_node(node_) {}
        // конструктор копии
        iterator(const iterator& it) : the_node(it.the_node) {}

        iterator& operator=(const iterator& it) {
            the_node = it.the_node;
            return *this;
        }

        // в этом классе оператор == означает, что два итератора указывают на
        // один и тот же узел
        bool operator==(const iterator& it) const {
            return (the_node == it.the_node);
        }

        bool operator!=(const iterator& it) const {
            return !(it == *this);
        }

        // переводит итератор на следующий узел списка.
        iterator& operator++() {
            if (the_node == 0)
                throw "incremented an empty iterator";
            // if (the_node->next == 0)
            // throw "tried to increment too far past the end";

            the_node = the_node->next;
            return *this;
        }

        // переводит итератор на предідущий узел списка.
        iterator& operator--() {
            if (the_node == 0)
                throw "decremented an empty iterator";
            if (the_node->prev == 0)
                throw "tried to decrement past the beginning";

            the_node = the_node->prev;
            return *this;
        }

        // Возвращает значение данных.
        T& operator*() const {
            if (the_node == 0)
                throw "tried to dereference an empty iterator";
            return the_node->data;
        }

      private:
        Node* the_node;
    };

    iterator begin() {
        return first_iterator;
    }

    iterator end() {
        return last_iterator;
    }

  private:
    struct Node {
        Node* prev = nullptr;
        Node* next = nullptr;
        T data{};

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
        Node() {}
        ~Node() {}
    };

  private:
    Node* first_ = nullptr;
    Node* last_ = nullptr;
    size_t size_ = 0;

    iterator first_iterator =
        nullptr; // итератор, который всегда указывает на начало списка
    iterator last_iterator =
        nullptr; // итератор, который всегда указывает на элемент,
                 // который находится за последним.
};

template <typename T> void print_container(const ContainerList<T>& container) {
    for (size_t i = 0; i < container.size(); ++i) {
        if (i != 0)
            std::cout << ' ';

        std::cout << container[i];
    }
}
