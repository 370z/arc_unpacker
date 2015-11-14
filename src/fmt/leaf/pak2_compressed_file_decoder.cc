#include "fmt/leaf/pak2_compressed_file_decoder.h"
#include "io/buffered_io.h"
#include "util/range.h"

using namespace au;
using namespace au::fmt::leaf;

static const bstr magic = "\xAF\xF6\x4D\x4F"_b;

static bstr decompress(const bstr &src, const size_t size_orig)
{
    bstr output;
    output.reserve(size_orig);
    io::BufferedIO input_io(src);
    while (output.size() < size_orig && !input_io.eof())
    {
        const auto control = input_io.read_u8();
        if (control >= 0x80)
        {
            if (control >= 0xA0)
            {
                int repeat;
                int base_value;
                if (control == 0xFF)
                {
                    repeat = input_io.read_u8() + 2;
                    base_value = 0;
                }
                else if (control >= 0xE0)
                {
                    repeat = (control & 0x1F) + 2;
                    base_value = 0;
                }
                else
                {
                    repeat = (control & 0x1F) + 2;
                    base_value = input_io.read_u8();
                }
                output += bstr(repeat, base_value);
            }
            else
            {
                const auto repeat = control & 0x1F;
                output += input_io.read(repeat);
            }
        }
        else
        {
            const auto look_behind
                = (input_io.read_u8() + (control << 8)) % 0x400;
            const auto repeat = (control >> 2) + 2;
            for (const auto i : util::range(repeat))
                output += output[output.size() - look_behind];
        }
    }
    return output;
}

bool Pak2CompressedFileDecoder::is_recognized_impl(File &file) const
{
    return file.io.seek(4).read(magic.size()) == magic;
}

std::unique_ptr<File> Pak2CompressedFileDecoder::decode_impl(File &file) const
{
    const auto size_orig = file.io.seek(24).read_u32_le();
    const auto data = file.io.seek(36).read_to_eof();
    return std::make_unique<File>(file.name, decompress(data, size_orig));
}

static auto dummy
    = fmt::register_fmt<Pak2CompressedFileDecoder>("leaf/pak2-compressed-file");
