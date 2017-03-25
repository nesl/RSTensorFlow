# RenderScript implemented float precision ops
Enable matmul and conv ops computing on Android GPU. Details can be see [Deep Learning with Low Power Consumption and Parallel Computation On Android Device](https://sites.google.com/a/g.ucla.edu/tflowp/).  

This package contains two RenderScript ops. We can replace the default Eigen computation with these two function.
* rsMatmul_sgemm
* rsConv_script

## How to enable built with RenderScript
* First make sure your `bazel` version is `0.4.3`. Build with `0.4.5` has troubles and is issued here [0.4.5 build issue](https://github.com/tensorflow/tensorflow/commit/fba05c300bf6840e76787680ed7fd1239cdb9ad0#commitcomment-21467983)
* Follow the [original Android example](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/examples/android) setup the `WORKSPACE`.  
Our setup on OS X is:

```
android_sdk_repository(
    name = "androidsdk",
    path = "/Users/USERNAME/Library/Android/sdk",
    api_level = 23,
    build_tools_version="25.0.2"
)
android_ndk_repository(
    name = "androidndk",
    # Replace with path to Android NDK on your system
    path = "/Users/USERNAME/Library/Android/sdk/ndk-bundle",
    # Replace with the Android NDK API level
    api_level = 14
)
```

* Find all the keyword `renderscript support` in the project and uncomment all these blocks. There should be 4 files contain this keyword:
    * tensorflow/tensorflow/core/kernels/conv_ops.cc
    * tensorflow/tensorflow/core/kernels/matmul_op.cc
    * tensorflow/tensorflow/core/kernels/BUILD
    * tensorflow/tensorflow/examples/android/BUILD  

  Don't forget to uncomment the header inclusion in both op source files!
* Build with bazel:  
    `bazel build -c opt //tensorflow/examples/android:tensorflow_demo`
* Finally install to android phone:  
    `adb install -r bazel-bin/tensorflow/examples/android/tensorflow_demo.apk`
* This currently works for `armeabi-v7a` device, for other abi support you can change the hardcoded setup inside.


## RenderScript Device
The RenderScript ops can running on both GPU and CPU and this cannot be controlled by the developer. During our experiment, on Qualcomm processor it will load the 


## Prebuilt apk  
[Prebuilt APK](https://www.dropbox.com/s/iwo31agtpsgyuhh/tensorflow_demo.apk?dl=0)