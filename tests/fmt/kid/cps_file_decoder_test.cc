#include "fmt/kid/cps_file_decoder.h"
#include "test_support/catch.hh"
#include "test_support/file_support.h"

using namespace au;
using namespace au::fmt::kid;

TEST_CASE("KID CPS containers", "[fmt]")
{
    CpsFileDecoder decoder;
    auto input_file = tests::file_from_path(
        "tests/fmt/kid/files/cps/yh04adm.cps");
    auto expected_file = tests::file_from_path(
        "tests/fmt/kid/files/cps/yh04adm.prt");
    auto actual_file = decoder.decode(*input_file);
    tests::compare_files(*expected_file, *actual_file, false);
}