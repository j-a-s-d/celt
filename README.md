# CeLT

C eXTRA LiBRARiES & TOOLS

> *NOTE: this is a work in progress, I'm still recycling my old code (with lots of parts that can't be published), so some aspects of the code may be left behind in some areas, same warning applies for tests and documentation so be patient. Also, this it's not intended for newbies at all, due to it's nature, you should know what are you doing by using any of this code, plus you should know how to read code and find your own answers.*

## MOTIVATION
> *"If you want more effective programmers, you will discover that they should not waste their time debugging, they should not introduce the bugs to starth with."*
- Edger Dijkstra, The Humble Programmer, 1972

## LIBRARIES

An opinionated mashup of decades of c code (with 2100+ test cases and 0 memory leaks/invalid memory accesses) structured in a bunch of libraries mostly for c99+, mostly for linux, mostly for gcc and clang, which doesn't use any external dependency (except indicated) not even libm/math.h (but it's compatible of course).
In all of this libraries, name casing is snake, data types are suffixed as _dt and function types (such as callback types) are suffixed as _fn.

* [`Ce`](libs/docs/ce.md) *mostly c89+ (plus some c99+ typedefs), for most compilers, only headers with macros and typedefs*

* [`MeH`](libs/docs/meh.md) *c99+, for gcc/clang, uses Ce, only headers with macros and static inline functions*
* [`GeM`](libs/docs/gem.md) *c99+, uses Ce, same as MeH but as independent files with special needs or purposes (ex. for clang linking BlocksRuntime)*

* [`KeWL`](libs/docs/kewl.md) *c99+, for gcc/clang, uses MeH, more headers and some .c files to add a bunch of useful functions and data types*
* [`GeST`](libs/docs/gest.md) *c99+, uses MeH, same as KeWL but as independent files with special needs or purposes (ex. for unix-like only)*

* [`WeRKS`](libs/docs/werks.md) *c99+, for gcc/clang, uses KeWL, collections (like a stringlist and a key-value map) and common advanced functionalities (like logging and internationalization)*
* [`PeRKS`](libs/docs/perks.md) *uses KeWL, same as WeRKS but as independent files with special needs or purposes (ex. for c11 or superior)*

## TOOLS

Also a selection of programs to work with c code in various ways featuring things that are not found in other tooling repositories.
None of this programs use any of the CeLT libraries, just in case you want this but not that.

* [`ceems`](tools/docs/ceems.md) *c code well-known includes good-enough inference tool*

* [`cinco`](tools/docs/cinco.md) *c include outfinding tool*

* [`chime`](tools/docs/chime.md) *c header included members explorer tool*

* [`cinex`](tools/docs/cinex.md) *c include expanding tool*

*IMPORTANT: every library, tool, demo, etc is fully tested with valgrind for memory leaks or illegal accesses before publishing.*

### HISTORY

* 15-feb-2026 -- *20260215L*
	- [KeWL] added `float_sin`, `double_sin`, `long_double_sin`, `float_cos`, `double_cos`, `long_double_cos`, `float_atan`, `double_atan`, `long_double_atan`, `float_atan2`, `double_atan2` and `long_double_atan2`
* 08-feb-2026 -- *20260208L*
	- [WeRKS] added `werks_stringlist_formatted_insert`
	- other minor adjustments
* 30-jan-2026 -- *20260130L*
	- [GeM] added `get_terminal_cursor_position`
	- [WeRKS] added `ANSI_CODE_CURSOR_REPOSITION_FORMAT ANSI_ESCAPE`, `ANSI_CODE_CURSOR_POSITION ANSI_ESCAPE`, `ANSI_CODE_CURSOR_HIDE ANSI_ESCAPE`, `ANSI_CODE_CURSOR_SHOW ANSI_ESCAPE` and `printf_at`
* 24-jan-2026 -- *20260124L*
	- [KeWL] added `string_array_consolidate_range`, `string_array_consolidate_with_sentinel` and `string_array_consolidate`
	- [WeRKS] added `werks_stringlist_consolidate`
