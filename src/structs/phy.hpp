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

  struct SurfaceHeader {
    int32_t size;
    int32_t vphysicsId;
    int16_t version;
    Enums::ModelType modelType;
    int32_t surfaceSize;
  };

  struct CompactSurfaceHeader {
    Vector3 dragAxisAreas;
    int32_t axisMapSize;

    // Split into a separate "legacy surface header" by dev wiki, but always present for compact surfaces
    Vector3 massCentre;
    Vector3 rotationInertia;
    float upperLimitRadius;
    int32_t maxDeviation : 8;
    int32_t byteSize : 24;
    int32_t offsetLedgetreeRoot;
    std::array<int32_t, 2> unused;
    std::array<char, 4> id; // Should be IVPS
  };

  struct ConvexSolidHeader {
    int32_t verticesOffset;
    int32_t boneIndex;
    int32_t flags; // TODO: Enum?
    int32_t trianglesCount;
  };

  struct LedgeNode {
    int32_t rightNodeOffset;
    int32_t compactNodeOffset;
    Vector3 centre;
    float radius;
    std::array<uint8_t, 3> boxSizes;
    uint8_t unused;

    [[nodiscard]] bool isTerminal() const {
      return rightNodeOffset == 0;
    }
  };

  struct Ledge {
    int32_t pointOffset;

    union {
      int32_t ledgetreeNodeOffset;
      int32_t sourceUserdata;
    };

    uint32_t hasChildrenFlags : 2;
    int32_t isCompactFlag : 2;
    uint32_t dummy : 4;
    uint32_t sizeDiv16 : 24;

    uint16_t trianglesCount;
    int16_t unknown;
  };

  struct Edge {
    uint16_t startPointIndex : 16;
    uint16_t oppositePointIndex : 15;
    uint16_t isVirtual : 1;
  };

  struct CompactTriangle {
    uint16_t triangleIndex : 12;
    uint16_t pierceIndex : 12;
    uint16_t materialIndex : 7;
    uint16_t isVirtual : 1;

    std::array<Edge, 3> edges;
  };
#pragma pack(pop)
}
