/*
 * utils.h
 *
 *  Created on: Jan 7, 2012
 *      Author: Yu
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>

void tokenize(const std::string& str, std::vector<std::string> &str_vec, char delimiter = ' ');

void showArray(const int *array, int array_size);

void showVector(const std::vector<int>& vec);

#define ARRAY_COUNT(a) (sizeof(a)/sizeof(a[0]))

template <class T>
void printArray(const T *array, int array_size)
{
  for (int i = 0; i < array_size; ++i)
    std::cout << array[i] << ", ";

  std::cout << std::endl;
}

template <class T>
void printArray2D(const T *array, int rows, int cols)
{
  for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
          std::cout << array[i*rows+j] << ", ";
      }
      std::cout << std::endl;
  }
}

template <class T>
void printVector(const std::vector<T>& vec)
{
  for (int i = 0; i < vec.size(); ++i)
    std::cout << vec[i] << ", ";

  std::cout << std::endl;
}

template <class T>
void printVector2D(const std::vector<std::vector<T>>& vec)
{
  for (int i = 0; i < vec.size(); ++i) {
      for (int j = 0; j < vec[i].size(); ++j) {
          std::cout << vec[i][j] << ", ";
      }
      std::cout << std::endl;
  }
}

template <class T>
void buildVector2D(std::vector<std::vector<T>>& vec, const T* array, int rows, int cols)
{
  vec.resize(rows);
  for (int i = 0; i < vec.size(); ++i) {
      vec[i].resize(cols);
      for (int j = 0; j < vec[i].size(); ++j) {
          vec[i][j] = array[i*rows+j];
      }
  }
}

#endif /* UTILS_H_ */
