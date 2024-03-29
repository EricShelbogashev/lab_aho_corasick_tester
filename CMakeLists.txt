cmake_minimum_required(VERSION 3.22)
project(lab_aho_corasick_tester C)

#set(CMAKE_C_STANDARD 99)

add_executable(lab_aho_corasick_tester testDriver.c testLab.h testLabAC.c)


cmake_minimum_required(VERSION 3.5)

#project(La C)

enable_testing()

find_library(MATH_LIBRARY m)

function(SET_COMPILER_SETTINGS target)
    cmake_parse_arguments(
            SET_COMPILER_SETTINGS
            ""
            "EXTENSIONS"
            ""
            ${ARGN}
    )

    set_target_properties(${target} PROPERTIES
            C_STANDARD 11
            C_STANDARD_REQUIRED YES
            C_EXTENSIONS ${SET_COMPILER_SETTINGS_EXTENSIONS}
            )

    target_compile_options(${target} PRIVATE
            $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>,$<C_COMPILER_ID:GNU>>:
            -Wall
            -Wextra
            -Wno-missing-field-initializers
            -pedantic
            -pedantic-errors
            >
            $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>>:
            -Weverything
            -Wno-padded
            -Wno-disabled-macro-expansion
            >
            $<$<C_COMPILER_ID:MSVC>:
            /W4
            >)

    target_compile_definitions(${target} PRIVATE
            $<$<BOOL:${MINGW}>:
            __USE_MINGW_ANSI_STDIO=1
            >
            $<$<C_COMPILER_ID:MSVC>:
            _CRT_SECURE_NO_WARNINGS=1
            >)

    if (MATH_LIBRARY)
        target_link_libraries(${target} PUBLIC ${MATH_LIBRARY})
    endif ()
endfunction()

add_library(testDriver testDriver.c)
# EXTENSIONS YES заменяет std=c11 на std=gnu11, что выставляет POSIX макросы
set_compiler_settings(testDriver EXTENSIONS YES)

set(TEST_LAB_SOURCES
        testlabAC.c
        )
foreach (source ${TEST_LAB_SOURCES})
    get_filename_component(target ${source} NAME_WE)
    add_executable(${target} ${source})
    set_compiler_settings(${target} EXTENSIONS NO)
    target_link_libraries(${target} PRIVATE testDriver)

    string(REPLACE "testlab" "lab" test ${target})
    add_test(NAME ${test}
            COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${target}"
            "${CMAKE_CURRENT_SOURCE_DIR}/test/${test}$<$<BOOL:${WIN32}>:.exe>")
endforeach ()