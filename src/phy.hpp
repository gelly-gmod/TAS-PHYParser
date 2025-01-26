#pragma once

#include "helpers/offset-data-view.hpp"
#include "helpers/text-section-parser.hpp"
#include "structs/phy.hpp"
#include <memory>
#include <optional>
#include <span>
#include <vector>

namespace PhyParser {
  class Phy {
  public:
    struct Solid {
      std::vector<Structs::Vector4> vertices;
      std::vector<uint16_t> indices;

      int32_t boneIndex;
    };

    struct LedgeData {
      std::vector<Structs::Vector4> vertices;
      std::vector<uint16_t> indices;
    };

    explicit Phy(const std::span<std::byte>& data, const std::optional<int64_t>& checksum = std::nullopt);

    [[nodiscard]] int64_t getChecksum() const;

    [[nodiscard]] const std::vector<Solid>& getSolids() const;

    [[nodiscard]] const TextSection& getTextSection() const;

    [[nodiscard]] static std::vector<Solid> parseCompactSurface(const OffsetDataView& data);

  private:
    Structs::Header header;
    std::vector<Solid> solids;
    TextSection textSection;

    [[nodiscard]] static std::vector<Solid> parseSurface(
      const Structs::SurfaceHeader& surfaceHeader, const OffsetDataView& data
    );

    [[nodiscard]] static std::vector<Solid> parseMopp(const OffsetDataView& data);

    [[nodiscard]] static LedgeData parseLedge(const Structs::Ledge& ledge, const OffsetDataView& data);
  };
}
