#include "gem_testing.h"
#include "werks_expreval.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_expreval_test ../src/kewl.c ../src/werks_expreval.c werks_expreval_test.c");
#endif

void test_bad_expr(werks_expreval_dt* evaluator, const char* expr) {
    WERKS_EXPREVAL_TYPE result = werks_expreval_evaluate_expression(evaluator, expr);
    Tests.run("werks_expreval_evaluate_expression NO expression", werks_expreval_constants_get_error(evaluator) == WERKS_EXPREVAL_ERROR_EXPRESSION && WERKS_EXPREVAL_ISNAN(result));
    Tests.print("Expression: %s\n", expr);
    Tests.print("Result: " WERKS_EXPREVAL_FORMAT STRINGS_LF, result);
}

size_t result_changes = 0;

void on_result_change_handler(__unused werks_expreval_expressions_list_dt* list, werks_expreval_expressions_data_dt* data) {
    Tests.print("result change on expression \"%s\": " WERKS_EXPREVAL_FORMAT " (old) -> " WERKS_EXPREVAL_FORMAT " (new)\n", data->expression, data->last, data->current);
    result_changes++;
}

bool loop_done = false;

void loop_handler(__unused werks_expreval_expressions_list_dt* list, werks_expreval_expressions_data_dt* data) {
    Tests.print("looping \"%s\" = " WERKS_EXPREVAL_FORMAT "\n", data->expression, data->current);
    loop_done = true;
}

void loop_with_reference_handler(__unused werks_expreval_expressions_list_dt* list, werks_expreval_expressions_data_dt* data, void* reference) {
    Tests.print("looping with reference \"%s\" = " WERKS_EXPREVAL_FORMAT "\n", data->expression, data->current);
    loop_done = assigned(reference);
}

double treater(double value) {
    Tests.print("treating " WERKS_EXPREVAL_FORMAT "\n", value);
    return value + 1.0;
}

