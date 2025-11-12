#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

std::vector<std::string> split(const std::string &s, char delim);

std::string trim(const std::string &s);

std::string getValidatedCccdInput();

std::string getValidatedCccdInputOptional();

// Room type validation functions
std::string getValidatedRoomTypeInput();

std::string getValidatedRoomTypeInputOptional();

// Room price validation functions
double getValidatedRoomPriceInput(const std::string &roomType);

double getValidatedRoomPriceInputOptional(const std::string &roomType);

// Helper function to get minimum price for a room type
double getMinimumPriceForRoomType(const std::string &roomType);

// Employee position validation functions
std::string getValidatedPositionInput();

std::string getValidatedPositionInputOptional();

// Batch operation helper functions
int getValidatedQuantityInput();

void displayProgressIndicator(int current, int total, const std::string &action);

bool getConfirmation(const std::string &message);

#endif
