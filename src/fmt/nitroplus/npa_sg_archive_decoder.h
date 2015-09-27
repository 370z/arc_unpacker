#pragma once

#include "fmt/archive_decoder.h"

namespace au {
namespace fmt {
namespace nitroplus {

    class NpaSgArchiveDecoder final : public ArchiveDecoder
    {
    protected:
        bool is_recognized_internal(File &) const override;
        void unpack_internal(File &, FileSaver &) const override;
    };

} } }