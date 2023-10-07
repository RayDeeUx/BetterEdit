#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

struct FromLevelStart {};
struct DefaultBehaviour {};
using FromPoint = CCPoint;
using FromObj = StartPosObject*;
using StartPosKind = std::variant<
    FromLevelStart,
    DefaultBehaviour,
    FromPoint,
    FromObj
>;