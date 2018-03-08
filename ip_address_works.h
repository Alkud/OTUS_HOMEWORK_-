// ip_address_works.h in OTUS Homework #2

#pragma once

#include <array>

using  ipArray = std::array<uint8_t, 4>;

/* Define default (or dummy) ip address */
#define DEFAULT_IP_INTEGER 0
#define DEFAULT_IP_STRING std::string{"0.0.0.0"}
#define DEFAULT_IP_ARRAY ipArray{0, 0, 0, 0}

/* Convert a "ddd.ddd.ddd.ddd" string to an array and vice versa */
ipArray ipStringToArray(const std::string& addressString);
std::string ipArrayToString(const ipArray& addressTuple);

/* Convert a "ddd.ddd.ddd.ddd" string to an integer value and vice versa */
uint32_t ipStringToInteger(const std::string& addressString);
std::string ipIntegerToString(const uint32_t& addressInteger);

/* Convert an array to an integer value and vice versa */
uint32_t ipArrayToInteger(const ipArray& addressTuple);
ipArray ipIntegerToArray(const uint32_t& addressInteger);
