/*
 * Copyright (c) 2025, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <vector>

#include <cuda_runtime_api.h>
#include <cuda_fp4.h>
#include <cublasLt.h>

#include "sample_cublasLt_LtNvfp4Matmul.h"
#include "helpers.h"

int main() {
    TestBench<__nv_fp4_e2m1, __nv_fp4_e2m1, float, __nv_fp8_e4m3> props(64, 128, 256, 2.0f, 0.0f /* ignored */, 32ULL * 1024 * 1024, 1, __nv_fp8_e4m3{2.0f}, __nv_fp8_e4m3{0.5f}, __nv_fp8_e4m3{1.0f}, __nv_fp8_e4m3{1.0f},
        CUBLASLT_MATMUL_MATRIX_SCALE_VEC16_UE4M3, CUBLASLT_MATMUL_MATRIX_SCALE_VEC16_UE4M3, CUBLASLT_MATMUL_MATRIX_SCALE_SCALAR_32F, CUBLASLT_MATMUL_MATRIX_SCALE_SCALAR_32F, CUBLASLT_MATMUL_MATRIX_SCALE_VEC16_UE4M3);

    props.run([&props] {
        LtNvfp4Matmul(props.ltHandle,
                    props.m,
                    props.n,
                    props.k,
                    &props.alpha,
                    props.AscaleDev,
                    props.Adev,
                    props.k,
                    props.BscaleDev,
                    props.Bdev,
                    props.k,
                    props.CscaleDev,
                    props.Cdev,
                    props.m,
                    props.DscaleDev,
                    props.DOutscaleDev,
                    props.workspace,
                    props.workspaceSize,
                    props.AScaleMode,
                    props.BScaleMode,
                    props.CScaleMode,
                    props.DScaleMode,
                    props.DOutScaleMode);
    });

    return 0;
}