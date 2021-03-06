/*******************************************************************************
* Copyright 2016 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef CPU_JIT_BATCH_NORMALIZATION_HPP
#define CPU_JIT_BATCH_NORMALIZATION_HPP

#include "c_types_map.hpp"
#include "batch_normalization.hpp"
#include "jit_avx2_batch_norm_generator_f32.hpp"

namespace mkldnn {
namespace impl {
namespace cpu {

template <impl::precision_t prec>
class jit_avx2_batch_normalization:
    public batch_normalization<jit_avx2_batch_normalization<prec>> {
public:
    typedef typename prec_trait<prec>::type data_t;
    using batch_normalization
        <jit_avx2_batch_normalization<prec>>::batch_normalization;
    jit_avx2_batch_normalization(
        const batch_normalization_primitive_desc_t &bnpd,
        const primitive_at_t *inputs, const primitive *outputs[]);
    ~jit_avx2_batch_normalization() { delete generator; }

    static status_t set_default_parameters(batch_normalization_desc_t &bnorm_d);
    static status_t constraint(const batch_normalization_desc_t &bnorm_d);

    static const primitive_impl implementation;
private:
    jit_avx2_batch_norm_generator_f32 *generator;

    status_t execute_forward();
};

}
}
}

#endif

// vim: et ts=4 sw=4 cindent cino^=l0,\:0,N-s
