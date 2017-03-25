package(
    default_visibility = [
        "//visibility:public",
    ],
)

filegroup(
    name = "rs_lib_a",
    srcs = glob([
        "so/*.a",
    ]),
)

filegroup(
    name = "rs_lib_so",
    srcs = glob([
        "so/*.so",
    ]),
)

filegroup(
    name = "rs_lib_hdrs",
    srcs = glob(["cpp/**/*.h"]),
)

cc_library(
    name = "rs_native_lib",
    srcs = [
        ":rs_lib_a",
        ":rs_lib_so",
    ],
    hdrs = [
        ":rs_lib_hdrs",
    ],
    linkstatic = 1,
)