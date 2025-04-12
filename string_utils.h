/**
 * @brief Utility functions for string manipulation.
 */
#ifndef string_utils_H
#define string_utils_H

#include <Arduino.h>

/**
 * @brief Splits a string into an array of substrings based on a specified delimiter.
 *
 * This function takes an input string and divides it into multiple substrings
 * wherever the delimiter character is found. The resulting substrings are stored
 * in a dynamically allocated array of String objects.
 *
 * @param input The string to be split.
 * @param delimiter The character used to separate the substrings.
 * @param numParts A reference to an integer variable where the number of resulting
 * substrings will be stored. The caller is responsible for
 * deallocating the memory pointed to by the returned String array.
 * @return A pointer to a dynamically allocated array of String objects, where each
 * element contains a substring from the input string. Returns `nullptr`
 * if memory allocation fails
 *
 * ## Usage:
 * ```cpp
 * String myString = "apple,banana,orange";
 * char delimiter = ',';
 * int partsCount;
 * String* parts = splitString(myString, delimiter, partsCount);
 *
 * if (parts != nullptr) {
 *  Serial.print("Number of parts: ");
 *  Serial.println(partsCount);
 *  for (int i = 0; i < partsCount; i++) {
 *  Serial.print("Part ");
 *  Serial.print(i);
 *  Serial.print(": ");
 *  Serial.println(parts[i]);
 * }
 * // Remember to deallocate the memory when done
 * delete[] parts;
 * } else {
 *  Serial.println("Failed to split the string.");
 * }
 * ```
 */
String* splitString(String input, char delimiter, int& numParts);

#endif