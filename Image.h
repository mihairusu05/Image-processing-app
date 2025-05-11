#pragma once

#include <iostream>
#include <string>
#include "Helper_Classes.h"
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

/**
 * @class Size
 * @brief Represents the width and height of an image.
 */

class Size {
public:
	unsigned int width;/**< Image width */
	unsigned int height;/**< Image height */

	/**
	 * @brief Constructor to initialize width and height.
	 * @param w Image width.
	 * @param h Image height.
	 */

	Size(unsigned int w = 0, unsigned int h = 0) : width(w), height(h) {}
};

/**
 * @class Image
 * @brief Represents a grayscale image with pixel operations.
 */

class Image {
private :
	unsigned char** m_data;/**< Pointer to image pixel data */
	unsigned int m_width;/**< Image width */
	unsigned int m_height;/**< Image height */

	/**
	* @brief Allocates memory for the image.
	*/
	void allocateMemory() {
		m_data = new unsigned char* [m_height];
		for (unsigned int i = 0; i < m_height; ++i) {
			m_data[i] = new unsigned char[m_width] {0};
		}
	}

public :
	/**
	 * @brief Releases allocated memory.
	 */

	void release() {
		if (m_data) {
			for (unsigned int i = 0; i < m_height; ++i) {
				delete[] m_data[i];
			}

			delete[] m_data;
			m_data = nullptr;
			m_width = m_height = 0;
		}
	}

	/**
	 * @brief Default constructor. Creates an empty image.
	 */
	Image() : m_data(nullptr), m_width(0), m_height(0) {}

	/**
	 * @brief Constructor to create an image with specified width and height.
	 * @param w Image width.
	 * @param h Image height.
	 */
	Image(unsigned int w, unsigned int h) : m_width(w), m_height(h) {
		allocateMemory();
	}

	/**
	* @brief Copy constructor. Performs a deep copy of the image.
	* @param other The image to copy.
	*/
	Image(const Image& other) : m_width(other.m_width), m_height(other.m_height) {
		allocateMemory();
		for (unsigned int i = 0; i < m_height; ++i) {
			copy(other.m_data[i], other.m_data[i] + m_width, m_data[i]);
		}
	}

	/**
	 * @brief Copy assignment operator. Performs deep copy.
	 * @param other The image to copy.
	 * @return Reference to the assigned image.
	 */
	Image& operator=(const Image& other) {
		if (this == &other)
			return *this;
		release();
		m_width = other.m_width;
		m_height = other.m_height;

		allocateMemory();
		for (unsigned int i = 0; i < m_height; ++i) {
			copy(other.m_data[i], other.m_data[i] + m_width, m_data[i]);
		}

		return *this;
	}

	/**
	 * @brief Destructor. Releases allocated memory.
	 */
	~Image() {
		release();
	}

	/**
	 * @brief Loads a PGM image from a file.
	 * @param imagePath Path to the PGM file.
	 * @return True if loading succeeds, false otherwise.
	 */
	bool load(std::string imagePath) {
		std::ifstream file(imagePath, std::ios::binary);
		if (!file.is_open()) return false;

		std::string format;
		file >> format;
		if (format != "P5") return false; 

		file >> m_width >> m_height;
		int maxVal;
		file >> maxVal;
		file.ignore(); 

		if (maxVal > 255) return false;

		allocateMemory();
		for (unsigned int i = 0; i < m_height; ++i)
			file.read(reinterpret_cast<char*>(m_data[i]), m_width);

		file.close();
		return true;

	}

	/**
	 * @brief Saves the image to a PGM file.
	 * @param imagePath Path to save the PGM file.
	 * @return True if saving succeeds, false otherwise.
	 */
	bool save(std::string imagePath) {
		std::ofstream file(imagePath, std::ios::binary);
		if (!file.is_open()) return false;

		file << "P5\n" << m_width << " " << m_height << "\n255\n";
		for (unsigned int i = 0; i < m_height; ++i)
			file.write(reinterpret_cast<char*>(m_data[i]), m_width);

		file.close();
		return true;

	}

	/**
	 * @brief Adds two images pixel-wise.
	 * @param img The image to add.
	 * @return A new image containing the result.
	 */
	Image operator+(const Image& img) {
		Image result(m_width, m_height);
		for (unsigned int i = 0; i < m_height; ++i)
			for (unsigned int j = 0; j < m_width; ++j)
				result.m_data[i][j] = min(255, m_data[i][j] + img.m_data[i][j]);
		return result;

	}

