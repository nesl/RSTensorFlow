package(
    default_visibility = [
        "//visibility:public",
    ],
)

filegroup(
    name = "rs_ndkbuilt_hdrs",
    srcs = glob(["jni/**/*.h"]),
)

filegroup(
    name = "rs_ndkbuilt_cpp",
    srcs = glob(["jni/**/*.cpp"]),
)

filegroup(
    name = "rs_ndkbuilt_o",
    srcs = glob(["jni/**/*.o"]),
)

cc_library(
    name = "rs_ops_ndkbuilt",
    srcs = [
        ":rs_ndkbuilt_o",
    ],
    hdrs = [
        ":rs_ndkbuilt_hdrs",
    ],
    deps = [
        "//tensorflow/contrib/android_renderscript_ops/rs:rs_native_lib",
    ],
    linkstatic = 1,
)


filegroup(
    name = "android_rs_ops_utils_srcs",
    srcs = glob(["utils/*.cpp"]),
)

filegroup(
    name = "android_rs_ops_utils_hdrs",
    srcs = glob(["utils/*.h"]),
)

cc_library(
    name = "android_rs_ops_utils",
    srcs = [
        ":android_rs_ops_utils_srcs",
    ],
    hdrs = [
        ":android_rs_ops_utils_hdrs",
    ],
    linkstatic = 1,
)