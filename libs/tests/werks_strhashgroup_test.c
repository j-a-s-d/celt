#include "gem_testing.h"
#include "werks_strhashgroup.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_werks_strhashgroup_dtest ../src/kewl.c ../src/werks_strhashgroup.c werks_werks_strhashgroup_dtest.c");
#endif

bool on_before_insertion(__unused werks_strhashgroup_dt* group, __unused const char* token) {
    Tests.print("on_before_insertion\n");
    return false;
}

bool on_before_deletion(__unused werks_strhashgroup_dt* group, __unused const char* token) {
    Tests.print("on_before_deletion\n");
    return false;
}

int main(void) {
    Tests.begin("WeRKS STRHASHGROUP");
    werks_strhashgroup_dt* slg = werks_strhashgroup_create(false);
    Tests.run("werks_strhashgroup_create false slg", assigned(slg));
    Tests.run("werks_strhashgroup_get_component", assigned(werks_strhashgroup_get_component(slg)));
    Tests.run("werks_strhashgroup_has slg NO", !werks_strhashgroup_has(slg, "test"));
    Tests.run("werks_strhashgroup_add slg YES", werks_strhashgroup_add(slg, "test"));
    Tests.run("werks_strhashgroup_has slg YES", werks_strhashgroup_has(slg, "test"));
    Tests.run("werks_strhashgroup_add slg NO", !werks_strhashgroup_add(slg, "test"));
    Tests.run("werks_strhashgroup_count_every slg 1", werks_strhashgroup_count_every(slg, "test") == 1);
    Tests.run("werks_strhashgroup_add slg YES", werks_strhashgroup_add(slg, "bar"));
    Tests.run("werks_strhashgroup_has slg YES", werks_strhashgroup_has(slg, "bar"));
    Tests.run("werks_strhashgroup_add slg YES", werks_strhashgroup_add(slg, "baz"));
    Tests.run("werks_strhashgroup_has slg YES", werks_strhashgroup_has(slg, "baz"));
    Tests.run("werks_strhashgroup_get_on_before_insertion slg", werks_strhashgroup_get_on_before_insertion(slg) == NULL);
    werks_strhashgroup_set_on_before_insertion(slg, on_before_insertion);
    Tests.run("werks_strhashgroup_set_on_before_insertion slg", werks_strhashgroup_get_on_before_insertion(slg) != NULL);
    Tests.run("werks_strhashgroup_add slg NO", !werks_strhashgroup_add(slg, "testing"));
    Tests.run("werks_strhashgroup_remove_once slg YES", werks_strhashgroup_remove_once(slg, "baz"));
    Tests.run("werks_strhashgroup_remove_once slg NO", !werks_strhashgroup_remove_once(slg, "baz"));
    Tests.run("werks_strhashgroup_get_on_before_deletion slg", werks_strhashgroup_get_on_before_deletion(slg) == NULL);
    werks_strhashgroup_set_on_before_deletion(slg, on_before_deletion);
    Tests.run("werks_strhashgroup_set_on_before_deletion slg", werks_strhashgroup_get_on_before_deletion(slg) != NULL);
    Tests.run("werks_strhashgroup_remove_once slg NO", !werks_strhashgroup_remove_once(slg, "bar"));
    Tests.run("werks_strhashgroup_count_total slg 2", werks_strhashgroup_count_total(slg) == 2);
    werks_strhashgroup_set_on_before_deletion(slg, NULL);
    Tests.run("werks_strhashgroup_remove_every slg YES", werks_strhashgroup_remove_every(slg, "bar"));
    Tests.run("werks_strhashgroup_count_total slg 1", werks_strhashgroup_count_total(slg) == 1);
    werks_strhashgroup_clear(slg);
    Tests.run("werks_strhashgroup_clear slg", werks_strhashgroup_count_total(slg) == 0);
    werks_strhashgroup_dt* blg = werks_strhashgroup_create(true);
    Tests.run("werks_strhashgroup_create true blg", assigned(blg));
    Tests.run("werks_strhashgroup_has blg NO", !werks_strhashgroup_has(blg, "test"));
    Tests.run("werks_strhashgroup_add blg YES 1", werks_strhashgroup_add(blg, "test"));
    Tests.run("werks_strhashgroup_has blg YES", werks_strhashgroup_has(blg, "test"));
    Tests.run("werks_strhashgroup_add blg YES 2", werks_strhashgroup_add(blg, "test"));
    Tests.run("werks_strhashgroup_has blg YES", werks_strhashgroup_has(blg, "test"));
    Tests.run("werks_strhashgroup_count_every blg 2", werks_strhashgroup_count_every(blg, "test") == 2);
    Tests.run("werks_strhashgroup_add blg YES", werks_strhashgroup_add(blg, "bar"));
    Tests.run("werks_strhashgroup_has blg YES", werks_strhashgroup_has(blg, "bar"));
    Tests.run("werks_strhashgroup_add blg YES", werks_strhashgroup_add(blg, "baz"));
    Tests.run("werks_strhashgroup_has blg YES", werks_strhashgroup_has(blg, "baz"));
    Tests.run("werks_strhashgroup_get_on_before_insertion blg", werks_strhashgroup_get_on_before_insertion(blg) == NULL);
    werks_strhashgroup_set_on_before_insertion(blg, on_before_insertion);
    Tests.run("werks_strhashgroup_set_on_before_insertion blg", werks_strhashgroup_get_on_before_insertion(blg) != NULL);
    Tests.run("werks_strhashgroup_add blg NO", !werks_strhashgroup_add(blg, "testing"));
    Tests.run("werks_strhashgroup_remove_once blg YES", werks_strhashgroup_remove_once(blg, "baz"));
    Tests.run("werks_strhashgroup_remove_once blg NO", !werks_strhashgroup_remove_once(blg, "baz"));
    Tests.run("werks_strhashgroup_remove_every blg NO", !werks_strhashgroup_remove_every(blg, "baz"));
    Tests.run("werks_strhashgroup_get_on_before_deletion blg", werks_strhashgroup_get_on_before_deletion(blg) == NULL);
    werks_strhashgroup_set_on_before_deletion(blg, on_before_deletion);
    Tests.run("werks_strhashgroup_set_on_before_deletion blg", werks_strhashgroup_get_on_before_deletion(blg) != NULL);
    Tests.run("werks_strhashgroup_remove_once blg NO", !werks_strhashgroup_remove_once(blg, "bar"));
    Tests.run("werks_strhashgroup_count_total blg 3", werks_strhashgroup_count_total(blg) == 3);
    Tests.run("werks_strhashgroup_remove_every blg NO", !werks_strhashgroup_remove_every(blg, "test"));
    Tests.run("werks_strhashgroup_count_total blg 3", werks_strhashgroup_count_total(blg) == 3);
    werks_strhashgroup_set_on_before_deletion(blg, NULL);
    Tests.run("werks_strhashgroup_count_every blg 2", werks_strhashgroup_count_every(blg, "test") == 2);
    Tests.run("werks_strhashgroup_remove_every blg YES", werks_strhashgroup_remove_every(blg, "test"));
    Tests.run("werks_strhashgroup_count_total blg 1", werks_strhashgroup_count_total(blg) == 1);
    werks_strhashgroup_clear(blg);
    Tests.run("werks_strhashgroup_clear blg", werks_strhashgroup_count_total(blg) == 0);
    werks_strhashgroup_dt* slg2 = werks_strhashgroup_create(false);
    Tests.run("werks_strhashgroup_read_from_string slg2", werks_strhashgroup_read_from_string(slg2, "000--abd--def--ghi--ghi--123--456--789--000", "--"));
    Tests.run("werks_strhashgroup_count_total slg2 7", werks_strhashgroup_count_total(slg2) == 7);
    __auto char* csv = werks_strhashgroup_write_to_string(slg2, ';');
    Tests.run("werks_strhashgroup_write_to_string", has_content(csv));
    Tests.print("%s\n", csv);
    werks_strhashgroup_destroy(slg);
    werks_strhashgroup_destroy(blg);
    werks_strhashgroup_destroy(slg2);
    return Tests.end();
}

