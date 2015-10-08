#include "fmt/wild_bug/wpn_audio_decoder.h"
#include "test_support/catch.hh"
#include "test_support/decoder_support.h"
#include "test_support/file_support.h"

using namespace au;
using namespace au::fmt::wild_bug;

static void do_test(
    const std::string &input_path,
    const std::string &expected_path)
{
    WpnAudioDecoder decoder;
    auto input_file = tests::zlib_file_from_path(input_path);
    auto expected_file = tests::zlib_file_from_path(expected_path);
    auto actual_file = tests::decode(decoder, *input_file);
    tests::compare_files(*expected_file, *actual_file, false);
}

TEST_CASE("Wild Bug WPN audio", "[fmt]")
{
    do_test(
        "tests/fmt/wild_bug/files/wpn/SE_107-zlib.WPN",
        "tests/fmt/wild_bug/files/wpn/SE_107-zlib-out.wav");
}