	/**
	* @brief Subtracts an image pixel-wise.
	* @param img The image to subtract.
	* @return A new image containing the result.
	*/
	Image operator-(const Image& img) {
		Image result(m_width, m_height);
		for (unsigned int i = 0; i < m_height; ++i)
			for (unsigned int j = 0; j < m_width; ++j)
				result.m_data[i][j] = max(0, m_data[i][j] - img.m_data[i][j]);
		return result;

	}

	/**
   * @brief Extracts a region of interest (ROI) from the image.
   * @param roiImg The output image containing the ROI.
   * @param roiRect Rectangle defining the ROI bounds.
   * @return True if extraction is successful, false otherwise.
   */
	bool getROI(Image& roiImg, Rectangle roiRect) {
		if (roiRect.m_x + roiRect.m_width > m_width || roiRect.m_y + roiRect.m_height > m_height) return false;

		roiImg = Image(roiRect.m_width, roiRect.m_height);
		for (unsigned int i = 0; i < roiRect.m_height; ++i)
			for (unsigned int j = 0; j < roiRect.m_width; ++j)
				roiImg.m_data[i][j] = m_data[roiRect.m_y + i][roiRect.m_x + j];

		return true;

	}

	/**
	* @brief Extracts a region of interest (ROI) from the image.
	* @param roiImg The output image containing the ROI.
	* @param x X coordinate of the ROI.
	* @param y Y coordinate of the ROI.
	* @param width Width of the ROI.
	* @param height Height of the ROI.
	* @return True if extraction is successful, false otherwise.
	*/
	bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int
		height) {
		if (x + width > m_width || y + height > m_height) return false;  

		roiImg = Image(width, height);
		for (unsigned int i = 0; i < height; ++i)
			for (unsigned int j = 0; j < width; ++j)
				roiImg.at(j, i) = at(x + j, y + i);
		return true;
	}

	/**
	 * @brief Checks if the image is empty.
	 * @return True if empty, false otherwise.
	 */
	bool isEmpty() const { return m_data == nullptr; }

	/**
	 * @brief Gets the size of the image.
	 * @return Size object containing width and height.
	 */
	Size size() const { return Size(m_width, m_height); }

	/**
	* @brief Gets the image width.
	* @return Width of the image.
	*/
	unsigned int width() const { return m_width; }

	/**
	* @brief Gets the image height.
	* @return Height of the image.
	*/
	unsigned int height() const { return m_height; }

	/**
	* @brief Accesses a pixel value at a specific position.
	* @param x X coordinate of the pixel.
	* @param y Y coordinate of the pixel.
	* @return Reference to the pixel.
	*/
	unsigned char& at(unsigned int x, unsigned int y) { return m_data[y][x]; }

	/**
	* @brief Accesses a pixel value at a given point.
	* @param pt Point containing X and Y coordinates.
	* @return Reference to the pixel.
	*/
	unsigned char& at(Point pt) { return at(pt.m_x, pt.m_y); }

	/**
	 * @brief Gets a pointer to the specified row in the image.
	 * @param y Row index.
	 * @return Pointer to the row.
	 */
	unsigned char* row(int y) { return m_data[y]; }

	/**
	* @brief Outputs the image pixels in a formatted manner.
	* @param os The output stream.
	* @param img The image to print.
	* @return The output stream.
	*/
	friend ostream& operator<<(std::ostream& os, const Image& img) {
		for (unsigned int i = 0; i < img.m_height; ++i) {
			for (unsigned int j = 0; j < img.m_width; ++j)
				os << std::setw(3) << (int)img.m_data[i][j] << " ";
			os << std::endl;
		}
		return os;

	}

	/**
	* @brief Creates an image filled with zeros.
	* @param width Image width.
	* @param height Image height.
	* @return An image filled with zeros.
	*/
	static Image zeros(unsigned int width, unsigned int height) { return Image(width, height); }

	/**
	 * @brief Creates an image filled with ones (255 intensity).
	 * @param width Image width.
	 * @param height Image height.
	 * @return An image filled with 255 values.
	 */
	static Image ones(unsigned int width, unsigned int height) {
		Image img(width, height);
		for (unsigned int i = 0; i < height; ++i)
			fill(img.m_data[i], img.m_data[i] + width, 255);
		return img;

	}

};