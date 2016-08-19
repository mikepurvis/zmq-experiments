if (NOT MSVC)
    include(FindPkgConfig)
    pkg_check_modules(PC_LIBZMQ "libzmq")
    if (NOT PC_LIBZMQ_FOUND)
        pkg_check_modules(PC_LIBZMQ "libzmq")
    endif (NOT PC_LIBZMQ_FOUND)
    if (PC_LIBZMQ_FOUND)
        # add CFLAGS from pkg-config file, e.g. draft api.
        add_definitions(${PC_LIBZMQ_CFLAGS} ${PC_LIBZMQ_CFLAGS_OTHER})
        set(PC_LIBZMQ_INCLUDE_HINTS ${PC_LIBZMQ_INCLUDE_DIRS})
        set(PC_LIBZMQ_LIBRARY_HINTS ${PC_LIBZMQ_LIBRARY_DIRS})
    endif(PC_LIBZMQ_FOUND)
endif (NOT MSVC)

find_path (
    LIBZMQ_INCLUDE_DIRS
    NAMES zmq.h
    HINTS ${PC_LIBZMQ_INCLUDE_HINTS}
)

find_library (
    LIBZMQ_LIBRARIES
    NAMES zmq libzmq.dylib
    HINTS ${PC_LIBZMQ_LIBRARY_HINTS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    LIBZMQ
    REQUIRED_VARS LIBZMQ_LIBRARIES LIBZMQ_INCLUDE_DIRS
)
mark_as_advanced(
    LIBZMQ_FOUND
    LIBZMQ_LIBRARIES LIBZMQ_INCLUDE_DIRS
)
