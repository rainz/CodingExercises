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

#endif /* UTILS_H_ */
