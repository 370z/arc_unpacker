#pragma once

#include "fmt/archive_decoder.h"

namespace au {
namespace fmt {
namespace will {

    class WipfArchiveDecoder final : public ArchiveDecoder
    {
    protected:
        bool is_recognized_internal(File &) const override;
        void unpack_internal(File &, FileSaver &) const override;
        std::unique_ptr<INamingStrategy> naming_strategy() const override;
    };

} } }