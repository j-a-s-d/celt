/**
 * werks_i18n: messages localization
 */

#include "gem_testing.h"
#include "werks_i18n.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/WERKS_I18N_test ../src/kewl.c ../src/WERKS_I18N.c WERKS_I18N_test.c")
#endif

int main(void) {
    Tests.begin("WeRKS I18N");
    Tests.run("werks_i18n_init", I18N.init());
    Tests.run("werks_i18n_init again", werks_i18n_init());
    Tests.run("werks_i18n_get_size", I18N.get_size() == 0);
    Tests.print("%lu\n", werks_i18n_get_size());
    Tests.run("werks_i18n_get_capacity", I18N.get_capacity() == WERKS_I18N_INITIAL_CAPACITY);
    Tests.print("%lu\n", werks_i18n_get_capacity());
    Tests.run("werks_i18n_get_current_language NONE", I18N.get_current_language() == NULL);
    Tests.run("werks_i18n_get_current_language_name NONE", I18N.get_current_language_name() == NULL);
    Tests.run("werks_i18n_set_current_language EN NO", !werks_i18n_set_current_language("en"));
    Tests.run("werks_i18n_accept_language NULL code", !I18N.accept_language(NULL, "English"));
    Tests.run("werks_i18n_accept_language NULL name", !I18N.accept_language("en", NULL));
    Tests.run("werks_i18n_accept_language NULL NULL", !I18N.accept_language(NULL, NULL));
    Tests.run("werks_i18n_accept_language EN", I18N.accept_language("en", "English"));
    Tests.run("werks_i18n_accept_language ES", werks_i18n_accept_language("es", "Español"));
    Tests.run("werks_i18n_get_current_language EN", streq(werks_i18n_get_current_language(), "en"));
    Tests.run("werks_i18n_get_current_language_name EN", streq(werks_i18n_get_current_language_name(), "English"));
    Tests.run("werks_i18n_fetch_raw_text NULL", streq(I18N.fetch_raw_text(NULL), WERKS_I18N_MESSAGE_DEFAULT_VALUE));
    Tests.run("werks_i18n_fetch_raw_text", streq(I18N.fetch_raw_text("hello_world"), WERKS_I18N_MESSAGE_DEFAULT_VALUE));
    Tests.print("%s\n", I18N.fetch_raw_text("hello_world"));
    Tests.run("werks_i18n_add_message NULL language", !werks_i18n_add_message(NULL, "Hello World!"));
    Tests.run("werks_i18n_add_message NULL message", !werks_i18n_add_message("hello_world", NULL));
    Tests.run("werks_i18n_add_message NULL NULL", !werks_i18n_add_message(NULL, NULL));
    Tests.run("werks_i18n_add_message", werks_i18n_add_message("hello_world", "Hello World!"));
    Tests.run("werks_i18n_fetch_raw_text", streq(werks_i18n_fetch_raw_text("hello_world"), "Hello World!"));
    Tests.print("%s\n", I18N.fetch_raw_text("hello_world"));
    Tests.run("werks_i18n_add_message again", werks_i18n_add_message("test", "testing"));
    Tests.run("werks_i18n_fetch_raw_text", streq(werks_i18n_fetch_raw_text("test"), "testing"));
    Tests.print("%s\n", I18N.fetch_raw_text("test"));
    Tests.run("werks_i18n_delete_message", werks_i18n_delete_message("test"));
    Tests.run("werks_i18n_fetch_raw_text", !has_content(I18N.fetch_raw_text("test")));
    Tests.run("werks_i18n_set_current_language ES", werks_i18n_set_current_language("es"));
    Tests.run("werks_i18n_get_current_language ES", streq(werks_i18n_get_current_language(), "es"));
    Tests.run("werks_i18n_add_message", werks_i18n_add_message("hello_world", "Hola Mundo!"));
    Tests.run("werks_i18n_fetch_raw_text", streq(werks_i18n_fetch_raw_text("hello_world"), "Hola Mundo!"));
    Tests.run("werks_i18n_register_message PT NO", !werks_i18n_register_message("pt:hello_world=Olá Mundo!"));
    Tests.run("werks_i18n_accept_language PT", werks_i18n_accept_language("pt", "Português"));
    Tests.run("werks_i18n_get_current_language_name ES", streq(werks_i18n_get_current_language_name(), "Español"));
    Tests.print("%s\n", werks_i18n_get_current_language_name());
    Tests.run("werks_i18n_register_message PT YES", werks_i18n_register_message("pt:hello_world=Olá Mundo!"));
    Tests.run("werks_i18n_get_current_language_name ES", streq(werks_i18n_get_current_language_name(), "Español"));
    Tests.run("werks_i18n_set_current_language PT", werks_i18n_set_current_language("pt"));
    Tests.run("werks_i18n_get_current_language_name PT", streq(werks_i18n_get_current_language_name(), "Português"));
    Tests.print("%s\n", werks_i18n_get_current_language_name());
    Tests.run("werks_i18n_fetch_raw_text", streq(werks_i18n_fetch_raw_text("hello_world"), "Olá Mundo!"));
    Tests.print("%s\n", I18N.fetch_raw_text("hello_world"));
    write_file("i18n.txt", "fr:hello_world=Salut Monde!\nit:hello_world=Ciao Mondo!\nde:hello_world=Hallo Welt!");
    Tests.run("werks_i18n_load_from_file", werks_i18n_load_from_file("i18n.txt"));
    Tests.run("werks_i18n_set_current_language FR NO", !werks_i18n_set_current_language("fr"));
    Tests.run("werks_i18n_accept_language FR", werks_i18n_accept_language("fr", "Français"));
    Tests.run("werks_i18n_accept_language IT", werks_i18n_accept_language("it", "Italiano"));
    Tests.run("werks_i18n_accept_language DE", werks_i18n_accept_language("de", "Deutsch"));
    Tests.run("werks_i18n_load_from_file", werks_i18n_load_from_file("i18n.txt"));
    Tests.run("werks_i18n_set_current_language FR", werks_i18n_set_current_language("fr"));
    Tests.run("werks_i18n_fetch_raw_text", streq(I18N.fetch_raw_text("hello_world"), "Salut Monde!"));
    Tests.run("werks_i18n_fetch_raw_language_text NULL language", streq(I18N.fetch_raw_language_text(NULL, "hello_world"), WERKS_I18N_MESSAGE_DEFAULT_VALUE));
    Tests.run("werks_i18n_fetch_raw_language_text NULL message", streq(I18N.fetch_raw_language_text("it", NULL), WERKS_I18N_MESSAGE_DEFAULT_VALUE));
    Tests.run("werks_i18n_fetch_raw_language_text NULL NULL", streq(I18N.fetch_raw_language_text(NULL, NULL), WERKS_I18N_MESSAGE_DEFAULT_VALUE));
    Tests.run("werks_i18n_fetch_raw_language_text", werks_i18n_fetch_raw_language_text("it", "hello_world"));
    Tests.run("werks_i18n_set_current_language DE", werks_i18n_set_current_language("de"));
    Tests.run("werks_i18n_fetch_raw_text", streq(I18N.fetch_raw_text("hello_world"), "Hallo Welt!"));
    Tests.run("werks_i18n_add_message", werks_i18n_add_message("guten_greeting", "Guten %s!"));
    __auto const char* sz1 = I18N.get_text("guten_greeting", "Tag");
    Tests.run("werks_i18n_get_text", streq(sz1, "Guten Tag!"));
    __auto const char* sz2 = werks_i18n_get_text("guten_greeting", "Tag");
    Tests.print("%s\n", sz2);
    __auto const char* sz3 = I18N.get_text("hello_world");
    Tests.run("werks_i18n_get_text no args", streq(sz3, "Hallo Welt!"));
    Tests.run("werks_i18n_get_text NULL", streq(werks_i18n_get_text(NULL), WERKS_I18N_MESSAGE_DEFAULT_VALUE));
    Tests.run("werks_i18n_set_current_language EN", werks_i18n_set_current_language("en"));
    Tests.run("werks_i18n_fetch_raw_text", streq(I18N.fetch_raw_text("hello_world"), "Hello World!"));
    __auto const char* sz4 = I18N.get_language_text("de", "guten_greeting", "Morgen");
    Tests.run("werks_i18n_get_language_text", streq(sz4, "Guten Morgen!"));
    __auto const char* sz5 = werks_i18n_get_language_text("de", "guten_greeting", "Morgen");
    Tests.print("%s\n", sz5);
    __auto const char* sz6 = I18N.get_language_text("de", "hello_world");
    Tests.run("werks_i18n_get_language_text no args", streq(sz6, "Hallo Welt!"));
    Tests.run("werks_i18n_get_language_text NULL NULL", streq(werks_i18n_get_language_text(NULL, NULL), WERKS_I18N_MESSAGE_DEFAULT_VALUE));
    I18N.deinit();
    werks_i18n_deinit();
    delete_file("i18n.txt");
    return Tests.end();
}

