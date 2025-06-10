configure_lit_site_cfg(
        ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
        MAIN_CONFIG
        ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
)

set(expt_OPT_TEST_DEPENDS
        FileCheck count not
        expt-opt
        )

add_lit_testsuite(check-expt-opt "Running the expt-opt regression tests"
        ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${expt_OPT_TEST_DEPENDS}
        )
set_target_properties(check-expt-opt PROPERTIES FOLDER "Tests")

add_lit_testsuites(expt_OPT ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS ${expt_OPT_TEST_DEPENDS})
