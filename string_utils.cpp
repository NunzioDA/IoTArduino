#include "string_utils.h"
#include "Arduino.h"

String* splitString(String input, char delimiter, int& numParts) {
  numParts = 1;
  for (int i = 0; i < input.length(); i++) {
    if (input.charAt(i) == delimiter) {
      numParts++;
    }
  }

  String* parts = new String[numParts];
  
  int start = 0;
  int end = 0;
  int index = 0;

  while ((end = input.indexOf(delimiter, start)) != -1) {
    parts[index++] = input.substring(start, end);
    start = end + 1;
  }


  parts[index] = input.substring(start);

  return parts;
}