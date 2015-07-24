#ifndef FORMATS_KIRIKIRI_XP3_FILTERS_MAHOYORU_FILTER_H
#define FORMATS_KIRIKIRI_XP3_FILTERS_MAHOYORU_FILTER_H
#include "formats/kirikiri/xp3_filters/filter.h"

namespace Formats
{
    namespace Kirikiri
    {
        namespace Xp3Filters
        {
            class MahoYoruFilter final : public Filter
            {
            public:
                virtual void decode(File &file, u32 key) const override;
            };
        }
    }
}

#endif
