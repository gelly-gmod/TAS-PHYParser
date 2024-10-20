#pragma once
#include "structs/phy.hpp"
#include <memory>
#include <optional>
#include <span>

namespace PhyParser {
  class Phy {
  public:
    explicit Phy(const std::span<std::byte>& data, const std::optional<int64_t>& checksum = std::nullopt);

    [[nodiscard]] int64_t getChecksum() const;

  private:
    Structs::Header header;
  };
}
