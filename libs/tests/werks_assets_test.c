#include "gem_testing.h"
#include "werks_assets.h"

#ifdef werks_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_assets_test ../src/kewl.c ../src/werks_assets.c werks_assets_test.c")
#endif

EMBED_ASSET("build.sh", databin_asset);

int main(void) {
    Tests.begin("WeRKS ASSETS");
    Tests.run("asset is embedded", assigned(databin_asset_start));
    Tests.run("DUMP_ASSET", DUMP_ASSET("build.sh.out", databin_asset));
    Tests.run("delete_file", delete_file("build.sh.out"));
    return Tests.end();
}

