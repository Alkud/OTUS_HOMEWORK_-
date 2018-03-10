// main.cpp in OTUS Homework #2

#include <iostream>
#include <regex>
#include <iterator>
#include "ip_address_works.h"

using ipIntVector = std::vector<uint32_t>;

std::vector<std::string> split(std::string inputString, char delimiter)
{
  std::vector<std::string> result;
  auto first {0U};
  auto last{inputString.find_first_of(delimiter, 0)};
  while(last != std::string::npos)
  {
    result.push_back(inputString.substr(first, last - first));
    first = last + 1;
    last = inputString.find_first_of(delimiter, first);
  }
  result.push_back(inputString.substr(first));
  return result;
}

ipIntVector filter(const ipIntVector& inputVector, uint8_t firstByte)
{
  std::vector<uint32_t> result;
  for (auto address : inputVector)
  {
    if (address >> 24 == firstByte)
      result.push_back(address);
  }
  return result;
}

ipIntVector filter(const ipIntVector& inputVector, uint8_t firstByte, uint8_t secondByte)
{
  ipIntVector result;
  for (auto address : inputVector)
  {
    if ( address >> 24 == firstByte &&
        (address & 0x00FF0000) >> 16 == secondByte)
      result.push_back(address);
  }
  return result;
}

ipIntVector filterAny(const ipIntVector& inputVector, uint8_t filterByte)
{
  ipIntVector result;
  for (auto address : inputVector)
  {
    if (                     address >> 24 == filterByte ||
              (address & 0x00FF0000) >> 16 == filterByte ||
              (address & 0x0000FF00) >> 8  == filterByte ||
              (address & 0x000000FF)       == filterByte   )
      result.push_back(address);
  }
  return result;
}




int main(int argc, char* argv[])
{
  std::vector<uint32_t> addresses{};
  try
  {
    std::string nextString;
    /* User input */
    while(std::getline(std::cin, nextString))
    {
      std::string addressString{split(nextString, '\t').at(0)};
      addresses.push_back(ipStringToInteger(addressString));
    }
    /* Lambda sorter */
    auto descendingSorter {[](uint32_t a, uint32_t b){return b < a;}};
    /* Sorting user input with lamba sorter */
    std::sort(addresses.begin(), addresses.end(), descendingSorter); // sort in the descending order
    /* Output sorted values */
    for (auto addressInteger : addresses)
    {
      std::cout << ipIntegerToString(addressInteger) << std::endl;            // output in sorting order
    }

    auto filteredAddresses {filter(addresses, 1)};
    for (auto addressInteger : filteredAddresses)
    {
      std::cout << ipIntegerToString(addressInteger) << std::endl;            // output in sorting order
    }

    filteredAddresses = filter(addresses, 46, 70);
    for (auto addressInteger : filteredAddresses)
    {
      std::cout << ipIntegerToString(addressInteger) << std::endl;            // output in sorting order
    }

    filteredAddresses = filterAny(addresses, 46);
    for (auto addressInteger : filteredAddresses)
    {
      std::cout << ipIntegerToString(addressInteger) << std::endl;            // output in sorting order
    }
  }
  catch (const std::exception &e)
  {
    /* If something's wrong, send exception's messsage to std::cerr */
    std::cerr << e.what() << std::endl;
  }
}
