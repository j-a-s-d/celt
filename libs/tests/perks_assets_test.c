#include "gem_testing.h"
#include "perks_assets.h"

#ifdef PERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/perks_assets_test ../src/kewl.c ../src/perks_assets.c perks_assets_test.c")
#endif

EMBED_ASSET("build.sh", databin_asset);

int main(void) {
    Tests.begin("PeRKS ASSETS");
    Tests.run("asset is embedded", assigned(databin_asset_start));
    Tests.run("DUMP_ASSET", DUMP_ASSET("build.sh.out", databin_asset));
    Tests.run("delete_file", delete_file("build.sh.out"));
    return Tests.end();
}

