#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include "../include/figure.h"
#include "../include/pentagon.h"
#include "../include/octagon.h"
#include "../include/array.h"

// -------------------------------------------------------------
// 1. Тесты геометрического центра
// -------------------------------------------------------------
TEST(FigureTest, PentagonCenter) {
    Pentagon p({{0,0}, {2,0}, {3,2}, {1,3}, {-1,2}});
    Point c = p.GetCenter();
    EXPECT_NEAR(c.x, 1.0, 1e-6);
    EXPECT_NEAR(c.y, 1.4, 1e-6);
}

TEST(FigureTest, OctagonCenter) {
    Octagon o({
        {0,0}, {2,0}, {3,1}, {3,3},
        {2,4}, {0,4}, {-1,3}, {-1,1}
    });
    Point c = o.GetCenter();
    EXPECT_NEAR(c.x, 1.0, 1e-6);
    EXPECT_NEAR(c.y, 2.0, 1e-6);
}

// -------------------------------------------------------------
// 2. Тесты площади
// -------------------------------------------------------------
TEST(FigureTest, PentagonArea) {
    Pentagon p({{0,0}, {2,0}, {3,2}, {1,3}, {-1,2}});
    double area = static_cast<double>(p);
    EXPECT_NEAR(area, 8.0, 1e-6);  
}

TEST(FigureTest, OctagonArea) {
    Octagon o({
        {0,0}, {2,0}, {3,1}, {3,3},
        {2,4}, {0,4}, {-1,3}, {-1,1}
    });
    double area = static_cast<double>(o);
    EXPECT_NEAR(area, 14.0, 1e-6);
}

// -------------------------------------------------------------
// 3. Тест operator<<
// -------------------------------------------------------------
TEST(IOTest, OutputOperator) {
    Pentagon p({{0,0}, {1,0}, {2,1}, {1,2}, {0,1}});
    std::ostringstream out;
    out << p;
    std::string text = out.str();

    EXPECT_NE(text.find("(0, 0)"), std::string::npos);
    EXPECT_NE(text.find("(1, 0)"), std::string::npos);
    EXPECT_NE(text.find("(2, 1)"), std::string::npos);
}

// -------------------------------------------------------------
// 4. Тест operator>>
// -------------------------------------------------------------
TEST(IOTest, InputOperator) {
    std::istringstream in("0 0 1 0 2 1 1 2 0 1");
    Pentagon p;
    in >> p;
    EXPECT_FALSE(in.fail());
    EXPECT_NEAR(static_cast<double>(p), 2.0, 1e-6);
}

// -------------------------------------------------------------
// 5. Тест копирования
// -------------------------------------------------------------
TEST(CopyMoveTest, CopyConstructor) {
    Pentagon p({{0,0},{1,0},{2,1},{1,2},{0,1}});
    Pentagon p2 = p;

    EXPECT_TRUE(p == p2);
    EXPECT_NEAR(static_cast<double>(p2), static_cast<double>(p), 1e-9);
}

TEST(CopyMoveTest, CopyAssignment) {
    Pentagon p({{0,0},{1,0},{2,1},{1,2},{0,1}});
    Pentagon p2;
    p2 = p;

    EXPECT_TRUE(p == p2);
}

TEST(CopyMoveTest, MoveConstructor) {
    Pentagon p({{0,0},{1,0},{2,1},{1,2},{0,1}});
    Pentagon p2 = std::move(p);

    EXPECT_NEAR(static_cast<double>(p2), 2.0, 1e-9);
}

TEST(CopyMoveTest, MoveAssignment) {
    Pentagon p({{0,0},{1,0},{2,1},{1,2},{0,1}});
    Pentagon p2;
    p2 = std::move(p);

    EXPECT_NEAR(static_cast<double>(p2), 2.0, 1e-9);
}

// -------------------------------------------------------------
// 6. Тест сравнения фигур
// -------------------------------------------------------------
TEST(FigureTest, Comparison) {
    Pentagon a({{0,0},{1,0},{2,1},{1,2},{0,1}});
    Pentagon b({{0,0},{1,0},{2,1},{1,2},{0,1}});
    Pentagon c({{0,1},{1,1},{2,2},{1,3},{0,2}});

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

// -------------------------------------------------------------
// 7. Тест массива фигур
// -------------------------------------------------------------
TEST(ArrayTest, InsertAndAreaSum) {
    Array arr(3);

    arr[0] = new Pentagon({{0,0},{1,0},{2,1},{1,2},{0,1}});
    arr[1] = new Octagon({
        {0,0}, {2,0}, {3,1}, {3,3},
        {2,4}, {0,4}, {-1,3}, {-1,1}
    });

    EXPECT_NEAR(static_cast<double>(*arr[0]), 2.0, 1e-6);
    EXPECT_NEAR(static_cast<double>(*arr[1]), 14.0, 1e-6);

    double sum = arr.TotalArea();
    EXPECT_NEAR(sum, 16.0, 1e-6);
}

TEST(ArrayTest, RemoveElement) {
    Array arr(3);

    arr[0] = new Pentagon({{0,0},{1,0},{2,1},{1,2},{0,1}});
    arr[1] = new Pentagon({{0,0},{1,0},{2,1},{1,2},{0,1}});

    arr.DeleteFigure(0);

    EXPECT_EQ(arr[0], nullptr);
    EXPECT_NE(arr[1], nullptr);
}
