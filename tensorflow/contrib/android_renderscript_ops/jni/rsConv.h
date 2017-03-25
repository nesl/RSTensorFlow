//
// Created by WangYingnan on 3/12/17.
//

#ifndef RSKERNELSTEST_RSCONV_H
#define RSKERNELSTEST_RSCONV_H

#include "tensorflow/contrib/android_renderscript_ops/jni/RScommon.h"
#include "tensorflow/contrib/android_renderscript_ops/jni/ScriptC_mScriptConv.h"


namespace androidrs {

namespace conv {

struct rsConvInfo{
    int in_depth;
    int input_rows;
    int input_cols;

    int filter_rows;
    int filter_cols;

    int stride_rows;
    int stride_cols;

    int pad_rows;
    int pad_cols;

    int out_depth;
    int out_rows;
    int out_cols;

    int batch;
    int data_format; // 4 F32, 1 U8

    rsConvInfo(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10, int n11, int n12, int n13, int n14){
        in_depth=n1;
        input_rows=n2;
        input_cols=n3;
        filter_rows=n4;filter_cols=n5;
        stride_rows=n6;stride_cols=n7;
        pad_rows=n8;pad_cols=n9;
        out_depth=n10;out_rows=n11;out_cols=n12;
        batch=n13;data_format=n14;
    };
};

static sp<RS> mRS = new RS();
static const char* cachePath = "/data/user/0/org.tensorflow.demo/cache";
static int count = 0; 

sp<ScriptC_mScriptConv>& initSC()
{
    static sp<ScriptC_mScriptConv> sc = new ScriptC_mScriptConv(androidrs::conv::mRS);
    return sc;
}

sp<Allocation>& initAlloc(int idx, int type)
{
    static sp<const Element> e = Element::F32(androidrs::conv::mRS);
    // conv1
    static sp<const Type> conv1_filters_t = Type::create(androidrs::conv::mRS, e, 3 * 7 * 7 * 64, 0, 0);
    static sp<const Type> conv1_inputs_t = Type::create(androidrs::conv::mRS, e, 3 * 224 * 224, 0, 0);
    static sp<const Type> conv1_outputs_t = Type::create(androidrs::conv::mRS, e, 64 * 112 * 112, 0, 0);
    static sp<Allocation> conv1_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv1_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv1_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv1_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv1_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv1_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv2
    static sp<const Type> conv2_filters_t = Type::create(androidrs::conv::mRS, e, 64 * 1 * 1 * 64, 0, 0);
    static sp<const Type> conv2_inputs_t = Type::create(androidrs::conv::mRS, e, 64 * 56 * 56, 0, 0);
    static sp<const Type> conv2_outputs_t = Type::create(androidrs::conv::mRS, e, 64 * 56 * 56, 0, 0);
    static sp<Allocation> conv2_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv2_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv2_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv2_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv2_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv2_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv3
    static sp<const Type> conv3_filters_t = Type::create(androidrs::conv::mRS, e, 64 * 3 * 3 * 192, 0, 0);
    static sp<const Type> conv3_inputs_t = Type::create(androidrs::conv::mRS, e, 64 * 56 * 56, 0, 0);
    static sp<const Type> conv3_outputs_t = Type::create(androidrs::conv::mRS, e, 192 * 56 * 56, 0, 0);
    static sp<Allocation> conv3_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv3_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv3_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv3_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv3_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv3_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv4
    static sp<const Type> conv4_filters_t = Type::create(androidrs::conv::mRS, e, 192 * 1 * 1 * 16, 0, 0);
    static sp<const Type> conv4_inputs_t = Type::create(androidrs::conv::mRS, e, 192 * 28 * 28, 0, 0);
    static sp<const Type> conv4_outputs_t = Type::create(androidrs::conv::mRS, e, 16 * 28 * 28, 0, 0);
    static sp<Allocation> conv4_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv4_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv4_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv4_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv4_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv4_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv5
    static sp<const Type> conv5_filters_t = Type::create(androidrs::conv::mRS, e, 16 * 5 * 5 * 32, 0, 0);
    static sp<const Type> conv5_inputs_t = Type::create(androidrs::conv::mRS, e, 16 * 28 * 28, 0, 0);
    static sp<const Type> conv5_outputs_t = Type::create(androidrs::conv::mRS, e, 32 * 28 * 28, 0, 0);
    static sp<Allocation> conv5_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv5_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv5_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv5_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv5_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv5_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv6
    static sp<const Type> conv6_filters_t = Type::create(androidrs::conv::mRS, e, 192 * 1 * 1 * 96, 0, 0);
    static sp<const Type> conv6_inputs_t = Type::create(androidrs::conv::mRS, e, 192 * 28 * 28, 0, 0);
    static sp<const Type> conv6_outputs_t = Type::create(androidrs::conv::mRS, e, 96 * 28 * 28, 0, 0);
    static sp<Allocation> conv6_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv6_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv6_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv6_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv6_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv6_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv7
    static sp<const Type> conv7_filters_t = Type::create(androidrs::conv::mRS, e, 96 * 3 * 3 * 128, 0, 0);
    static sp<const Type> conv7_inputs_t = Type::create(androidrs::conv::mRS, e, 96 * 28 * 28, 0, 0);
    static sp<const Type> conv7_outputs_t = Type::create(androidrs::conv::mRS, e, 128 * 28 * 28, 0, 0);
    static sp<Allocation> conv7_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv7_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv7_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv7_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv7_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv7_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv8
    static sp<const Type> conv8_filters_t = Type::create(androidrs::conv::mRS, e, 192 * 1 * 1 * 64, 0, 0);
    static sp<const Type> conv8_inputs_t = Type::create(androidrs::conv::mRS, e, 192 * 28 * 28, 0, 0);
    static sp<const Type> conv8_outputs_t = Type::create(androidrs::conv::mRS, e, 64 * 28 * 28, 0, 0);
    static sp<Allocation> conv8_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv8_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv8_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv8_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv8_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv8_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv9
    static sp<const Type> conv9_filters_t = Type::create(androidrs::conv::mRS, e, 192 * 1 * 1 * 32, 0, 0);
    static sp<const Type> conv9_inputs_t = Type::create(androidrs::conv::mRS, e, 192 * 28 * 28, 0, 0);
    static sp<const Type> conv9_outputs_t = Type::create(androidrs::conv::mRS, e, 32 * 28 * 28, 0, 0);
    static sp<Allocation> conv9_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv9_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv9_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv9_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv9_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv9_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv10
    static sp<const Type> conv10_filters_t = Type::create(androidrs::conv::mRS, e, 256 * 1 * 1 * 64, 0, 0);
    static sp<const Type> conv10_inputs_t = Type::create(androidrs::conv::mRS, e, 256 * 28 * 28, 0, 0);
    static sp<const Type> conv10_outputs_t = Type::create(androidrs::conv::mRS, e, 64 * 28 * 28, 0, 0);
    static sp<Allocation> conv10_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv10_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv10_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv10_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv10_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv10_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv11
    static sp<const Type> conv11_filters_t = Type::create(androidrs::conv::mRS, e, 256 * 1 * 1 * 32, 0, 0);
    static sp<const Type> conv11_inputs_t = Type::create(androidrs::conv::mRS, e, 256 * 28 * 28, 0, 0);
    static sp<const Type> conv11_outputs_t = Type::create(androidrs::conv::mRS, e, 32 * 28 * 28, 0, 0);
    static sp<Allocation> conv11_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv11_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv11_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv11_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv11_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv11_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv12
    static sp<const Type> conv12_filters_t = Type::create(androidrs::conv::mRS, e, 32 * 5 * 5 * 96, 0, 0);
    static sp<const Type> conv12_inputs_t = Type::create(androidrs::conv::mRS, e, 32 * 28 * 28, 0, 0);
    static sp<const Type> conv12_outputs_t = Type::create(androidrs::conv::mRS, e, 96 * 28 * 28, 0, 0);
    static sp<Allocation> conv12_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv12_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv12_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv12_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv12_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv12_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv13
    static sp<const Type> conv13_filters_t = Type::create(androidrs::conv::mRS, e, 256 * 1 * 1 * 128, 0, 0);
    static sp<const Type> conv13_inputs_t = Type::create(androidrs::conv::mRS, e, 256 * 28 * 28, 0, 0);
    static sp<const Type> conv13_outputs_t = Type::create(androidrs::conv::mRS, e, 128 * 28 * 28, 0, 0);
    static sp<Allocation> conv13_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv13_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv13_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv13_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv13_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv13_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv14
    static sp<const Type> conv14_filters_t = Type::create(androidrs::conv::mRS, e, 128 * 3 * 3 * 192, 0, 0);
    static sp<const Type> conv14_inputs_t = Type::create(androidrs::conv::mRS, e, 128 * 28 * 28, 0, 0);
    static sp<const Type> conv14_outputs_t = Type::create(androidrs::conv::mRS, e, 192 * 28 * 28, 0, 0);
    static sp<Allocation> conv14_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv14_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv14_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv14_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv14_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv14_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv15
    static sp<const Type> conv15_filters_t = Type::create(androidrs::conv::mRS, e, 256 * 1 * 1 * 128, 0, 0);
    static sp<const Type> conv15_inputs_t = Type::create(androidrs::conv::mRS, e, 256 * 28 * 28, 0, 0);
    static sp<const Type> conv15_outputs_t = Type::create(androidrs::conv::mRS, e, 128 * 28 * 28, 0, 0);
    static sp<Allocation> conv15_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv15_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv15_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv15_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv15_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv15_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv16
    static sp<const Type> conv16_filters_t = Type::create(androidrs::conv::mRS, e, 480 * 1 * 1 * 64, 0, 0);
    static sp<const Type> conv16_inputs_t = Type::create(androidrs::conv::mRS, e, 480 * 14 * 14, 0, 0);
    static sp<const Type> conv16_outputs_t = Type::create(androidrs::conv::mRS, e, 64 * 14 * 14, 0, 0);
    static sp<Allocation> conv16_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv16_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv16_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv16_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv16_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv16_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv17
    static sp<const Type> conv17_filters_t = Type::create(androidrs::conv::mRS, e, 480 * 1 * 1 * 16, 0, 0);
    static sp<const Type> conv17_inputs_t = Type::create(androidrs::conv::mRS, e, 480 * 14 * 14, 0, 0);
    static sp<const Type> conv17_outputs_t = Type::create(androidrs::conv::mRS, e, 16 * 14 * 14, 0, 0);
    static sp<Allocation> conv17_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv17_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv17_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv17_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv17_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv17_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv18
    static sp<const Type> conv18_filters_t = Type::create(androidrs::conv::mRS, e, 16 * 5 * 5 * 48, 0, 0);
    static sp<const Type> conv18_inputs_t = Type::create(androidrs::conv::mRS, e, 16 * 14 * 14, 0, 0);
    static sp<const Type> conv18_outputs_t = Type::create(androidrs::conv::mRS, e, 48 * 14 * 14, 0, 0);
    static sp<Allocation> conv18_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv18_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv18_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv18_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv18_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv18_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv19
    static sp<const Type> conv19_filters_t = Type::create(androidrs::conv::mRS, e, 480 * 1 * 1 * 96, 0, 0);
    static sp<const Type> conv19_inputs_t = Type::create(androidrs::conv::mRS, e, 480 * 14 * 14, 0, 0);
    static sp<const Type> conv19_outputs_t = Type::create(androidrs::conv::mRS, e, 96 * 14 * 14, 0, 0);
    static sp<Allocation> conv19_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv19_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv19_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv19_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv19_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv19_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv20
    static sp<const Type> conv20_filters_t = Type::create(androidrs::conv::mRS, e, 96 * 3 * 3 * 204, 0, 0);
    static sp<const Type> conv20_inputs_t = Type::create(androidrs::conv::mRS, e, 96 * 14 * 14, 0, 0);
    static sp<const Type> conv20_outputs_t = Type::create(androidrs::conv::mRS, e, 204 * 14 * 14, 0, 0);
    static sp<Allocation> conv20_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv20_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv20_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv20_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv20_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv20_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv21
    static sp<const Type> conv21_filters_t = Type::create(androidrs::conv::mRS, e, 480 * 1 * 1 * 192, 0, 0);
    static sp<const Type> conv21_inputs_t = Type::create(androidrs::conv::mRS, e, 480 * 14 * 14, 0, 0);
    static sp<const Type> conv21_outputs_t = Type::create(androidrs::conv::mRS, e, 192 * 14 * 14, 0, 0);
    static sp<Allocation> conv21_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv21_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv21_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv21_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv21_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv21_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // conv22
    static sp<const Type> conv22_filters_t = Type::create(androidrs::conv::mRS, e, 508 * 1 * 1 * 128, 0, 0);
    static sp<const Type> conv22_inputs_t = Type::create(androidrs::conv::mRS, e, 508 * 4 * 4, 0, 0);
    static sp<const Type> conv22_outputs_t = Type::create(androidrs::conv::mRS, e, 128 * 4 * 4, 0, 0);
    static sp<Allocation> conv22_filters_alloc = Allocation::createTyped(androidrs::conv::mRS, conv22_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv22_inputs_alloc = Allocation::createTyped(androidrs::conv::mRS,  conv22_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> conv22_outputs_alloc = Allocation::createTyped(androidrs::conv::mRS, conv22_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    switch (idx)
    {
    case 0:
        switch(type){
            case 0: return conv1_filters_alloc;
            case 1: return conv1_inputs_alloc;
            case 2: return conv1_outputs_alloc;
        }
    case 1:
        switch(type){
            case 0: return conv2_filters_alloc;
            case 1: return conv2_inputs_alloc;
            case 2: return conv2_outputs_alloc;
        }
    case 2:
        switch(type){
            case 0: return conv3_filters_alloc;
            case 1: return conv3_inputs_alloc;
            case 2: return conv3_outputs_alloc;
        }
    case 3:
        switch(type){
            case 0: return conv4_filters_alloc;
            case 1: return conv4_inputs_alloc;
            case 2: return conv4_outputs_alloc;
        }
    case 4:
        switch(type){
            case 0: return conv5_filters_alloc;
            case 1: return conv5_inputs_alloc;
            case 2: return conv5_outputs_alloc;
        }
    case 5:
        switch(type){
            case 0: return conv6_filters_alloc;
            case 1: return conv6_inputs_alloc;
            case 2: return conv6_outputs_alloc;
        }
    case 6:
        switch(type){
            case 0: return conv7_filters_alloc;
            case 1: return conv7_inputs_alloc;
            case 2: return conv7_outputs_alloc;
        }
    case 7:
        switch(type){
            case 0: return conv8_filters_alloc;
            case 1: return conv8_inputs_alloc;
            case 2: return conv8_outputs_alloc;
        }
    case 8:
        switch(type){
            case 0: return conv9_filters_alloc;
            case 1: return conv9_inputs_alloc;
            case 2: return conv9_outputs_alloc;
        }
    case 9:
        switch(type){
            case 0: return conv10_filters_alloc;
            case 1: return conv10_inputs_alloc;
            case 2: return conv10_outputs_alloc;
        }
    case 10:
        switch(type){
            case 0: return conv11_filters_alloc;
            case 1: return conv11_inputs_alloc;
            case 2: return conv11_outputs_alloc;
        }
    case 11:
        switch(type){
            case 0: return conv12_filters_alloc;
            case 1: return conv12_inputs_alloc;
            case 2: return conv12_outputs_alloc;
        }
    case 12:
        switch(type){
            case 0: return conv13_filters_alloc;
            case 1: return conv13_inputs_alloc;
            case 2: return conv13_outputs_alloc;
        }
    case 13:
        switch(type){
            case 0: return conv14_filters_alloc;
            case 1: return conv14_inputs_alloc;
            case 2: return conv14_outputs_alloc;
        }
    case 14:
        switch(type){
            case 0: return conv15_filters_alloc;
            case 1: return conv15_inputs_alloc;
            case 2: return conv15_outputs_alloc;
        }
    case 15:
        switch(type){
            case 0: return conv16_filters_alloc;
            case 1: return conv16_inputs_alloc;
            case 2: return conv16_outputs_alloc;
        }
    case 16:
        switch(type){
            case 0: return conv17_filters_alloc;
            case 1: return conv17_inputs_alloc;
            case 2: return conv17_outputs_alloc;
        }
    case 17:
        switch(type){
            case 0: return conv18_filters_alloc;
            case 1: return conv18_inputs_alloc;
            case 2: return conv18_outputs_alloc;
        }
    case 18:
        switch(type){
            case 0: return conv19_filters_alloc;
            case 1: return conv19_inputs_alloc;
            case 2: return conv19_outputs_alloc;
        }
    case 19:
        switch(type){
            case 0: return conv20_filters_alloc;
            case 1: return conv20_inputs_alloc;
            case 2: return conv20_outputs_alloc;
        }
    case 20:
        switch(type){
            case 0: return conv21_filters_alloc;
            case 1: return conv21_inputs_alloc;
            case 2: return conv21_outputs_alloc;
        }
    case 21:
        switch(type){
            case 0: return conv22_filters_alloc;
            case 1: return conv22_inputs_alloc;
            case 2: return conv22_outputs_alloc;
        }
    }
}

template <typename T>
void rsConv_script(void* filter, void* input, void* output, rsConvInfo convInfo)
{
    int idx = count%22;
    if(!androidrs::conv::mRS->getContext()){
        androidrs::conv::mRS->init(androidrs::conv::cachePath);
    }

    sp<Allocation > allFilters_alloc = initAlloc(idx, 0);
    sp<Allocation > allInputs_alloc = initAlloc(idx, 1);
    sp<Allocation > allOutputs_alloc = initAlloc(idx, 2);

    allFilters_alloc->copy1DFrom(filter);
    allInputs_alloc->copy1DFrom(input);

    sp<ScriptC_mScriptConv> sc = initSC();

    //kernel
    sc->set_in_depth(convInfo.in_depth);
    sc->set_input_rows(convInfo.input_rows);
    sc->set_input_cols(convInfo.input_cols);
    sc->set_filter_rows(convInfo.filter_rows);
    sc->set_filter_cols(convInfo.filter_cols);
    sc->set_stride_rows(convInfo.stride_rows);
    sc->set_stride_cols(convInfo.stride_cols);
    sc->set_pad_rows(convInfo.pad_rows);
    sc->set_pad_cols(convInfo.pad_cols);
    sc->set_out_depth(convInfo.out_depth);
    sc->set_out_rows(convInfo.out_rows);
    sc->set_out_cols(convInfo.out_cols);

    sc->set_filters(allFilters_alloc);
    sc->set_inputs(allInputs_alloc);
    sc->invoke_initParam();

    sc->forEach_launchConvF32(allOutputs_alloc);

    // sync
    allOutputs_alloc->copy1DTo(output);
    count++;
};

}
}


#endif //RSKERNELSTEST_RSCONV_H