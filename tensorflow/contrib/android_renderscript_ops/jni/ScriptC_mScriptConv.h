/*
 * Copyright (C) 2011-2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This file is auto-generated. DO NOT MODIFY!
 * The source Renderscript file: mScriptConv.rs
 */

#include "tensorflow/contrib/android_renderscript_ops/rs/cpp/RenderScript.h"

using namespace android::RSC;  // NOLINT

/* This class encapsulates access to the exported elements of the script.  Typically, you
 * would instantiate this class once, call the set_* methods for each of the exported global
 * variables you want to change, then call one of the forEach_ methods to invoke a kernel.
 */
class ScriptC_mScriptConv : public android::RSC::ScriptC {
private:
    /* For each non-const variable exported by the script, we have an equivalent field.  This
     * field contains the last value this variable was set to using the set_ method.  This may
     * not be current value of the variable in the script, as the script is free to modify its
     * internal variable without changing this field.  If the script initializes the
     * exported variable, the constructor will initialize this field to the same value.
     */
    int32_t mExportVar_in_depth;
    int32_t mExportVar_input_rows;
    int32_t mExportVar_input_cols;
    int32_t mExportVar_filter_rows;
    int32_t mExportVar_filter_cols;
    int32_t mExportVar_stride_rows;
    int32_t mExportVar_stride_cols;
    int32_t mExportVar_pad_rows;
    int32_t mExportVar_pad_cols;
    int32_t mExportVar_out_depth;
    int32_t mExportVar_out_rows;
    int32_t mExportVar_out_cols;
    int32_t mExportVar_filter_w;
    int32_t mExportVar_filter_sz;
    int32_t mExportVar_filter_stride_e;
    int32_t mExportVar_input_stride_e;
    int32_t mExportVar_padded_rows;
    int32_t mExportVar_padded_cols;
    int32_t mExportVar_filter_hf;
    android::RSC::sp<const android::RSC::Allocation> mExportVar_filters;
    android::RSC::sp<const android::RSC::Allocation> mExportVar_inputs;
    /* The following elements are used to verify the types of allocations passed to kernels.
     */
    android::RSC::sp<const android::RSC::Element> __rs_elem_F32;
    android::RSC::sp<const android::RSC::Element> __rs_elem_U8;
public:
    ScriptC_mScriptConv(android::RSC::sp<android::RSC::RS> rs);
    virtual ~ScriptC_mScriptConv();

    /* Methods to set and get the variables exported by the script. Const variables will not
     * have a setter.
     * 
     * Note that the value returned by the getter may not be the current value of the variable
     * in the script.  The getter will return the initial value of the variable (as defined in
     * the script) or the the last value set by using the setter method.  The script is free to
     * modify its value independently.
     */
    void set_in_depth(int32_t v) {
        setVar(0, &v, sizeof(v));
        mExportVar_in_depth = v;
    }

    int32_t get_in_depth() const {
        return mExportVar_in_depth;
    }

    void set_input_rows(int32_t v) {
        setVar(1, &v, sizeof(v));
        mExportVar_input_rows = v;
    }

    int32_t get_input_rows() const {
        return mExportVar_input_rows;
    }

    void set_input_cols(int32_t v) {
        setVar(2, &v, sizeof(v));
        mExportVar_input_cols = v;
    }

    int32_t get_input_cols() const {
        return mExportVar_input_cols;
    }

    void set_filter_rows(int32_t v) {
        setVar(3, &v, sizeof(v));
        mExportVar_filter_rows = v;
    }

    int32_t get_filter_rows() const {
        return mExportVar_filter_rows;
    }

    void set_filter_cols(int32_t v) {
        setVar(4, &v, sizeof(v));
        mExportVar_filter_cols = v;
    }

    int32_t get_filter_cols() const {
        return mExportVar_filter_cols;
    }

    void set_stride_rows(int32_t v) {
        setVar(5, &v, sizeof(v));
        mExportVar_stride_rows = v;
    }

