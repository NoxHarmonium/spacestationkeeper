//
//  EnumHelper.cpp
//  SpaceStationKeeper
//
//  Created by Sean Dawson on 10/04/2014.
//
//

#include "Utils/EnumHelper.h"

EnumHelper::EnumHelper() {}

void EnumHelper::setFlag(int value) { _internalValue |= value; }
void EnumHelper::clearFlag(int value) { _internalValue &= !value; }
bool EnumHelper::hasFlag(int value) { return _internalValue & value; }
int EnumHelper::getInternalValue() { return _internalValue; }

std::ostream &operator<<(std::ostream &out, EnumHelper &helper) {
  out << std::dec << "(0x" << std::hex << helper._internalValue << ") ";
  return out;
}
