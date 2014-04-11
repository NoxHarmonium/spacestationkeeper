//
//  EnumHelper.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 10/04/2014.
//
//

#include "EnumHelper.h"

EnumHelper::EnumHelper() {}

void EnumHelper::setFlag(int value) { _internalValue.insert(value); }
void EnumHelper::clearFlag(int value) { _internalValue.erase(value); }
bool EnumHelper::hasFlag(int value) { return _internalValue.count(value) > 0; }

std::ostream &operator<<(std::ostream &out, EnumHelper &helper) {

  int totalValue = 0;
  for (const auto &value : helper._internalValue) {
    totalValue |= value;
  }

  out << std::dec << "(0x" << std::hex << totalValue << ") ";
  return out;
}