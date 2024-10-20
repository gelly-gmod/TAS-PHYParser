#include "phy.hpp"
#include "helpers/offset-data-view.hpp"

namespace PhyParser {
  using Structs::Header;

  Phy::Phy(const std::span<std::byte>& data, const std::optional<int64_t>& checksum) {
    const OffsetDataView dataView(data);
    header = dataView.parseStruct<Header>(0, "Failed to parse PHY header").first;

    if (checksum.has_value() && header.checksum != checksum.value()) {
      throw InvalidChecksum("PHY checksum does not match");
    }
  }

  int64_t Phy::getChecksum() const {
    return header.checksum;
  }
}
