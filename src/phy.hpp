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
    struct Solid {};

    explicit Phy(const std::span<std::byte>& data, const std::optional<int64_t>& checksum = std::nullopt);

    [[nodiscard]] int64_t getChecksum() const;

  private:
    Structs::Header header;
    std::vector<Solid> solids;

    [[nodiscard]] static Solid parseSurface(const Structs::SurfaceHeader& surfaceHeader, const OffsetDataView& data);

    [[nodiscard]] static Solid parseCompactSurface(const OffsetDataView& data);

    [[nodiscard]] static Solid parseMopp(const OffsetDataView& data);

    [[nodiscard]] static std::pair<std::vector<Structs::Vector4>, std::vector<uint16_t>> parseLedge(
      const Structs::Ledge& ledge, const OffsetDataView& data
    );
  };
}
