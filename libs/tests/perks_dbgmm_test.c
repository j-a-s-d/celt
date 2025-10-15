#include "gem_testing.h"
#include "perks_dbgmm.h"

#ifdef PERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/perks_dbgmm_test ../src/kewl.c ../src/perks_dbgmm.c perks_dbgmm_test.c")
#endif

void report_callback(size_t size, const char* stringified_pointers) {
    Tests.print("report_callback calls: %lu\n", dbgmm_get_report_calls());
    Tests.print("Heap Pointers (%zu):\n%s\n", size, stringified_pointers);
}

void alloca_callback(size_t size, const char* file, int line, const char* func, void* new_ptr) {
    Tests.print("[%s:%i@%s] alloca %p[%li]\n", file, line, func, new_ptr, size);
}

void aligned_alloca_callback(size_t alignment, size_t size, const char* file, int line, const char* func, void* new_ptr) {
    Tests.print("[%s:%i@%s] aligned_alloca %p[%zu]#%zu<%s>\n", file, line, func, new_ptr, size, alignment, is_byte_aligned(new_ptr, alignment) ? "aligned" : "misaligned");
}

void malloc_success_callback(size_t size, const char* file, int line, const char* func, void* new_ptr) {
    Tests.print("[%s:%i@%s] malloc %p[%li]\n", file, line, func, new_ptr, size);
}

void malloc_failure_callback(size_t size, const char* file, int line, const char* func) {
    Tests.print("[%s:%i@%s] malloc failed [%zu]\n", file, line, func, size);
}

void calloc_success_callback(size_t num, size_t size, const char* file, int line, const char* func, void* new_ptr) {
    Tests.print("[%s:%i@%s] calloc %p[%zu]\n", file, line, func, new_ptr, num * size);
}

void calloc_failure_callback(size_t num, size_t size, const char* file, int line, const char* func) {
    Tests.print("[%s:%i@%s] calloc failed [%zu * %zu]\n", file, line, func, num, size);
}

#ifdef __c11
void aligned_alloc_success_callback(size_t alignment, size_t size, const char* file, int line, const char* func, void* new_ptr) {
    Tests.print("[%s:%i@%s] aligned_alloc %p[%zu]#%zu<%s>\n", file, line, func, new_ptr, size, alignment, is_byte_aligned(new_ptr, alignment) ? "aligned" : "misaligned");
}

void aligned_alloc_failure_callback(size_t alignment, size_t size, const char* file, int line, const char* func) {
    Tests.print("[%s:%i@%s] aligned_alloc failed [%zu]#%zu\n", file, line, func, size, alignment);
}
#endif

void realloc_success_callback(void* ptr, size_t size, const char* file, int line, const char* func, void* new_ptr) {
    Tests.print("[%s:%i@%s] realloc %p[%li] from %p\n", file, line, func, new_ptr, size, ptr);
}

void realloc_failure_callback(void* ptr, size_t size, const char* file, int line, const char* func) {
    Tests.print("[%s:%i@%s] realloc failed %p(%zu)\n", file, line, func, ptr, size);
}

void free_success_callback(void* ptr, const char* file, int line, const char* func) {
    Tests.print("[%s:%i@%s] free %p\n", file, line, func, ptr);
}

void free_failure_callback(const char* file, int line, const char* func) {
    Tests.print("[%s:%i@%s] free NULL\n", file, line, func);
}

