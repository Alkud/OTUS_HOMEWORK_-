// main.cpp in OTUS Homework #2

#include <iostream>
#include <regex>
#include <iterator>
#include "ip_address_works.h"
#include "ip_filter_version.h" // if we need to get current build version


std::string extractAddress(const std::string& source)
{
  std::regex addressPattern{"((\\d{1,3}\\.){3}\\d{1,3})"};//((\\d{1,3}\\.){3}\\d{1,3})
  std::smatch match;
  if (std::regex_search(source, match, addressPattern))
  {
    return match[0];
  }
  else
    return std::string{};
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
      std::string addressString{extractAddress(nextString)};
      addresses.push_back(ipStringToInteger(addressString));
    }
    /* Lambda sorter */
    auto descendingSorter {[](uint32_t a, uint32_t b){return b < a;}};
    /* Sorting user input with lamba sorter */
    std::sort(addresses.begin(), addresses.end(), descendingSorter); // sort in the descending order
    /* Output sorted values */
    for (auto stringInteger : addresses)
    {
      std::cout << ipIntegerToString(stringInteger) << std::endl;   // output in sorting order
    }
  }
  catch (const std::exception &e)
  {
    /* If something's wrong, send exception's messsage to std::cerr */
    std::cerr << e.what() << std::endl;
  }
}