* 18-jan-2026 -- *20260118L*
	- [KeWL] added `is_circular_point_before`, `bool_to_int_char`, `is_uppercase_char`, `is_lowercase_char`, `is_digit_char`, `is_uppercase_string` and `is_lowercase_string`
	- other minor adjustments
* 08-jan-2026 -- *20260108L*
	- [KeWL] added `get_days_between_time_t`, `get_days_between_ymd` and `get_days_between_datetime`
* 07-jan-2026 -- *20260107L*
	- [KeWL] added `unescape_single_chars`
	- [WeRKS] added `werks_stringlist_delete_first`
	- other minor adjustments
* 06-jan-2026 -- *20260106L*
	- [KeWL] added `is_ascii_readable_char` and `is_ascii_readable_string`
* 05-jan-2026 -- *20260105L*
	- [MeH] added `SIZED_ARRAY_EACH`
	- [WeRKS] added `werks_stringlist_remove_all_containing_any` and `werks_stringlist_remove_all_not_containing_any`
* 03-jan-2026 -- *20260103L*
	- [KeWL] added `kewl_ptrholder_sorter_fn`, `kewl_ptrholder_sort` and `kewl_ptrholder_reverse`
	- [WeRKS] added `werks_expreval_expressions_list_sort_by_value_ascending` and `werks_expreval_expressions_list_sort_by_value_descending`
* 02-jan-2026 -- *20260102L*
	- [Ce] added `qsort_comparator_fn`
	- [KeWL] added `get_circular_shortest_offset`
* 28-dec-2025 -- *20251228L*
	- [WeRKS] added `chunk_read_handler_with_reference_fn`, `read_binary_file_by_chunk_with_reference`, `line_read_handler_with_reference_fn`, `read_text_file_by_line_with_reference`, `byte_read_handler_with_reference_fn` and `read_binary_file_by_byte_with_reference`
* 23-dec-2025 -- *20251223L*
	- [WeRKS] added `werks_stringlist_formatted_set`
* 22-dec-2025 -- *20251222L*
	- [WeRKS] added `werks_expreval_expressions_list_get_current_value`
* 20-dec-2025 -- *20251220L*
	- [MeH] added `MEH_DEFAULT_SENTINEL_LIMIT`
	- [WeRKS] added `WERKS_EXPREVAL_TREATER_TYPE`, `werks_expreval_expressions_list_treat`, `werks_stringlist_from_array_with_sentinel` and `werks_expreval_expressions_list_add_from_array_with_size`
* 19-dec-2025 -- *20251219L*
	- [WeRKS] added `werks_expreval_expressions_list_loop_with_reference_handler_fn`, `werks_expreval_expressions_list_loop_with_reference`, `werks_expreval_expressions_list_reverse_loop_with_reference`, `werks_kvm_on_before_store_item_handler_fn`, `werks_kvm_set_on_before_store_item` and `werks_kvm_get_on_before_store_item`
* 18-dec-2025 -- *20251218L*
	- [WeRKS] added `werks_expreval_constants_set_all` and `werks_expreval_constants_drop_all`
* 17-dec-2025 -- *20251217L*
	- [KeWL] added `validate_numeric_xxcyy_string` and `replace_substring`
* 05-dec-2025 -- *20251205L*
	- [WeRKS] added `werks_kvm_untyped_treatment_dt`, `WERKS_KVM_UNTYPED_TREATMENT_DEFAULT`, `werks_kvm_get_untyped_treatment` and `werks_kvm_set_untyped_treatment`
* 01-dec-2025 -- *20251201L*
	- [KeWL] added `normalize_circular_angle`, `get_circular_opposite_point`, `is_circular_point_between`, `get_circular_distance` and `get_circular_offset_percentage_between`
	- other minor adjustments
* 24-nov-2025 -- *20251124L*
	- [MeH] added `MEH_DEFAULT_BUFFER_SIZE`
	- [KeWL] added `validate_numeric_xxcyyczz_string`, `validate_ddmmyyyy_date_string_format` and `validate_yyyymmdd_date_string_format`
	- other minor adjustments
