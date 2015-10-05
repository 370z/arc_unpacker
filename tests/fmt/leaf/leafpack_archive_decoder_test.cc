#include "fmt/leaf/leafpack_archive_decoder.h"
#include "test_support/archive_support.h"
#include "test_support/catch.hh"
#include "test_support/file_support.h"

using namespace au;
using namespace au::fmt::leaf;

TEST_CASE("Leaf LEAFPACK archives", "[fmt]")
{
    std::vector<std::shared_ptr<File>> expected_files
    {
        tests::stub_file("123.txt", "1234567890"_b),
        tests::stub_file("abc.xyz", "abcdefghijklmnopqrstuvwxyz"_b),
    };

    LeafpackArchiveDecoder decoder;
    auto actual_files = au::tests::unpack_to_memory(
        "tests/fmt/leaf/files/leafpack/test.pak", decoder);

    au::tests::compare_files(expected_files, actual_files, true);
}
