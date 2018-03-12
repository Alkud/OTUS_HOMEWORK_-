// main.cpp in OTUS Homework #2

#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include <functional>
#include <utility>
#include <algorithm>
#include <vector>
#include "ip_address_works.h"

using stringVector = std::vector<std::string>;
using ipVector = std::vector<uint32_t>;
struct ipStruct
{
  uint32_t value{};
  uint8_t byte3{};
  uint8_t byte2{};
  uint8_t byte1{};
  uint8_t byte0{};
};

bool operator<(const ipStruct& a, const ipStruct& b)
{
  return a.value < b.value;
}

bool operator>(const ipStruct& a, const ipStruct& b)
{
  return a.value > b.value;
}

using ipStructVector = std::vector<ipStruct>;

stringVector split(std::string inputString, char delimiter)
{
  stringVector result;
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

ipStructVector filter(const ipStructVector& inputVector, int byte3, int byte2 = -1, int byte1 = -1, int byte0 = -1)
{
  ipStructVector result{};
  for(auto addressStruct : inputVector)
  {
    if (byte3 == addressStruct.byte3 &&
        (byte2 == -1 || byte2 == addressStruct.byte2) &&
        (byte1 == -1 || byte1 == addressStruct.byte1) &&
        (byte0 == -1 || byte0 == addressStruct.byte0)   )
      result.push_back(addressStruct);
  }
  return result;
}

template <uint8_t... args>
ipStructVector filterAny(const ipStructVector& inputVector)
{
  ipStructVector result{};
  std::array<uint8_t, sizeof...(args)> argsArray{args...};
  for(auto addressStruct : inputVector)
  {
    for (auto& byte : argsArray)
    {
      if (byte == addressStruct.byte3 ||
          byte == addressStruct.byte2 ||
          byte == addressStruct.byte1 ||
          byte == addressStruct.byte0   )
      {
        result.push_back(addressStruct);
        break;
      }
    }
  }
  return result;
}

int main(int argc, char* argv[])
{
  ipStructVector addresses{};
  try
  {
    std::string nextString;
    /* User input */
    while(std::getline(std::cin, nextString))
    {
      std::string addressString{split(nextString, '\t').at(0)};
      auto addressInteger {ipStringToInteger(addressString)};
      ipArray addressArray {ipIntegerToArray(addressInteger)};
      ipStruct addressStruct{addressInteger, addressArray[3],
            addressArray[2], addressArray[1], addressArray[0]};
      addresses.push_back(addressStruct);
    }

    std::sort(addresses.begin(), addresses.end(), std::greater<>());

    /* Output sorted values */
    for (auto addressStruct : addresses)
    {
      std::cout << int(addressStruct.byte3) << "." <<
                   int(addressStruct.byte2) << "." <<
                   int(addressStruct.byte1) << "." <<
                   int(addressStruct.byte0) << std::endl;
    }

    /* Filter 1.*.*.*. */
    auto filteredAddresses {filter(addresses, 1)};
    for (auto addressStruct : filteredAddresses)
    {
      std::cout << int(addressStruct.byte3) << "." <<
                    int(addressStruct.byte2) << "." <<
                    int(addressStruct.byte1) << "." <<
                    int(addressStruct.byte0) << std::endl;
    }

    /* Filter 46.70.*.* */
    filteredAddresses = filter(addresses, 46, 70);
    for (auto addressStruct : filteredAddresses)
    {
      std::cout << int(addressStruct.byte3) << "." <<
                    int(addressStruct.byte2) << "." <<
                    int(addressStruct.byte1) << "." <<
                    int(addressStruct.byte0) << std::endl;
    }
    /* Filter any 46 */
    filteredAddresses = filterAny<46>(addresses);
    for (auto addressStruct : filteredAddresses)
    {
      std::cout << int(addressStruct.byte3) << "." <<
                    int(addressStruct.byte2) << "." <<
                    int(addressStruct.byte1) << "." <<
                    int(addressStruct.byte0) << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    /* If something's wrong, send exception's messsage to std::cerr */
    std::cerr << e.what() << std::endl;
  }
}
