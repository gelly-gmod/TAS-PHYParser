#pragma once

#include "common.hpp"
#include "../enums.hpp"
#include <array>
#include <cstdint>

namespace PhyParser::Enums {
  enum class ModelType : int16_t;
}
namespace PhyParser::Structs {
#pragma pack(push, 1)
  struct Header {
    int32_t size;
    int32_t id;
    int32_t solidCount;
    int64_t checksum;
  };

  struct CompactSurfaceHeader {
    int32_t size;
    int32_t vphysicsId;
    int16_t version;
    Enums::ModelType modelType;
    int32_t surfaceSize;
    Vector3 dragAxisAreas;
    int32_t axisMapSize;
  };

  struct LegacySurfaceHeader {
    int32_t size;
    Vector3 massCentre;
    Vector3 rotationInertia;
    float upperLimitRadius;
    int32_t maxDeviation : 8;
    int32_t byteSize : 24;
    int32_t offsetLedgetreeRoot;
    std::array<int32_t, 3> dummy;
  };

  struct ConvexSolidHeader {
    int32_t verticesOffset;
    int32_t boneIndex;
    int32_t flags; // TODO: Enum?
    int32_t trianglesCount;
  };

  struct Triangle {
    int8_t vertexIndex;
    int8_t unused1;
    uint16_t unused2;

    int16_t vertex1Index;
    int16_t unused3;
    int16_t vertex2Index;
    int16_t unused4;
    int16_t vertex3Index;
    int16_t unused5;
  };
#pragma pack(pop)
}
