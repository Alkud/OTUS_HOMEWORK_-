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
using ipMultimap = std::multimap<uint32_t, ipArray, std::greater<uint32_t>>;

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

ipMultimap filter(const ipMultimap& inputMap, int byte3, int byte2 = -1, int byte1 = -1, int byte0 = -1)
{
  ipMultimap result{};
  for(auto addressPair : inputMap)
  {
    if (byte3 == addressPair.second[3] &&
        (byte2 == -1 || byte2 == addressPair.second[2]) &&
        (byte1 == -1 || byte1 == addressPair.second[1]) &&
        (byte0 == -1 || byte0 == addressPair.second[0])   )
      result.insert(addressPair);
  }
  return result;
}

template <uint8_t... args>
ipMultimap filterAny(const ipMultimap& inputMap)
{
  ipMultimap result{};
  std::array<uint8_t, sizeof...(args)> argsArray{args...};
  for(auto addressPair : inputMap)
  {
    for (auto& byte : argsArray)
    {
      if (std::find(addressPair.second.begin(), addressPair.second.end(), byte)
          != addressPair.second.end())
      {
        result.insert(addressPair);
        break;
      }
    }
  }
  return result;
}



int main(int argc, char* argv[])
{
  ipMultimap addresses{};
  try
  {
    std::string nextString;
    /* User input */
    while(std::getline(std::cin, nextString))
    {
      std::string addressString{split(nextString, '\t').at(0)};
      auto addressInteger {ipStringToInteger(addressString)};
      addresses.insert(std::make_pair<uint32_t, ipArray>(
                         ipStringToInteger(addressString), ipIntegerToArray(addressInteger)));
    }
    /* Output sorted values */
    for (auto addressPair : addresses)
    {
      std::cout << int(addressPair.second[3]) << "." <<
                   int(addressPair.second[2]) << "." <<
                   int(addressPair.second[1]) << "." <<
                   int(addressPair.second[0]) << std::endl;
    }

    /* Filter 1.*.*.*. */
    auto filteredAddresses {filter(addresses, 1)};
    for (auto addressPair : filteredAddresses)
    {
      std::cout << int(addressPair.second[3]) << "." <<
                   int(addressPair.second[2]) << "." <<
                   int(addressPair.second[1]) << "." <<
                   int(addressPair.second[0]) << std::endl;
    }

    /* Filter 46.70.*.* */
    filteredAddresses = filter(addresses, 46, 70);
    for (auto addressPair : filteredAddresses)
    {
      std::cout << int(addressPair.second[3]) << "." <<
                   int(addressPair.second[2]) << "." <<
                   int(addressPair.second[1]) << "." <<
                   int(addressPair.second[0]) << std::endl;
    }

    /* Filter any 46 */
    filteredAddresses = filterAny<46>(addresses);
    for (auto addressPair : filteredAddresses)
    {
      std::cout << int(addressPair.second[3]) << "." <<
                   int(addressPair.second[2]) << "." <<
                   int(addressPair.second[1]) << "." <<
                   int(addressPair.second[0]) << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    /* If something's wrong, send exception's messsage to std::cerr */
    std::cerr << e.what() << std::endl;
  }
}
