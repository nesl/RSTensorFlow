# Description:
#   JNI-based Java inference interface for TensorFlow.

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

exports_files(["LICENSE"])

load(
    "//tensorflow:tensorflow.bzl",
    "tf_copts",
    "if_android",
)

exports_files([
    "jni/version_script.lds",
])

filegroup(
    name = "rs_android_tensorflow_inference_jni_srcs",
    srcs = glob([
        "**/*.cc",
        "**/*.h",
    ]),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "rs_android_tensorflow_inference_jni",
    srcs = if_android([":rs_android_tensorflow_inference_jni_srcs"]),
    copts = tf_copts(),
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/core:android_tensorflow_lib_lite",
        "//tensorflow/java/src/main/native",
    ],
    alwayslink = 1,
)

filegroup(
    name = "all_files",
    srcs = glob(
        ["**/*"],
        exclude = [
            "**/METADATA",
            "**/OWNERS",
            "bin/**",
            "gen/**",
        ],
    ),
    visibility = ["//tensorflow:__subpackages__"],
)

# JAR with Java bindings to TF.
android_library(
    name = "rs_android_tensorflow_inference_java",
    srcs = glob(["java/**/RSTensorFlowInferenceInterface.java"]),
    tags = [
        "manual",
        "notap",
    ],
)

# Build the native .so.
# bazel build //tensorflow/contrib/android:libtensorflow_inference.so \
#   --crosstool_top=//external:android/crosstool \
#   --host_crosstool_top=@bazel_tools//tools/cpp:toolchain \
#   --cpu=armeabi-v7a
LINKER_SCRIPT = "//tensorflow/contrib/android:jni/version_script.lds"

cc_binary(
    name = "librstensorflow_inference.so",
    srcs = [],
    copts = tf_copts(),
    linkopts = if_android([
        "-landroid",
        "-llog",
        "-lm",
        "-z defs",
        "-s",
        "-Wl,--version-script",  # This line must be directly followed by LINKER_SCRIPT.
        LINKER_SCRIPT,
    ]),
    linkshared = 1,
    linkstatic = 1,
    tags = [
        "manual",
        "notap",
    ],
    deps = [
        ":rs_android_tensorflow_inference_jni",
        "//tensorflow/core:android_tensorflow_lib",
        LINKER_SCRIPT,
    ],
)