int main(void) {
    Tests.begin("PeRKS DBGMM");
    
    Tests.run("dbgmm_get_report_callback", dbgmm_get_report_callback() == NULL);
    dbgmm_set_report_callback(report_callback);
    Tests.run("dbgmm_set_report_callback", dbgmm_get_report_callback() == report_callback);
    
    Tests.run("dbgmm_get_alloca_callback", dbgmm_get_alloca_callback() == NULL);
    dbgmm_set_alloca_callback(alloca_callback);
    Tests.run("dbgmm_set_alloca_callback", dbgmm_get_alloca_callback() == alloca_callback);
    
    Tests.run("dbgmm_get_aligned_alloca_callback", dbgmm_get_aligned_alloca_callback() == NULL);
    dbgmm_set_aligned_alloca_callback(aligned_alloca_callback);
    Tests.run("dbgmm_set_aligned_alloca_callback", dbgmm_get_aligned_alloca_callback() == aligned_alloca_callback);
    
    Tests.run("dbgmm_get_malloc_success_callback", dbgmm_get_malloc_success_callback() == NULL);
    dbgmm_set_malloc_success_callback(malloc_success_callback);
    Tests.run("dbgmm_set_malloc_success_callback", dbgmm_get_malloc_success_callback() == malloc_success_callback);
    
    Tests.run("dbgmm_get_malloc_failure_callback", dbgmm_get_malloc_failure_callback() == NULL);
    dbgmm_set_malloc_failure_callback(malloc_failure_callback);
    Tests.run("dbgmm_set_malloc_failure_callback", dbgmm_get_malloc_failure_callback() == malloc_failure_callback);
    
    Tests.run("dbgmm_get_calloc_success_callback", dbgmm_get_calloc_success_callback() == NULL);
    dbgmm_set_calloc_success_callback(calloc_success_callback);
    Tests.run("dbgmm_set_calloc_success_callback", dbgmm_get_calloc_success_callback() == calloc_success_callback);
    
    Tests.run("dbgmm_get_calloc_failure_callback", dbgmm_get_calloc_failure_callback() == NULL);
    dbgmm_set_calloc_failure_callback(calloc_failure_callback);
    Tests.run("dbgmm_set_calloc_failure_callback", dbgmm_get_calloc_failure_callback() == calloc_failure_callback);
    
    Tests.run("dbgmm_get_aligned_alloc_success_callback", dbgmm_get_aligned_alloc_success_callback() == NULL);
    dbgmm_set_aligned_alloc_success_callback(aligned_alloc_success_callback);
    Tests.run("dbgmm_set_aligned_alloc_success_callback", dbgmm_get_aligned_alloc_success_callback() == aligned_alloc_success_callback);
    
    Tests.run("dbgmm_get_aligned_alloc_failure_callback", dbgmm_get_aligned_alloc_failure_callback() == NULL);
    dbgmm_set_aligned_alloc_failure_callback(aligned_alloc_failure_callback);
    Tests.run("dbgmm_set_aligned_alloc_failure_callback", dbgmm_get_aligned_alloc_failure_callback() == aligned_alloc_failure_callback);
    
    Tests.run("dbgmm_get_realloc_success_callback", dbgmm_get_realloc_success_callback() == NULL);
    dbgmm_set_realloc_success_callback(realloc_success_callback);
    Tests.run("dbgmm_set_realloc_success_callback", dbgmm_get_realloc_success_callback() == realloc_success_callback);
    
    Tests.run("dbgmm_get_realloc_failure_callback", dbgmm_get_realloc_failure_callback() == NULL);
    dbgmm_set_realloc_failure_callback(realloc_failure_callback);
    Tests.run("dbgmm_set_realloc_failure_callback", dbgmm_get_realloc_failure_callback() == realloc_failure_callback);
    
    Tests.run("dbgmm_get_free_success_callback", dbgmm_get_free_success_callback() == NULL);
    dbgmm_set_free_success_callback(free_success_callback);
    Tests.run("dbgmm_set_free_success_callback", dbgmm_get_free_success_callback() == free_success_callback);
    
    Tests.run("dbgmm_get_free_failure_callback", dbgmm_get_free_failure_callback() == NULL);
    dbgmm_set_free_failure_callback(free_failure_callback);
    Tests.run("dbgmm_set_free_failure_callback", dbgmm_get_free_failure_callback() == free_failure_callback);
    
    dbgmm_audit();

    int sz = 1024 * sizeof(int);
    int* stack_arr = alloca(sz);
    Tests.run("alloca", assigned(stack_arr));
    stack_arr[0] = 1;
    Tests.print("Value: %d\n", stack_arr[0]);

    int* aligned_stack_arr = aligned_alloca(32, sz);
    Tests.run("aligned_alloca", assigned(aligned_stack_arr));
    aligned_stack_arr[0] = 2;
    Tests.print("Value: %d\n", aligned_stack_arr[0]);

    int* arr = malloc(sizeof(int) * 5);
    Tests.run("malloc", assigned(arr));
    arr[0] = 10;
    Tests.print("Value: %d\n", arr[0]);

    arr = realloc(arr, sizeof(int) * 10);
    Tests.run("realloc", assigned(arr));
    arr[1] = 20;
    Tests.print("Value: %d\n", arr[1]);

    int* arr2 = calloc(5, sizeof(int));
    Tests.run("calloc", assigned(arr2));
    Tests.print("Value (zeroed): %d\n", arr2[0]);

#ifdef __c11
    int* arra = aligned_alloc(32, sz);
    Tests.run("aligned_alloc", assigned(arra));
    arra[0] = 40;
    Tests.print("Value: %d\n", arra[0]);

    dbgmm_report(); // 3
    free(arra);
#endif
    dbgmm_report(); // 2
    free(arr);
    dbgmm_report(); // 1
    free(arr2);
    dbgmm_report(); // 0

    dbgmm_deaudit();
    dbgmm_report(); // NOTHING HAPPENS
    dbgmm_report(); // NOTHING HAPPENS
    dbgmm_report(); // NOTHING HAPPENS
    return Tests.end();
}

