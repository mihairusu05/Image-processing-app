#pragma once

#include <iostream>
using namespace std;

/**
 * @class Point
 * @brief A class that represents a 2D point with x and y coordinates.
 *
 * This class stores two integer values representing the x and y coordinates of a point.
 * It provides constructors, input/output stream operators, and basic operations for the point.
 */
class Point {
public:
    int m_x; /**< @brief The x-coordinate of the point. */
    int m_y; /**< @brief The y-coordinate of the point. */

    /**
     * @brief Default constructor for Point.
     * Initializes the point to (0, 0).
     */
    Point() : m_x(0), m_y(0) {}

    /**
     * @brief Constructs a Point with the given x and y coordinates.
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     */
    Point(int x, int y) : m_x(x), m_y(y) {}

    /**
     * @brief Overloads the output stream operator for Point.
     * @param os The output stream.
     * @param p1 The point to output.
     * @return The output stream with the point representation.
     */
    friend ostream& operator<<(ostream& os, const Point& p1) {
        os << "(" << p1.m_x << ", " << p1.m_y << ")";
        return os;
    }

    /**
     * @brief Overloads the input stream operator for Point.
     * @param is The input stream.
     * @param p1 The point to input.
     * @return The input stream with the point values.
     */
    friend istream& operator>>(istream& is, Point& p1) {
        is >> p1.m_x >> p1.m_y;
        return is;
    }
};

/**
 * @class Rectangle
 * @brief A class that represents a rectangle defined by its top-left corner (x, y), width, and height.
 *
 * This class provides constructors for creating a rectangle, along with stream operators,
 * and several operator overloads for manipulating and interacting with rectangles.
 */
class Rectangle {
public:
    int m_x; /**< @brief The x-coordinate of the top-left corner of the rectangle. */
    int m_y; /**< @brief The y-coordinate of the top-left corner of the rectangle. */
    unsigned int m_width; /**< @brief The width of the rectangle. */
    unsigned int m_height; /**< @brief The height of the rectangle. */

    /**
     * @brief Default constructor for Rectangle.
     * Initializes the rectangle to position (0, 0) with width and height 0.
     */
    Rectangle() : m_x(0), m_y(0), m_width(0), m_height(0) {}

    /**
     * @brief Constructs a Rectangle with the given x, y, width, and height.
     * @param x The x-coordinate of the top-left corner.
     * @param y The y-coordinate of the top-left corner.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     */
    Rectangle(int x, int y, unsigned int width, unsigned int height)
        : m_x(x), m_y(y), m_width(width), m_height(height) {
    }

    /**
     * @brief Constructs a Rectangle from two Points defining opposite corners.
     * @param p1 The first point (top-left corner).
     * @param p2 The second point (bottom-right corner).
     */
    Rectangle(Point p1, Point p2) {
        m_x = p1.m_x;
        m_y = p1.m_y;
        m_width = static_cast<unsigned int>(abs(p2.m_x - p1.m_x));
        m_height = static_cast<unsigned int>(abs(p2.m_y - p1.m_y));
    }

    /**
     * @brief Overloads the output stream operator for Rectangle.
     * @param os The output stream.
     * @param r The rectangle to output.
     * @return The output stream with the rectangle representation.
     */
    friend ostream& operator<<(ostream& os, const Rectangle& r) {
        os << "(" << r.m_x << ", " << r.m_y << ", " << r.m_width << ", " << r.m_height << ")";
        return os;
    }

    /**
     * @brief Overloads the input stream operator for Rectangle.
     * @param is The input stream.
     * @param r The rectangle to input.
     * @return The input stream with the rectangle values.
     */
    friend istream& operator>>(istream& is, Rectangle& r) {
        is >> r.m_x >> r.m_y >> r.m_width >> r.m_height;
        return is;
    }

    /**
     * @brief Adds a Point to the rectangle's position.
     * @param p The point to add to the rectangle's position.
     * @return A new Rectangle with the modified position.
     */
    Rectangle operator+(const Point& p) const {
        return Rectangle(m_x + p.m_x, m_y + p.m_y, m_width, m_height);
    }

    /**
     * @brief Subtracts a Point from the rectangle's position.
     * @param p The point to subtract from the rectangle's position.
     * @return A new Rectangle with the modified position.
     */
    Rectangle operator-(const Point& p) const {
        return Rectangle(m_x - p.m_x, m_y - p.m_y, m_width, m_height);
    }

    /**
     * @brief Performs intersection of two rectangles, returning the overlapping area.
     * @param other The other rectangle to intersect with.
     * @return A new Rectangle representing the intersection area.
     * @note If the rectangles don't overlap, this will return a rectangle with width and height of 0.
     */
    Rectangle operator&(const Rectangle& other) const {
        int newX = max(m_x, other.m_x);
        int newY = max(m_y, other.m_y);
        int x2 = min(m_x + static_cast<int>(m_width), other.m_x + static_cast<int>(other.m_width));
        int y2 = min(m_y + static_cast<int>(m_height), other.m_y + static_cast<int>(other.m_height));

        if (newX < x2 && newY < y2) {
            return Rectangle(newX, newY, x2 - newX, y2 - newY);
        }
        else {
            return Rectangle(0, 0, 0, 0); /**< @brief Return a "zero-area" rectangle if no overlap exists. */
        }
    }

    /**
     * @brief Performs union of two rectangles, returning the smallest rectangle that contains both.
     * @param other The other rectangle to union with.
     * @return A new Rectangle representing the union of both rectangles.
     */
    Rectangle operator|(const Rectangle& other) const {
        int newX = min(m_x, other.m_x);
        int newY = min(m_y, other.m_y);
        int x2 = max(m_x + static_cast<int>(m_width), other.m_x + static_cast<int>(other.m_width));
        int y2 = max(m_y + static_cast<int>(m_height), other.m_y + static_cast<int>(other.m_height));

        return Rectangle(newX, newY, x2 - newX, y2 - newY);
    }
};
