#include "../include/array.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <iostream>


Array::Array() = default;

Array::Array(const size_t n) : sz(n) {
    arr_figures = new Figure*[sz];
    for (size_t i = 0; i < sz; ++i) {
        arr_figures[i] = nullptr;
    }
}

Figure*& Array::operator[](const size_t index) const{
    return arr_figures[index];
}

double Array::TotalArea() {
    double result = 0;
    for (size_t i = 0; i < sz; ++i) {
        if (arr_figures[i]) {
            result += arr_figures[i]->GetArea();
        }
    }
    return result;
}

void Array::DeleteFigure(size_t index) {
    if (index >= sz || arr_figures[index] == nullptr) return;
    delete arr_figures[index];
    arr_figures[index] = nullptr;
}


Array::~Array() {
    for (size_t i = 0; i < sz; ++i) {
        // TODO: Проверять i элемент массива на существование
        if (arr_figures[i]) delete arr_figures[i];
    }
    delete[] arr_figures;
    // if (arr_figures) {
    //     delete[] arr_figures;
    //     arr_figures = nullptr;
    // }
}