    int32_t get_stride_rows() const {
        return mExportVar_stride_rows;
    }

    void set_stride_cols(int32_t v) {
        setVar(6, &v, sizeof(v));
        mExportVar_stride_cols = v;
    }

    int32_t get_stride_cols() const {
        return mExportVar_stride_cols;
    }

    void set_pad_rows(int32_t v) {
        setVar(7, &v, sizeof(v));
        mExportVar_pad_rows = v;
    }

    int32_t get_pad_rows() const {
        return mExportVar_pad_rows;
    }

    void set_pad_cols(int32_t v) {
        setVar(8, &v, sizeof(v));
        mExportVar_pad_cols = v;
    }

    int32_t get_pad_cols() const {
        return mExportVar_pad_cols;
    }

    void set_out_depth(int32_t v) {
        setVar(9, &v, sizeof(v));
        mExportVar_out_depth = v;
    }

    int32_t get_out_depth() const {
        return mExportVar_out_depth;
    }

    void set_out_rows(int32_t v) {
        setVar(10, &v, sizeof(v));
        mExportVar_out_rows = v;
    }

    int32_t get_out_rows() const {
        return mExportVar_out_rows;
    }

    void set_out_cols(int32_t v) {
        setVar(11, &v, sizeof(v));
        mExportVar_out_cols = v;
    }

    int32_t get_out_cols() const {
        return mExportVar_out_cols;
    }

    void set_filter_w(int32_t v) {
        setVar(12, &v, sizeof(v));
        mExportVar_filter_w = v;
    }

    int32_t get_filter_w() const {
        return mExportVar_filter_w;
    }

    void set_filter_sz(int32_t v) {
        setVar(13, &v, sizeof(v));
        mExportVar_filter_sz = v;
    }

    int32_t get_filter_sz() const {
        return mExportVar_filter_sz;
    }

    void set_filter_stride_e(int32_t v) {
        setVar(14, &v, sizeof(v));
        mExportVar_filter_stride_e = v;
    }

    int32_t get_filter_stride_e() const {
        return mExportVar_filter_stride_e;
    }

    void set_input_stride_e(int32_t v) {
        setVar(15, &v, sizeof(v));
        mExportVar_input_stride_e = v;
    }

    int32_t get_input_stride_e() const {
        return mExportVar_input_stride_e;
    }

    void set_padded_rows(int32_t v) {
        setVar(16, &v, sizeof(v));
        mExportVar_padded_rows = v;
    }

    int32_t get_padded_rows() const {
        return mExportVar_padded_rows;
    }

    void set_padded_cols(int32_t v) {
        setVar(17, &v, sizeof(v));
        mExportVar_padded_cols = v;
    }

    int32_t get_padded_cols() const {
        return mExportVar_padded_cols;
    }

    void set_filter_hf(int32_t v) {
        setVar(18, &v, sizeof(v));
        mExportVar_filter_hf = v;
    }

    int32_t get_filter_hf() const {
        return mExportVar_filter_hf;
    }

    void set_filters(android::RSC::sp<const android::RSC::Allocation> v) {
        setVar(19, v);
        mExportVar_filters = v;
    }

    android::RSC::sp<const android::RSC::Allocation> get_filters() const {
        return mExportVar_filters;
    }

    void set_inputs(android::RSC::sp<const android::RSC::Allocation> v) {
        setVar(20, v);
        mExportVar_inputs = v;
    }

    android::RSC::sp<const android::RSC::Allocation> get_inputs() const {
        return mExportVar_inputs;
    }

    // No forEach_root(...)
    /* For each kernel of the script corresponds one method.  That method queues the kernel
     * for execution.  The kernel may not have completed nor even started by the time this
     * function returns.  Calls that extract the data out of the output allocation will wait
     * for the kernels to complete.
     */
    void forEach_launchConvF32(android::RSC::sp<android::RSC::Allocation> aout);
    void forEach_launchConvU8(android::RSC::sp<android::RSC::Allocation> aout);
    void invoke_initParam();
};

