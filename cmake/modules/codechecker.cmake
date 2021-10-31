if (WIN32 AND (CMAKE_CXX_PLATFORM_ID MATCHES MinGW))
    add_custom_target(run_static_analysis
            COMMAND msys2_shell.cmd -defterm  -no-start -full-path -here  -c "bash ${CMAKE_CURRENT_LIST_DIR}/../scripts/generate_compile_commands_for_codechecker.sh compile_commands.json > static_analysis_compile_commands.json"
            COMMAND CodeChecker analyze static_analysis_compile_commands.json --analyzers clangsa  --enable sensitive --tidyargs ${CMAKE_CURRENT_LIST_DIR}/../scripts/extra_tidy_compile_flags.txt --output ${CMAKE_BINARY_DIR}/static_analysis_reports || exit 0
            VERBATIM
            USES_TERMINAL
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
    add_custom_target(parse_static_analysis_report
            COMMAND CodeChecker parse static_analysis_reports > static_analysis_report.txt || exit 0
            VERBATIM
            USES_TERMINAL
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
    add_custom_target(run_clang_tidy
            COMMAND msys2_shell.cmd -defterm  -no-start -full-path -here  -c "bash ${CMAKE_CURRENT_LIST_DIR}/../scripts/generate_compile_commands_for_codechecker.sh compile_commands.json > clang_tidy_compile_commands.json"
            COMMAND CodeChecker analyze clang_tidy_compile_commands.json --analyzers clang-tidy  --enable sensitive --tidyargs ${CMAKE_CURRENT_LIST_DIR}/../scripts/extra_tidy_compile_flags.txt --output ${CMAKE_BINARY_DIR}/clang_tidy_reports || exit 0
            VERBATIM
            USES_TERMINAL
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
    add_custom_target(parse_clang_tidy_result
            COMMAND CodeChecker parse clang_tidy_reports > clang_tidy_report.txt || exit 0
            VERBATIM
            USES_TERMINAL
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
else()
    add_custom_target(run_static_analysis
            COMMAND CodeChecker analyze compile_commands.json --analyzers clangsa --ignore ${CMAKE_CURRENT_LIST_DIR}/../scripts/codechecker_skip.list --enable sensitive --output static_analysis_reports || exit 0
            VERBATIM
            USES_TERMINAL
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
    add_custom_target(parse_static_analysis_report
            COMMAND CodeChecker parse static_analysis_reports > static_analysis_report.txt || exit 0
            VERBATIM
            USES_TERMINAL
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
    add_custom_target(run_clang_tidy
            COMMAND CodeChecker analyze compile_commands.json --analyzers clang-tidy --ignore ${CMAKE_CURRENT_LIST_DIR}/../scripts/codechecker_skip.list --enable sensitive --output clang_tidy_reports || exit 0
            VERBATIM
            USES_TERMINAL
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
    add_custom_target(parse_clang_tidy_report
            COMMAND CodeChecker parse clang_tidy_reports > clang_tidy_report.txt || exit 0
            VERBATIM
            USES_TERMINAL
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )

endif ()
