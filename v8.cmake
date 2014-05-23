set(V8_SOURCES_COMMON
	V8/src/accessors.cc
	V8/src/allocation-site-scopes.cc
	V8/src/allocation-tracker.cc
	V8/src/allocation.cc
	V8/src/api.cc
	V8/src/arguments.cc
	V8/src/assembler.cc
	V8/src/assert-scope.cc
	V8/src/ast.cc
	V8/src/bignum-dtoa.cc
	V8/src/bignum.cc
	V8/src/bootstrapper.cc
	V8/src/builtins.cc
	V8/src/cached-powers.cc
	V8/src/checks.cc
	V8/src/code-stubs-hydrogen.cc
	V8/src/code-stubs.cc
	V8/src/codegen.cc
	V8/src/compilation-cache.cc
	V8/src/compiler.cc
	V8/src/contexts.cc
	V8/src/conversions.cc
	V8/src/counters.cc
	V8/src/cpu-profiler.cc
	V8/src/cpu.cc
	V8/src/d8-debug.cc
	V8/src/d8.cc
	V8/src/data-flow.cc
	V8/src/date.cc
	V8/src/dateparser.cc
	V8/src/debug-agent.cc
	V8/src/debug.cc
	V8/src/deoptimizer.cc
	V8/src/disassembler.cc
	V8/src/diy-fp.cc
	V8/src/dtoa.cc
	V8/src/elements-kind.cc
	V8/src/elements.cc
	V8/src/execution.cc
	V8/src/factory.cc
	V8/src/fast-dtoa.cc
	V8/src/fixed-dtoa.cc
	V8/src/flags.cc
	V8/src/frames.cc
	V8/src/full-codegen.cc
	V8/src/func-name-inferrer.cc
	V8/src/global-handles.cc
	V8/src/handles.cc
	V8/src/heap-profiler.cc
	V8/src/heap-snapshot-generator.cc
	V8/src/heap.cc
	V8/src/hydrogen-bce.cc
	V8/src/hydrogen-bch.cc
	V8/src/hydrogen-canonicalize.cc
	V8/src/hydrogen-check-elimination.cc
	V8/src/hydrogen-dce.cc
	V8/src/hydrogen-dehoist.cc
	V8/src/hydrogen-environment-liveness.cc
	V8/src/hydrogen-escape-analysis.cc
	V8/src/hydrogen-gvn.cc
	V8/src/hydrogen-infer-representation.cc
	V8/src/hydrogen-infer-types.cc
	V8/src/hydrogen-instructions.cc
	V8/src/hydrogen-load-elimination.cc
	V8/src/hydrogen-mark-deoptimize.cc
	V8/src/hydrogen-mark-unreachable.cc
	V8/src/hydrogen-osr.cc
	V8/src/hydrogen-range-analysis.cc
	V8/src/hydrogen-redundant-phi.cc
	V8/src/hydrogen-removable-simulates.cc
	V8/src/hydrogen-representation-changes.cc
	V8/src/hydrogen-sce.cc
	V8/src/hydrogen-store-elimination.cc
	V8/src/hydrogen-uint32-analysis.cc
	V8/src/hydrogen.cc
	V8/src/ic.cc
	V8/src/icu_util.cc
	V8/src/incremental-marking.cc
	V8/src/interface.cc
	V8/src/interpreter-irregexp.cc
	V8/src/isolate.cc
	V8/src/jsregexp.cc
	V8/src/lithium-allocator.cc
	V8/src/lithium-codegen.cc
	V8/src/lithium.cc
	V8/src/liveedit.cc
	V8/src/log-utils.cc
	V8/src/log.cc
	V8/src/mark-compact.cc
	V8/src/messages.cc
	V8/src/mksnapshot.cc
	V8/src/objects-debug.cc
	V8/src/objects-printer.cc
	V8/src/objects-visiting.cc
	V8/src/objects.cc
	V8/src/once.cc
	V8/src/optimizing-compiler-thread.cc
	V8/src/parser.cc
	V8/src/preparse-data.cc
	V8/src/preparser.cc
	V8/src/prettyprinter.cc
	V8/src/profile-generator.cc
	V8/src/property.cc
	V8/src/regexp-macro-assembler-irregexp.cc
	V8/src/regexp-macro-assembler-tracer.cc
	V8/src/regexp-macro-assembler.cc
	V8/src/regexp-stack.cc
	V8/src/rewriter.cc
	V8/src/runtime-profiler.cc
	V8/src/runtime.cc
	V8/src/safepoint-table.cc
	V8/src/sampler.cc
	V8/src/scanner-character-streams.cc
	V8/src/scanner.cc
	V8/src/scopeinfo.cc
	V8/src/scopes.cc
	V8/src/serialize.cc
	V8/src/snapshot-common.cc
	V8/src/snapshot-empty.cc
	V8/src/spaces.cc
	V8/src/store-buffer.cc
	V8/src/string-search.cc
	V8/src/string-stream.cc
	V8/src/strtod.cc
	V8/src/stub-cache.cc
	V8/src/sweeper-thread.cc
	V8/src/token.cc
	V8/src/transitions.cc
	V8/src/type-info.cc
	V8/src/types.cc
	V8/src/typing.cc
	V8/src/unicode.cc
	V8/src/utils.cc
	V8/src/v8-counters.cc
	V8/src/v8.cc
	V8/src/v8dll-main.cc
	V8/src/v8threads.cc
	V8/src/variables.cc
	V8/src/version.cc
	V8/src/win32-math.cc
	V8/src/zone.cc
#	V8/src/platform/condition-variable.cc
#	V8/src/platform/mutex.cc
#	V8/src/platform/semaphore.cc
#	V8/src/platform/socket.cc
#	V8/src/platform/time.cc
)

if(WIN32)
list(APPEND V8_SOURCES_COMMON V8/src/d8-windows.cc)
else()
list(APPEND V8_SOURCES_COMMON V8/src/d8-posix.cc)
endif()

if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86|i686") 
list(APPEND V8_SOURCES_COMMON V8/src/atomicops_internals_x86_gcc.cc)
endif()

if(WIN32)
set(V8_SOURCES_PLATFORM V8/src/platform-win32.cc)
endif()

IF("${CMAKE_SYSTEM}" MATCHES "Linux")
set(V8_SOURCES_PLATFORM	V8/src/platform-linux.cc)
endif()

#	V8/src/platform-cygwin.cc
#	V8/src/platform-freebsd.cc
#	V8/src/platform-macos.cc
#	V8/src/platform-openbsd.cc
#	V8/src/platform-posix.cc
#	V8/src/platform-qnx.cc
#	V8/src/platform-solaris.cc
#	V8/src/platform-win32.cc

file(GLOB V8_SOURCES_OTHERS "V8/src/*/*.cc")

add_library(v8 STATIC ${V8_SOURCES_COMMON} ${V8_SOURCES_PLATFORM} ${V8_SOURCES_OTHERS})

target_include_directories(v8 PRIVATE V8/src)
