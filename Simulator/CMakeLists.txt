find_program(PYTHON3 "python3")

if (PYTHON3)
    set(SETUP_PY_IN "setup.py.in")
    set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
    set(DEPS        "simulator")
    set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build/.stamp")

    configure_file(${SETUP_PY_IN} ${SETUP_PY})

    add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${PYTHON3} ${SETUP_PY} build
                       COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
                       DEPENDS ${DEPS})

    add_custom_target(simulator ALL DEPENDS ${OUTPUT})

    install(CODE "execute_process(COMMAND ${PYTHON3} ${SETUP_PY} install)")
endif()