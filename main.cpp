// main.cpp in OTUS Homework #2

#include <iostream>
#include <iterator>
#include <string>
#include <functional>
#include <utility>
#include <algorithm>
#include <vector>
#include <tuple>
#include <sstream>
#include "ip_address_works.h"

using stringVector = std::vector<std::string>;

using ipTuple = std::tuple<std::uint32_t, uint8_t, uint8_t, uint8_t, uint8_t>;
using ipTupleVector = std::vector<ipTuple>;

uint32_t ipBytesToInteger(const uint8_t& d3, const uint8_t& d2,
                          const uint8_t& d1, const uint8_t& d0)
{
  return (d3 << 24) + (d2 << 16) + (d1 << 8) + d0;
}

bool operator > (const ipTuple& a, const ipTuple& b)
{
  return std::get<0>(a) > std::get<0>(b);
}

bool operator < (const ipTuple& a, const ipTuple& b)
{
  return std::get<0>(a) < std::get<0>(b);
}

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

void filter(const ipTupleVector& inputVector, int byte3, int byte2 = -1, int byte1 = -1, int byte0 = -1)
{
  for(auto addressTuple : inputVector)
  {
    int d3 {std::get<1>(addressTuple)};
    int d2 {std::get<2>(addressTuple)};
    int d1 {std::get<3>(addressTuple)};
    int d0 {std::get<4>(addressTuple)};
    if ( byte3 ==  d3 &&
        (byte2 == -1 || byte2 == d2) &&
        (byte1 == -1 || byte1 == d1) &&
        (byte0 == -1 || byte0 == d0)   )
    {
      std::cout << d3 << '.' << d2 << '.' << d1 << '.' << d0 << std::endl;
    }
  }
}

template <uint8_t... args>
void filterAny(const ipTupleVector& inputVector)
{
  std::array<uint8_t, sizeof...(args)> argsArray{args...};
  for(auto addressTuple : inputVector)
  {
    int d3 {std::get<1>(addressTuple)};
    int d2 {std::get<2>(addressTuple)};
    int d1 {std::get<3>(addressTuple)};
    int d0 {std::get<4>(addressTuple)};
    for (auto& byte : argsArray)
    {
      if (byte == d3 || byte == d2 ||
          byte == d1 || byte == d0   )
      {
        std::cout << d3 << '.' << d2 << '.' << d1 << '.' << d0 << std::endl;
        break;
      }
    }
  }
}

int main(int argc, char* argv[])
{
  ipTupleVector addresses{};
  try
  {
    std::string nextString;
    /* User input */
    while(std::getline(std::cin, nextString))
    {
      std::string addressString{split(nextString, '\t').at(0)};
      std::stringstream stringStream{addressString};
      int byte3{}, byte2{}, byte1{}, byte0{};
      char ch{};
      stringStream >> byte3 >> ch >> byte2 >> ch >> byte1 >> ch >> byte0;
      uint32_t addressInteger { ipBytesToInteger( (uint8_t)byte3, (uint8_t)byte2,
            (uint8_t)byte1, (uint8_t)byte0 ) };
      addresses.push_back(std::tie(addressInteger, byte3, byte2, byte1, byte0));
    }

    /* Descending sorting */
    std::sort(addresses.begin(), addresses.end(), std::greater<>());

    /* Output sorted values */
    for (auto addressTuple : addresses)
    {
      int d3 {std::get<1>(addressTuple)};
      int d2 {std::get<2>(addressTuple)};
      int d1 {std::get<3>(addressTuple)};
      int d0 {std::get<4>(addressTuple)};
      std::cout << d3 << '.' << d2 << '.' << d1 << '.' << d0 << std::endl;
    }

    /* Filter 1.*.*.*. */
    filter(addresses, 1);

    /* Filter 46.70.*.* */
    filter(addresses, 46, 70);

    /* Filter any 46 */
    filterAny<46>(addresses);
  }
  catch (const std::exception &e)
  {
    /* If something's wrong, send exception's messsage to std::cerr */
    std::cerr << e.what() << std::endl;
  }
}
