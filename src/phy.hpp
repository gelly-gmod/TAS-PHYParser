#pragma once

#include "helpers/offset-data-view.hpp"
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
    };

    explicit Phy(const std::span<std::byte>& data, const std::optional<int64_t>& checksum = std::nullopt);

    [[nodiscard]] int64_t getChecksum() const;

    [[nodiscard]] const std::vector<Solid>& getSolids() const;

  private:
    Structs::Header header;
    std::vector<Solid> solids;

    [[nodiscard]] static std::vector<Solid> parseSurface(
      const Structs::SurfaceHeader& surfaceHeader, const OffsetDataView& data
    );

    [[nodiscard]] static std::vector<Solid> parseCompactSurface(const OffsetDataView& data);

    [[nodiscard]] static std::vector<Solid> parseMopp(const OffsetDataView& data);

    [[nodiscard]] static Solid parseLedge(const Structs::Ledge& ledge, const OffsetDataView& data);
  };
}
