# RenderScript Supported TensorFlow Ops
Enable float percison `matmul_op` and `conv_op` computing on Android GPU with RenderScript support. Details can be see at [Deep Learning with Low Power Consumption and Parallel Computation On Android Device](https://sites.google.com/a/g.ucla.edu/tflowp/).  

This package contains two RenderScript ops: `rsMatmul_sgemm` and `rsConv_script`. We can replace the default Eigen computation with these two functions. And the current modification is only targeting on the Inception V1 model inside the TF Classify app.
* rsMatmul_sgemm (data type: float)
* rsConv_script (data type: float, uint8_t)
* rsMatmul_bnnm (data type: uint8_t. Not included, currently has issue with RenderScript API miss matching with TF, might be fixed in the [future update of NDK](https://github.com/android-ndk/ndk/issues/331#issuecomment-287979565))

## Build with RenderScript support
* `git clone -b RenderScript https://github.com/EE202B/tensorflow.git` The current RenderScript modification is based on TF r1.1
* Make sure your `bazel` version is `0.4.3`. Building with `0.4.5` has troubles and has been filed an issue here [0.4.5 build issue](https://github.com/tensorflow/tensorflow/commit/fba05c300bf6840e76787680ed7fd1239cdb9ad0#commitcomment-21467983). Run `bazel version` first, if not `0.4.3` run `brew switch bazel 0.4.3` or install the binary installer from [Bazel GitHub Release page](https://github.com/bazelbuild/bazel/releases/tag/0.4.3).
* Follow the [original Android example](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/examples/android) to setup the `WORKSPACE`.  

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
* If use custom model (not Inception5h) or custom app (not org.tensorflow.demo), you must change the number of the `matmul` ops and `conv` ops at `androidrs::matmul` and `androidrs::conv`. Also change the package name to your own within these two namespaces. This hardcoding issue might be removed in future update. 
* Build with bazel:  
    `bazel build -c opt //tensorflow/examples/android:tensorflow_demo`
* Finally install to android phone:  
    `adb install -r bazel-bin/tensorflow/examples/android/tensorflow_demo.apk`
* `adb logcat -s TF_ANDROID_LOG` to see the time consumption of `conv_op` and `matmul_op`.

The currently build is for `armeabi-v7a` only. The RenderScript library, RS prebuilt binary and the bazel build are all set to `armeabi-v7a`. If you need to build for any other architecture, you need to change all these three things.


## RenderScript Runtime Device
 * The RenderScript ops can running on both GPU and CPU and running on GPU or not cannot be controlled by the developer. 
 * During our experiment, on Qualcomm processor it will automatically load the GPU runtime library `libRSDriver-adreno.so` and running on GPU.
 * If you want to force RenderScript running on CPU you can run `adb shell setprop debug.rs.default-CPU-driver 1`. Reference: [Force RS running on CPU](http://stackoverflow.com/questions/18753935/forcing-renderscript-to-run-on-cpu-or-gpu-atleast-for-performance-tuning-purpos).


## Prebuilt apk  
Download: [Prebuilt APK](https://www.dropbox.com/s/iwo31agtpsgyuhh/tensorflow_demo.apk?dl=0)  

In our case, the app works on Nexus6 with Android 7.0 but crash on Nexus5 with android 6.0. This may also apply to the building procedure above.


## Stand-alone RenderScript ops test
You can find a ops test app here: [RenderScriptOps](https://github.com/EE202B/RenderScriptOps). The test data are fetched from TF Classify app runtime.

## Issue
In comparison with the default eigen version, our renderscript supported app runs slower on the app level, but for the actual op time consumption, our app has 3x speed up when running on GPU. The rough test result can be seen at `doc/test-result.txt`. We believe this is caused by the app's Java level code. We will keep working on this to avoid the app level delay and provide a more professional test later.

## Documentation
For more implementation detail you can checkout the ppt in the `doc` folder.  

## GEMMLowp version  
Another alternative method to enhance the TensorFlow on Android is using `GEMMLowp` model instead of eigen.

* You need to first fetch the original eigen model:
    `curl https://storage.googleapis.com/download.tensorflow.org/models/inception5h.zip`
* Then use the [quantize_graph](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/tools/quantization) tool to generate the eight-bit model.

    ```
    bazel build tensorflow/tools/quantization:quantize_graph \
    && bazel-bin/tensorflow/tools/quantization/quantize_graph \
    --input=YOUR_EIGEN_MODEL.pb \
    --output_node_names = OUTPUT_NODE_NAMES_OF_YOUR_GEMMLOWP_MODEL \  
    --output=/tmp/YOUR_GEMMLOWP_MODEL.pb \
    --mode=eightbit
    ```
* Then puts your generated pb file into `tensorflow/tensorflow/examples/android/assets/`
* Finally modify the app's Java code in `tensorflow/tensorflow/examples/android/src/org/tensorflow/demo/ClassifierActivity.java`
    ```
    private static final int INPUT_SIZE = 224;
    private static final int IMAGE_MEAN = 117;
    private static final float IMAGE_STD = 1;
    private static final String INPUT_NAME = "input" ;
    private static final String OUTPUT_NAME = "OUTPUT_NODE_NAMES_OF_YOUR_GEMMLOWP_MODEL"; 
    private static final String MODEL_FILE = "file:///android_asset/YOUR_GEMMLOWP_MODEL.pb";
    private static final String LABEL_FILE = "file:///android_asset/imagenet_comp_graph_label_strings.txt";
    ```
* Then you should be able to build with `bazel build -c opt //tensorflow/examples/android:tensorflow_demo`  

We found out that GEMMLowp model is 2x slower than the eigen model due to have more conv layers, but the power consumption is less than eigen. More detail can be seen in our document.

## Useful tips  
* When running TF app, push the volume control buttom of the phone
* Using `trepn profiler` to monitor the perfoemance of the app.