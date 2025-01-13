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

#include <cuda_fp4.h>
#include <cublasLt.h>

/// Sample wrapper executing nvfp4 matmul with cublasLtMatmul, with addition of per-tensor block scaling, and
/// the workspace to support split-K algorithms.
///
/// pointer mode is for alpha and beta is always host, to change it configure the appropriate matmul descriptor
/// attribute matmul is not using cublas handle's configuration of math mode, here tensor ops are implicitly allowed; to
/// change this configure appropriate attribute in the preference handle
void LtNvfp4Matmul(cublasLtHandle_t ltHandle,
                 int m,
                 int n,
                 int k,
                 const float *alpha, /* host pointer */
                 const __nv_fp8_e4m3 *a_scale, /* device pointer */
                 const __nv_fp4_e2m1 *A,
                 int lda,
                 const __nv_fp8_e4m3 *b_scale, /* device pointer */
                 const __nv_fp4_e2m1 *B,
                 int ldb,
                 const __nv_fp8_e4m3 *c_scale, /* device pointer */
                 __nv_fp4_e2m1 *D,
                 int ldc,
                 const __nv_fp8_e4m3 *d_scale, /* device pointer */
                 __nv_fp8_e4m3 *d_out_scale, /* device pointer */
                 void *workspace,
                 size_t workspaceSize,
                 cublasLtMatmulMatrixScale_t AScaleMode,
                 cublasLtMatmulMatrixScale_t BScaleMode,
                 cublasLtMatmulMatrixScale_t CScaleMode,
                 cublasLtMatmulMatrixScale_t DScaleMode,
                 cublasLtMatmulMatrixScale_t DOutScaleMode);