int main(void) {
    Tests.begin("WeRKS EXPREVAL");
    werks_expreval_dt* evaluator = werks_expreval_make();
    Tests.run("werks_expreval_make", assigned(evaluator));
    werks_expreval_constants_dt* cs = werks_expreval_constants_get_constants(evaluator);
    Tests.run("werks_expreval_get_constants", assigned(cs));
    Tests.run("werks_expreval_constants_count 0", werks_expreval_constants_count(cs) == 0);
    Tests.run("werks_expreval_constants_set NO null", !werks_expreval_constants_set(cs, NULL, 2.0));
    Tests.run("werks_expreval_constants_set NO empty", !werks_expreval_constants_set(cs, "", 2.0));
    Tests.run("werks_expreval_constants_set YES", werks_expreval_constants_set(cs, "x", 2.0));
    Tests.run("werks_expreval_constants_has NO null", !werks_expreval_constants_has(cs, NULL));
    Tests.run("werks_expreval_constants_has NO empty", !werks_expreval_constants_has(cs, ""));
    Tests.run("werks_expreval_constants_has YES", werks_expreval_constants_has(cs, "x"));
    Tests.run("werks_expreval_constants_get NO null", WERKS_EXPREVAL_ISNAN(werks_expreval_constants_get(cs, NULL)));
    Tests.run("werks_expreval_constants_get NO empty", WERKS_EXPREVAL_ISNAN(werks_expreval_constants_get(cs, "")));
    Tests.run("werks_expreval_constants_get NO inexistent", WERKS_EXPREVAL_ISNAN(werks_expreval_constants_get(cs, "y")));
    Tests.run("werks_expreval_constants_get YES", !WERKS_EXPREVAL_ISNAN(werks_expreval_constants_get(cs, "x")));
    werks_expreval_constants_set(cs, "y", 3.0);
    Tests.run("werks_expreval_constants_count 2", werks_expreval_constants_count(cs) == 2);
    WERKS_EXPREVAL_TYPE result = WERKS_EXPREVAL_NAN;
    result = werks_expreval_evaluate_expression(evaluator, "($x + 2) / ($y * 5)");
    Tests.run("werks_expreval_evaluate_expression YES 1", werks_expreval_constants_get_error(evaluator) == WERKS_EXPREVAL_ERROR_NONE && result != WERKS_EXPREVAL_NAN);
    Tests.print("Result: " WERKS_EXPREVAL_FORMAT STRINGS_LF, result);
    werks_expreval_constants_drop(cs, "x");
    Tests.run("werks_expreval_constants_drop", werks_expreval_constants_count(cs) == 1);
    werks_expreval_constants_set(cs, "y", 4.0);
    Tests.run("werks_expreval_constants_get", werks_expreval_constants_get(cs, "y") == 4.0);
    result = werks_expreval_evaluate_expression(evaluator, "$x + 1");
    Tests.run("werks_expreval_evaluate_expression NO constant", werks_expreval_constants_get_error(evaluator) == WERKS_EXPREVAL_ERROR_CONSTANT && WERKS_EXPREVAL_ISNAN(result));
    Tests.print("Result: " WERKS_EXPREVAL_FORMAT STRINGS_LF, result);
    result = werks_expreval_evaluate_expression(evaluator, "1 + $x");
    Tests.run("werks_expreval_evaluate_expression NO constant", werks_expreval_constants_get_error(evaluator) == WERKS_EXPREVAL_ERROR_CONSTANT && WERKS_EXPREVAL_ISNAN(result));
    Tests.print("Result: " WERKS_EXPREVAL_FORMAT STRINGS_LF, result);
    result = werks_expreval_evaluate_expression(evaluator, "1 + 2");
    Tests.run("werks_expreval_evaluate_expression YES 2", werks_expreval_constants_get_error(evaluator) == WERKS_EXPREVAL_ERROR_NONE && !WERKS_EXPREVAL_ISNAN(result));
    result = werks_expreval_evaluate_expression(evaluator, "123");
    Tests.run("werks_expreval_evaluate_expression YES 3", werks_expreval_constants_get_error(evaluator) == WERKS_EXPREVAL_ERROR_NONE && !WERKS_EXPREVAL_ISNAN(result));
    result = werks_expreval_evaluate_expression(evaluator, "$y");
    Tests.run("werks_expreval_evaluate_expression YES 4", werks_expreval_constants_get_error(evaluator) == WERKS_EXPREVAL_ERROR_NONE && !WERKS_EXPREVAL_ISNAN(result));
    Tests.print("Result: " WERKS_EXPREVAL_FORMAT STRINGS_LF, result);
    test_bad_expr(evaluator, NULL);
    test_bad_expr(evaluator, "");
    test_bad_expr(evaluator, "+");
    test_bad_expr(evaluator, "-");
    test_bad_expr(evaluator, "*");
    test_bad_expr(evaluator, "/");
    test_bad_expr(evaluator, "(");
    test_bad_expr(evaluator, ")");
    test_bad_expr(evaluator, ".");
    test_bad_expr(evaluator, "$");
    test_bad_expr(evaluator, "abc");
    test_bad_expr(evaluator, "#");
    test_bad_expr(evaluator, "123 -");
    test_bad_expr(evaluator, "123 +");
    test_bad_expr(evaluator, "123 + .");
    test_bad_expr(evaluator, "123 + (");
    test_bad_expr(evaluator, "123 + )");
    test_bad_expr(evaluator, "123 + ($y -");
    test_bad_expr(evaluator, "123 + ($y *");
    test_bad_expr(evaluator, "123 + ($y /");
    werks_expreval_expressions_list_dt* list = werks_expreval_expressions_list_make();
    Tests.run("werks_expreval_expressions_list_make", assigned(list));
    Tests.run("werks_expreval_expressions_list_get_count 0", werks_expreval_expressions_list_get_count(list) == 0);
    Tests.run("werks_expreval_expressions_list_get_rounds 0", werks_expreval_expressions_list_get_rounds(list) == 0);
    Tests.run("werks_expreval_expressions_list_get_on_result_change NULL", werks_expreval_expressions_list_get_on_result_change(list) == NULL);
    werks_expreval_expressions_list_set_on_result_change(list, on_result_change_handler);
    Tests.run("werks_expreval_expressions_list_set_on_result_change", werks_expreval_expressions_list_get_on_result_change(list) == on_result_change_handler);
    werks_expreval_expressions_list_reevaluate(list, evaluator);
    Tests.run("werks_expreval_expressions_list_get_rounds 1", werks_expreval_expressions_list_get_rounds(list) == 1);
    Tests.run("werks_expreval_expressions_list_add NO null", !werks_expreval_expressions_list_add(list, NULL));
    Tests.run("werks_expreval_expressions_list_add NO empty", !werks_expreval_expressions_list_add(list, ""));
    Tests.run("werks_expreval_expressions_list_add YES", werks_expreval_expressions_list_add(list, "$y + 1"));
    Tests.run("werks_expreval_expressions_list_get_count 1", werks_expreval_expressions_list_get_count(list) == 1);
    Tests.run("werks_expreval_expressions_list_add YES", werks_expreval_expressions_list_add(list, "$y + 2"));
    Tests.run("werks_expreval_expressions_list_get_count 0", werks_expreval_expressions_list_get_count(list) == 2);
    Tests.run("werks_expreval_expressions_list_add NO repeated", !werks_expreval_expressions_list_add(list, "$y + 1"));
    Tests.run("werks_expreval_expressions_list_delete YES", werks_expreval_expressions_list_delete(list, "$y + 2"));
    Tests.run("werks_expreval_expressions_list_get_count 1", werks_expreval_expressions_list_get_count(list) == 1);
    Tests.run("werks_expreval_expressions_list_delete NO inexistent", !werks_expreval_expressions_list_delete(list, "$y + 2"));
    Tests.run("werks_expreval_expressions_list_delete NO empty", !werks_expreval_expressions_list_delete(list, ""));
    Tests.run("werks_expreval_expressions_list_delete NO null", !werks_expreval_expressions_list_delete(list, NULL));
    const werks_expreval_expressions_data_dt* data = werks_expreval_expressions_list_get(list, "$y + 1");
    Tests.run("werks_expreval_expressions_list_get YES", assigned(data));
    Tests.print("data->expression: %s\n", data->expression);
    Tests.run("werks_expreval_expressions_list_get NO null", werks_expreval_expressions_list_get(list, NULL) == NULL);
    Tests.run("werks_expreval_expressions_list_get NO empty", werks_expreval_expressions_list_get(list, "") == NULL);
    Tests.run("werks_expreval_expressions_list_get NO inexistent", werks_expreval_expressions_list_get(list, "$y + 2") == NULL);
    Tests.run("on_result_change 0", result_changes == 0);
    werks_expreval_expressions_list_reevaluate(list, evaluator);
    Tests.run("werks_expreval_expressions_list_get_rounds 2", werks_expreval_expressions_list_get_rounds(list) == 2);
    Tests.run("on_result_change 1", result_changes == 1);
    werks_expreval_constants_set(cs, "y", 5.0);
    werks_expreval_expressions_list_reevaluate(list, evaluator);
    Tests.run("werks_expreval_expressions_list_get_rounds 3", werks_expreval_expressions_list_get_rounds(list) == 3);
    Tests.run("on_result_change 2", result_changes == 2);
    werks_expreval_expressions_list_reevaluate(list, evaluator);
    Tests.run("werks_expreval_expressions_list_get_rounds 4", werks_expreval_expressions_list_get_rounds(list) == 4);
    Tests.run("on_result_change 2", result_changes == 2);
    Tests.run("werks_expreval_expressions_list_add YES", werks_expreval_expressions_list_add(list, "$y + 3"));
    Tests.run("werks_expreval_expressions_list_get_count 2", werks_expreval_expressions_list_get_count(list) == 2);
    werks_expreval_expressions_list_reevaluate(list, evaluator);
    Tests.run("werks_expreval_expressions_list_get_rounds 5", werks_expreval_expressions_list_get_rounds(list) == 5);
    werks_expreval_expressions_list_loop(list, loop_handler);
    Tests.run("werks_expreval_expressions_list_loop", loop_done);
    loop_done = false;
    werks_expreval_expressions_list_reverse_loop(list, loop_handler);
    Tests.run("werks_expreval_expressions_list_reverse_loop", loop_done);
    werks_expreval_expressions_list_loop_with_reference(list, loop_with_reference_handler, list);
    Tests.run("werks_expreval_expressions_list_loop_with_reference", loop_done);
    loop_done = false;
    werks_expreval_expressions_list_reverse_loop_with_reference(list, loop_with_reference_handler, list);
    Tests.run("werks_expreval_expressions_list_reverse_loop_with_reference", loop_done);
    werks_expreval_expressions_list_sort_by_value_ascending(list);
    werks_expreval_expressions_list_loop(list, loop_handler);
    werks_expreval_expressions_list_sort_by_value_descending(list);
    werks_expreval_expressions_list_loop(list, loop_handler);
    const werks_expreval_expressions_data_dt* data_before_treat = werks_expreval_expressions_list_get(list, "$y + 1");
    Tests.run("data_before_treat 6", data_before_treat->current == 6.0);
    werks_expreval_expressions_list_treat(list, treater);
    const werks_expreval_expressions_data_dt* data_after_treat = werks_expreval_expressions_list_get(list, "$y + 1");
    Tests.run("data_after_treat 7", data_after_treat->current == 7.0);
    Tests.run("werks_expreval_expressions_list_get_current_value NO 0", werks_expreval_expressions_list_get_current_value(list, "$y + 2", 0.0) == 0.0);
    Tests.run("werks_expreval_expressions_list_get_current_value YES 7", werks_expreval_expressions_list_get_current_value(list, "$y + 1", 0.0) == 7.0);
    werks_expreval_expressions_list_destroy(list);
    werks_expreval_constants_set(cs, "x", 4.0);
    Tests.run("werks_expreval_constants_count 2", werks_expreval_constants_count(cs) == 2);
    Tests.run("werks_expreval_constants_get x 4", werks_expreval_constants_get(cs, "x") == 4.0);
    Tests.run("werks_expreval_constants_get y 5", werks_expreval_constants_get(cs, "y") == 5.0);
    Tests.run("werks_expreval_constants_set_all", werks_expreval_constants_set_all(cs, 123.0));
    Tests.run("werks_expreval_constants_get x 123", werks_expreval_constants_get(cs, "x") == 123.0);
    Tests.run("werks_expreval_constants_get y 123", werks_expreval_constants_get(cs, "y") == 123.0);
    Tests.run("werks_expreval_constants_drop_all", werks_expreval_constants_drop_all(cs));
    Tests.run("werks_expreval_constants_count 0", werks_expreval_constants_count(cs) == 0);
    werks_expreval_destroy(evaluator);
    return Tests.end();
}

