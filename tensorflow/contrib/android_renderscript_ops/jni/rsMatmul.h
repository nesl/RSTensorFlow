//
// Created by WangYingnan on 3/12/17.
//

#ifndef RSKERNELSTEST_RSMATMUL_H
#define RSKERNELSTEST_RSMATMUL_H

#include "tensorflow/contrib/android_renderscript_ops/jni/RScommon.h"


namespace androidrs {

namespace matmul {

static sp<RS> mRS = new RS();
static sp<ScriptIntrinsicBLAS> sc = nullptr; //ScriptIntrinsicBLAS::create(androidrs::matmul::mRS);
//static const char* cachePath = "/data/user/0/org.tensorflow.demo/cache";
static int tot_matmul_cnt = 2;
static int count = 0;
static std::vector<sp<Allocation>> a_alloc_vec;
static std::vector<sp<Allocation>> b_alloc_vec;
static std::vector<sp<Allocation>> c_alloc_vec;

sp<ScriptIntrinsicBLAS>& initSC()
{
    
    if (sc == nullptr) {
    mRS->init(kCachePath);
    sc = ScriptIntrinsicBLAS::create(androidrs::matmul::mRS);   
    }
    return sc;
}

// float
void rsMatmul_sgemm(void* a_ptr, bool a_trans, void* b_ptr, bool b_trans, void* c_ptr,
                    int m, int n, int k, float alpha, float beta)
{
    int idx = count%tot_matmul_cnt;

    if(!androidrs::matmul::mRS->getContext()){
        androidrs::matmul::mRS->init(kCachePath);
    }

    //if(count<tot_matmul_cnt){
        sp<const Element> e = Element::F32(androidrs::matmul::mRS);

        sp<const Type> a_t = Type::create(androidrs::matmul::mRS, e, k, m, 0);
        sp<const Type> b_t = Type::create(androidrs::matmul::mRS, e, n, k, 0);
        sp<const Type> c_t = Type::create(androidrs::matmul::mRS, e, n, m, 0);

        sp<Allocation> a_alloc = Allocation::createTyped(androidrs::matmul::mRS, a_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
        sp<Allocation> b_alloc = Allocation::createTyped(androidrs::matmul::mRS, b_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
        sp<Allocation> c_alloc = Allocation::createTyped(androidrs::matmul::mRS, c_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

        //a_alloc_vec.push_back(a_alloc);
        //b_alloc_vec.push_back(b_alloc);
        //c_alloc_vec.push_back(c_alloc);
    // }

    //a_alloc_vec[idx]->copy2DRangeFrom(0, 0, k, m, a_ptr);
    //b_alloc_vec[idx]->copy2DRangeFrom(0, 0, n, k, b_ptr);
    a_alloc->copy2DRangeFrom(0, 0, k, m, a_ptr);
    b_alloc->copy2DRangeFrom(0, 0, n, k, b_ptr);

    RsBlasTranspose a_transpose = a_trans ? RsBlasTranspose::RsBlasTrans : RsBlasTranspose::RsBlasNoTrans;
    RsBlasTranspose b_transpose = b_trans ? RsBlasTranspose::RsBlasTrans : RsBlasTranspose::RsBlasNoTrans;

    sp<ScriptIntrinsicBLAS> script = initSC();
    // script->SGEMM(a_transpose, b_transpose, alpha, a_alloc_vec[idx], b_alloc_vec[idx], beta, c_alloc_vec[idx]);
    script->SGEMM(a_transpose, b_transpose, alpha, a_alloc, b_alloc, beta, c_alloc);

    // c_alloc_vec[idx]->copy2DRangeTo(0, 0, n, m, c_ptr);
    c_alloc->copy2DRangeTo(0, 0, n, m, c_ptr);
    //count++;
};

}
}

#endif //RSKERNELSTEST_RSMATMUL_H