* 21-nov-2025 -- *20251121L*
	- [MeH] added `free_and_null_array_items` and `FREE_ARRAY_ITEMS`
	- other minor adjustments
* 20-nov-2025 -- *20251120L*
	- [KeWL] added `string_array_with_sentinel_from_string_split`, `parse_xyz_shorts_string`, `parse_xyz_longs_string`, `parse_xyz_floats_string` and `parse_xyz_doubles_string`
* 16-nov-2025 -- *20251116L*
	- [WeRKS] added `werks_stringlist_remove_containing` and `werks_stringlist_remove_not_containing`
	- [KeWL] added `fill_datetime_with_now` and `parse_xyz_ints_string`
	- other minor adjustments
* 13-nov-2025 -- *20251113L*
	- [KeWL] added `make_datetime` and `datetime_*` macros to simplify the calling, `datetime_to_time_t`, `get_datetime_elapsed_time` and `fill_datetime_from_datetime`
	- other minor adjustments
* 11-nov-2025 -- *20251111L*
	- [MeH] added `float_round`, `double_round` and `long_double_round`
	- [KeWL] added `utc_decimal_hours_to_local_hms`
* 09-nov-2025 -- *20251109L*
	- [KeWL] added `copy_substring`
* 06-nov-2025 -- *20251106L*
	- [WeRKS] added `werks_stringlist_formatted_append` and `werks_stringlist_formatted_prepend`
	- [KeWL] added `datetime_alter_*` and alike simplifying macros to call `modify_datetime`
* 05-nov-2025 -- *20251105L*
	- [KeWL] added `day_shift` output flag to `local_hms_to_utc` and `local_hms_to_utc_decimal_hours`
	- other minor adjustments
* 04-nov-2025 -- *20251104L*
	- [WeRKS] added `werks_kvm_get_value`
	- [KeWL] added `debug_print`
	- other minor adjustments
* 03-nov-2025 -- *20251103L*
	- [WeRKS] added `werks_program_set_context`, `werks_program_get_context` and `werks_program_get_component`
	- other minor adjustments
* 02-nov-2025 -- *20251102L*
	- [KeWL] added `decimal_degrees_to_dms` and `dms_to_decimal_degrees`
* 31-oct-2025 -- *20251031L*
	- [KeWL] added `ymd_to_long_date`, `long_date_to_ymd`, `is_leap_year`, `get_days_in_month`, `modify_datetime`, `equal_datetimes` and `is_newer_datetime`
* 30-oct-2025 -- *20251030L*
	- [KeWL] added `local_hms_to_utc`, `local_hms_to_utc_decimal_hours`, `datetime_dt`, `fill_datetime_from_tm` and `get_now_datetime`
	- other minor adjustments
* 28-oct-2025 -- *20251028L*
	- [WeRKS] added `werks_kvm_export_to_json_object_string`
	- other minor adjustments
* 25-oct-2025 -- *20251025L*
	- [MeH] added `VALUE_DEGREES_TO_RADIANS`, `degrees_to_radians`, `VALUE_RADIANS_TO_DEGREES` and `radians_to_degrees`
	- other minor adjustments
* 23-oct-2025 -- *20251023L*
	- [KeWL] added `hms_to_decimal_hours` and `decimal_hours_to_hms`
* 20-oct-2025 -- *20251020L*
	- [WeRKS] added `werks_stringlist_reverse_treat` and `werks_stringlist_reverse_treat_with_reference`
	- other minor adjustments
* 19-oct-2025 -- *20251019L*
	- [Ce] added `both_assigned`
	- [KeWL] added `decode_utf8_escape`, `parse_json_strings_array` and  `parse_json_strings_array_with_reference`
	- [WeRKS] added `werks_stringlist_write_to_json_array_string` and `werks_stringlist_read_from_json_array_string`
	- other minor adjustments
* 14-oct-2025 -- *20251014L*
	- initial release

