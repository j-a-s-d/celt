# CeLT

C eXTRA LiBRARiES & TOOLS

> *NOTE: this is a work in progress, I'm still recycling my old code (with lots of parts that can't be published), so some aspects of the code may be left behind in some areas, same warning applies for tests and documentation so be patient. Also, this it's not intended for newbies at all, due to it's nature, you should know what are you doing by using any of this code, plus you should know how to read code and find your own answers.*

## MOTIVATION
> *"If you want more effective programmers, you will discover that they should not waste their time debugging, they should not introduce the bugs to starth with."*
- Edger Dijkstra, The Humble Programmer, 1972

## LIBRARIES

An opinionated mashup of decades of c code (with ~1900 test cases and 0 memory leaks/invalid memory accesses) structured in a bunch of libraries mostly for c99+, mostly for linux, mostly for gcc and clang, which doesn't use any external dependency (except indicated) not even libm/math.h (but it's compatible of course).
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

