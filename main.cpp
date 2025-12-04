#include "include/array_template.h"
#include "include/pentagon_template.h"
#include "include/rhombus_template.h"
#include "include/trapezoid_template.h"
#include <iostream>
#include <memory>

template <Scalar T> void PrintFigureInfo(const Figure<T> &fig) {
  std::cout << "Координаты вершин: ";
  fig.PrintPoints();
  auto center = fig.GetCenter();
  std::cout << "Геометрический центр: (" << center.x << ", " << center.y << ")"
            << "\n";
  std::cout << "Площадь: " << fig.GetArea() << "\n";
}

template <Scalar T>
double TotalArea(const Array<std::shared_ptr<Figure<T>>> &arr) {
  double total = 0;
  for (size_t i = 0; i < arr.Size(); ++i) {
    if (arr[i]) {
      total += arr[i]->GetArea();
    }
  }
  return total;
}

int main() {
  std::cout << "Массив указателей на базовый класс Figure<double>*\n";
  Array<Figure<double> *> arr1(5);

  auto *pent = new Pentagon<double>();
  std::cout << "Введите 5 точек для пятиугольника:\n";
  try {
    std::cin >> *pent;
    arr1.Push(pent);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Ошибка: " << e.what() << "\n";
    delete pent;
    return 1;
  }

  auto *rhomb = new Rhombus<double>();
  std::cout << "Введите 4 точки для ромба:" << "\n";
  try {
    std::cin >> *rhomb;
    arr1.Push(rhomb);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Ошибка: " << e.what() << "\n";
    delete rhomb;
    for (size_t i = 0; i < arr1.Size(); ++i)
      delete arr1[i];
    return 1;
  }

  auto *trap = new Trapezoid<double>();
  std::cout << "Введите 4 точки для трапеции:\n";
  try {
    std::cin >> *trap;
    arr1.Push(trap);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Ошибка: " << e.what() << "\n";
    delete trap;
    for (size_t i = 0; i < arr1.Size(); ++i)
      delete arr1[i];
    return 1;
  }

  std::cout << "\nИнформация о фигурах:\n";
  for (size_t i = 0; i < arr1.Size(); ++i) {
    std::cout << "Фигура " << i + 1 << ":" << "\n";
    PrintFigureInfo(*arr1[i]);
  }

  double total1 = 0;
  for (size_t i = 0; i < arr1.Size(); ++i) {
    total1 += arr1[i]->GetArea();
  }
  std::cout << "Общая площадь: " << total1 << "\n";

  std::cout << "\nУдаление фигуры с индексом 1" << "\n";
  delete arr1[1];
  arr1.Remove(1);

  std::cout << "Оставшиеся фигуры: " << arr1.Size() << "\n";

  for (size_t i = 0; i < arr1.Size(); ++i) {
    delete arr1[i];
  }

  std::cout << "\nПример 2: Массив умных указателей на Figure<double>\n";
  Array<std::shared_ptr<Figure<double>>> arr2(5);

  auto pent2 = std::make_shared<Pentagon<double>>();
  std::cout << "Введите 5 точек для пятиугольника:\n";
  try {
    std::cin >> *pent2;
    arr2.Push(pent2);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Ошибка: " << e.what() << "\n";
    return 1;
  }

  auto rhomb2 = std::make_shared<Rhombus<double>>();
  std::cout << "Введите 4 точки для ромба\n";
  try {
    std::cin >> *rhomb2;
    arr2.Push(rhomb2);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Ошибка: " << e.what() << "\n";
    return 1;
  }

  std::cout << "\nИнформация о фигурах:\n";
  for (size_t i = 0; i < arr2.Size(); ++i) {
    std::cout << "Фигура " << i + 1 << ":\n";
    PrintFigureInfo(*arr2[i]);
  }

  std::cout << "Общая площадь: " << TotalArea(arr2) << "\n";

  std::cout << "\nМассив конкретных фигур Pentagon<double>\n";

  Array<Pentagon<double>> arr3(3);

  Pentagon<double> p1;
  std::cout << "Введите 5 точек для пятиугольника:\n";
  try {
    std::cin >> p1;
    arr3.Push(std::move(p1));
  } catch (const std::invalid_argument &e) {
    std::cerr << "Ошибка: " << e.what() << "\n";
    return 1;
  }

  std::cout << "\nИнформация о пятиугольниках:\n";
  for (size_t i = 0; i < arr3.Size(); ++i) {
    std::cout << "Пятиугольник " << i + 1 << ":\n";
    PrintFigureInfo(arr3[i]);
  }

  std::cout << "\nТестирование операций\n";
  Pentagon<double> test1, test2;
  std::cout << "Введите 5 точек для первого пятиугольника:\n";
  try {
    std::cin >> test1;
  } catch (const std::invalid_argument &e) {
    std::cerr << "Ошибка: " << e.what() << "\n";
    return 1;
  }
  std::cout << "Введите 5 точек для второго пятиугольника:\n";
  try {
    std::cin >> test2;
  } catch (const std::invalid_argument &e) {
    std::cerr << "Ошибка: " << e.what() << "\n";
    return 1;
  }

  std::cout << "Пятиугольники равны? " << (test1 == test2 ? "Да" : "Нет")
            << "\n";

  Pentagon<double> test3 = test1;
  std::cout << "Копия равна оригиналу? " << (test3 == test1 ? "Да" : "Нет")
            << "\n";

  double area = static_cast<double>(test1);
  std::cout << "Площадь через приведение к double: " << area << "\n";

  return 0;
}
