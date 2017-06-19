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
static sp<ScriptC_mScriptConv> sc = nullptr;
static const char* cachePath = kCachePath;
//static const char* cachePath = "/data/user/0/org.tensorflow.demo/cache";
static int tot_conv_cnt = 22; 
static int count = 0; 
//static std::vector<sp<Allocation>> allFilters_alloc_vec;
//static std::vector<sp<Allocation>> allInputs_alloc_vec;
//static std::vector<sp<Allocation>> allOutputs_alloc_vec;

sp<ScriptC_mScriptConv>& initSC()
{
    if (sc == nullptr) {
    sc = new ScriptC_mScriptConv(androidrs::conv::mRS);
    // LOG(INFO) << "Initialized ConvScript.\n";
    }
    return sc;
}

template <typename T>
void rsConv_script(void* filter, void* input, void* output, rsConvInfo convInfo)
{
    int idx = count%tot_conv_cnt;

    if(!androidrs::conv::mRS->getContext()){
        androidrs::conv::mRS->init(androidrs::conv::cachePath);
    }

     // if(count<tot_conv_cnt){
        static sp<const Element> e = Element::F32(androidrs::conv::mRS);

        // alloc filter
        sp<const Type> all_filters_t = Type::create(androidrs::conv::mRS, e, convInfo.out_depth * convInfo.in_depth * convInfo.filter_rows * convInfo.filter_cols,
                                                        0,
                                                        0);
        sp<Allocation > allFilters_alloc = Allocation::createTyped(androidrs::conv::mRS, all_filters_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
        // alloc input
        sp<const Type> all_inputs_t = Type::create(androidrs::conv::mRS, e, convInfo.in_depth*convInfo.input_rows*convInfo.input_cols,
                                                        0,
                                                        0);
        sp<Allocation > allInputs_alloc = Allocation::createTyped(androidrs::conv::mRS, all_inputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
        //alloc output
        sp<const Type> all_outputs_t = Type::create(androidrs::conv::mRS, e, convInfo.out_depth*convInfo.out_rows*convInfo.out_cols,
                                                        0,
                                                        0);
        sp<Allocation > allOutputs_alloc = Allocation::createTyped(androidrs::conv::mRS, all_outputs_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

        // allFilters_alloc_vec.push_back(allFilters_alloc);
        // allInputs_alloc_vec.push_back(allInputs_alloc);
        // allOutputs_alloc_vec.push_back(allOutputs_alloc);
    // }

    // allFilters_alloc_vec[idx]->copy1DFrom(filter);
    // allInputs_alloc_vec[idx]->copy1DFrom(input);

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

    // sc->set_filters(allFilters_alloc_vec[idx]);
    sc->set_filters(allFilters_alloc);
    // sc->set_inputs(allInputs_alloc_vec[idx]);
    sc->set_inputs(allInputs_alloc);
    sc->invoke_initParam();

    // sc->forEach_launchConvF32(allOutputs_alloc_vec[idx]);
    sc->forEach_launchConvF32(allOutputs_alloc);
    allOutputs_alloc->copy1DTo(output);
    // allOutputs_alloc_vec[idx]->copy1DTo(output);
    // count++;
};

}
}


#endif //RSKERNELSTEST_RSCONV_H
