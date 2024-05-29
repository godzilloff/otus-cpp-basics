#include "container_list.hpp"
#include "container_serial.hpp"
#include <iostream>

void test_container_serial() {
    // 1. создание объекта контейнера для хранения объектов типа int
    ContainerSerial<int> int_container;

    // 2. добавление в контейнер десяти элементов (0, 1 … 9)
    for (int ii = 0; ii < 10; ii++) {
        int_container.push_back(ii);
    }

    // 3. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;

    // 4. вывод размера контейнера на экран
    std::cout << "size " << int_container.size() << std::endl;

    // 5. удаление третьего (по счёту), пятого и седьмого элементов
    int_container.erase(3);
    int_container.erase(4);
    int_container.erase(5);

    // 6. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;

    // 7. добавление элемента 10 в начало контейнера
    int_container.insert(0, 10);

    // 8. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;

    // 9. добавление элемента 20 в середину контейнера
    int_container.insert(int_container.size() / 2, 20);

    // 10. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;

    // 11. добавление элемента 30 в конец контейнера
    int_container.push_back(30);

    // 12. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;
}

void test_container_list() {
    // 1. создание объекта контейнера для хранения объектов типа int
    ContainerList<int> int_container;

    // 2. добавление в контейнер десяти элементов (0, 1 … 9)
    for (int ii = 0; ii < 10; ii++) {
        int_container.push_back(ii);
    }

    // 3. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;

    // 4. вывод размера контейнера на экран
    std::cout << "size " << int_container.size() << std::endl;

    // 5. удаление третьего (по счёту), пятого и седьмого элементов
    int_container.erase(3);
    int_container.erase(4);
    int_container.erase(5);

    // 6. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;

    // 7. добавление элемента 10 в начало контейнера
    int_container.insert(0, 10);

    // 8. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;

    // 9. добавление элемента 20 в середину контейнера
    int_container.insert(int_container.size() / 2, 20);

    // 10. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;

    // 11. добавление элемента 30 в конец контейнера
    int_container.push_back(30);

    // 12. вывод содержимого контейнера на экран
    print_container(int_container);
    std::cout << std::endl;
}

int main() {
    test_container_serial();

    std::cout << std::endl;

    test_container_list();

    return 0;
}