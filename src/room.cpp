#include "room.h";

Room::Room(std::string filename, int difficulty) {
  // Current expected layout format:
  // characterNumber|characterNumber|...|characterNumber\n
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open room layout file: " + filename);
  }
  int rowCount = 0;
  std::string row;
  while (std::getline(file, row) && rowCount < MAX_HEIGHT) {
    std::strncpy(roomMap[rowCount], row.c_str(), MAX_WIDTH - 1);
    rowCount++;
  }
}
