//
// Created by WangYingnan on 3/12/17.
//

#ifndef RSKERNELSTEST_RSMATMUL_H
#define RSKERNELSTEST_RSMATMUL_H

#include "tensorflow/contrib/android_renderscript_ops/jni/RScommon.h"


namespace androidrs {

namespace matmul {

static sp<RS> mRS = new RS();
static const char* cachePath = "/data/user/0/org.tensorflow.demo/cache";
static int count = 0;



sp<ScriptIntrinsicBLAS>& initSC()
{
    static sp<ScriptIntrinsicBLAS> sc = ScriptIntrinsicBLAS::create(androidrs::matmul::mRS);
    return sc;
}

sp<Allocation>& initAlloc(int idx, int type)
{
    static sp<const Element> e = Element::F32(androidrs::matmul::mRS);
    // mm1
    static sp<const Type> mm1_a_t = Type::create(androidrs::matmul::mRS, e, 2048, 1, 0);
    static sp<const Type> mm1_b_t = Type::create(androidrs::matmul::mRS, e, 1024, 2048, 0);
    static sp<const Type> mm1_c_t = Type::create(androidrs::matmul::mRS, e, 1024, 1, 0);
    static sp<Allocation> mm1_a_alloc = Allocation::createTyped(androidrs::matmul::mRS, mm1_a_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> mm1_b_alloc = Allocation::createTyped(androidrs::matmul::mRS, mm1_b_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> mm1_c_alloc = Allocation::createTyped(androidrs::matmul::mRS, mm1_c_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    // mm2
    static sp<const Type> mm2_a_t = Type::create(androidrs::matmul::mRS, e, 1024, 1, 0);
    static sp<const Type> mm2_b_t = Type::create(androidrs::matmul::mRS, e, 1008, 1024, 0);
    static sp<const Type> mm2_c_t = Type::create(androidrs::matmul::mRS, e, 1008, 1, 0);
    static sp<Allocation> mm2_a_alloc = Allocation::createTyped(androidrs::matmul::mRS, mm2_a_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> mm2_b_alloc = Allocation::createTyped(androidrs::matmul::mRS, mm2_b_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);
    static sp<Allocation> mm2_c_alloc = Allocation::createTyped(androidrs::matmul::mRS, mm2_c_t, RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT);

    switch (idx)
    {
    case 0:
        switch(type){
            case 0: return mm1_a_alloc;
            case 1: return mm1_b_alloc;
            case 2: return mm1_c_alloc;
        }
    case 1:
        switch(type){
            case 0: return mm2_a_alloc;
            case 1: return mm2_b_alloc;
            case 2: return mm2_c_alloc;
        }
    }
}

// float
void rsMatmul_sgemm(void* a_ptr, bool a_trans, void* b_ptr, bool b_trans, void* c_ptr,
                    int m, int n, int k, float alpha, float beta)
{
    int idx = count%2;

    if(!androidrs::matmul::mRS->getContext()){
        androidrs::matmul::mRS->init(androidrs::matmul::cachePath);
    }

    sp<Allocation> a_alloc = initAlloc(idx, 0);
    sp<Allocation> b_alloc = initAlloc(idx, 1);
    sp<Allocation> c_alloc = initAlloc(idx, 2);

    a_alloc->copy2DRangeFrom(0, 0, k, m, a_ptr);
    b_alloc->copy2DRangeFrom(0, 0, n, k, b_ptr);

    RsBlasTranspose a_transpose = a_trans ? RsBlasTranspose::RsBlasTrans : RsBlasTranspose::RsBlasNoTrans;
    RsBlasTranspose b_transpose = b_trans ? RsBlasTranspose::RsBlasTrans : RsBlasTranspose::RsBlasNoTrans;

    sp<ScriptIntrinsicBLAS> script = initSC();
    script->SGEMM(a_transpose, b_transpose, alpha, a_alloc, b_alloc, beta, c_alloc);

    c_alloc->copy2DRangeTo(0, 0, n, m, c_ptr);
    count++;
};

}
}

#endif //RSKERNELSTEST_RSMATMUL_H
