#ifndef SIMD_VECTOR_INT64_H
#define SIMD_VECTOR_INT64_H

#include "simd_vector_base.h"

namespace Fastor {


// AVX VERSION
//-----------------------------------------------------------------------------------------------

#ifdef FASTOR_AVX2_IMPL

template<>
struct SIMDVector<Int64,simd_abi::avx> {
    using value_type = __m256i;
    static constexpr FASTOR_INDEX Size = internal::get_simd_vector_size<SIMDVector<Int64,simd_abi::avx>>::value;
    static constexpr FASTOR_INLINE FASTOR_INDEX size() {return internal::get_simd_vector_size<SIMDVector<Int64,simd_abi::avx>>::value;}
    static constexpr int unroll_size(FASTOR_INDEX size) {return (static_cast<int>(size) - static_cast<int>(Size));}

    FASTOR_INLINE SIMDVector() : value(_mm256_setzero_si256()) {}
    FASTOR_INLINE SIMDVector(Int64 num) : value(_mm256_set1_epi64x(num)) {}
    FASTOR_INLINE SIMDVector(__m256i regi) : value(regi) {}
    FASTOR_INLINE SIMDVector(const SIMDVector<Int64,simd_abi::avx> &a) : value(a.value) {}
    FASTOR_INLINE SIMDVector(const Int64 *data, int Aligned=true) {
        if (Aligned)
            value =_mm256_load_si256((__m256i*)data);
        else
            value = _mm256_loadu_si256((__m256i*)data);
    }
    FASTOR_INLINE SIMDVector(Int64 *data, int Aligned=true) {
        if (Aligned)
            value =_mm256_load_si256((__m256i*)data);
        else
            value = _mm256_loadu_si256((__m256i*)data);
    }

    FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator=(Int64 num) {
        value = _mm256_set1_epi64x(num);
        return *this;
    }
    FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator=(__m256i regi) {
        value = regi;
        return *this;
    }
    FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator=(const SIMDVector<Int64,simd_abi::avx> &a) {
        value = a.value;
        return *this;
    }

    FASTOR_INLINE void load(const Int64 *data, int Aligned=true) {
        if (Aligned)
            value =_mm256_load_si256((__m256i*)data);
        else
            value = _mm256_loadu_si256((__m256i*)data);
    }
    FASTOR_INLINE void store(Int64 *data, bool Aligned=true) const {
        if (Aligned)
            _mm256_store_si256((__m256i*)data,value);
        else
            _mm256_storeu_si256((__m256i*)data,value);
    }

    FASTOR_INLINE void aligned_load(const Int64 *data) {
        value =_mm256_load_si256((__m256i*)data);
    }
    FASTOR_INLINE void aligned_store(Int64 *data) const {
        _mm256_store_si256((__m256i*)data,value);
    }

    FASTOR_INLINE Int64 operator[](FASTOR_INDEX i) const {return reinterpret_cast<const Int64*>(&value)[i];}
    FASTOR_INLINE Int64 operator()(FASTOR_INDEX i) const {return reinterpret_cast<const Int64*>(&value)[i];}

    FASTOR_INLINE void set(Int64 num) {
        value = _mm256_set1_epi64x(num);
    }
    FASTOR_INLINE void set(Int64 num0, Int64 num1, Int64 num2, Int64 num3) {
        value = _mm256_set_epi64x(num0,num1,num2,num3);
    }
    FASTOR_INLINE void set_sequential(Int64 num0) {
        value = _mm256_setr_epi64x(num0,num0+1,num0+2,num0+3);
    }

    // In-place operators
    FASTOR_INLINE void operator+=(Int64 num) {
        value = _mm256_add_epi64x(value,_mm256_set1_epi64x(num));

    }
    FASTOR_INLINE void operator+=(__m256i regi) {
        value = _mm256_add_epi64x(value,regi);
    }
    FASTOR_INLINE void operator+=(const SIMDVector<Int64,simd_abi::avx> &a) {
        value = _mm256_add_epi64x(value,a.value);
    }

    FASTOR_INLINE void operator-=(Int64 num) {
        value = _mm256_sub_epi64x(value,_mm256_set1_epi64x(num));
    }
    FASTOR_INLINE void operator-=(__m256i regi) {
        value = _mm256_sub_epi64x(value,regi);
    }
    FASTOR_INLINE void operator-=(const SIMDVector<Int64,simd_abi::avx> &a) {
        value = _mm256_sub_epi64x(value,a.value);
    }

    FASTOR_INLINE void operator*=(Int64 num) {
        value = _mm256_mul_epi64x(value,_mm256_set1_epi64x(num));
    }
    FASTOR_INLINE void operator*=(__m256i regi) {
        value = _mm256_mul_epi64x(value,regi);
    }
    FASTOR_INLINE void operator*=(const SIMDVector<Int64,simd_abi::avx> &a) {
        value = _mm256_mul_epi64x(value,a.value);
    }

    FASTOR_INLINE void operator/=(Int64 num) {
        Int64 val[Size]; _mm256_storeu_si256((__m256i*)val, value);
        for (FASTOR_INDEX i=0; i<Size; ++i) {
            val[i] /= num;
        }
        value = _mm256_loadu_si256((__m256i*)val);
    }
    FASTOR_INLINE void operator/=(__m256i regi) {
        Int64 val[Size]; _mm256_storeu_si256((__m256i*)val, value);
        Int64 val_num[Size]; _mm256_storeu_si256((__m256i*)val_num, regi);
        for (FASTOR_INDEX i=0; i<Size; ++i) {
            val[i] /= val_num[i];
        }
        value = _mm256_loadu_si256((__m256i*)val);
    }
    FASTOR_INLINE void operator/=(const SIMDVector<Int64,simd_abi::avx> &a) {
        Int64 val[Size]; _mm256_storeu_si256((__m256i*)val, value);
        Int64 val_a[Size]; _mm256_storeu_si256((__m256i*)val_a, a.value);
        for (FASTOR_INDEX i=0; i<Size; ++i) {
            val[i] /= val_a[i];
        }
        value = _mm256_loadu_si256((__m256i*)val);
    }

    FASTOR_INLINE Int64 minimum() {
        const Int64 *vals = reinterpret_cast<const Int64*>(&value);
        Int64 quan = 0;
        for (FASTOR_INDEX i=0; i<Size; ++i)
            if (vals[i]<quan)
                quan = vals[i];
        return quan;
    }
    FASTOR_INLINE Int64 maximum() {
        const Int64 *vals = reinterpret_cast<const Int64*>(&value);
        Int64 quan = 0;
        for (FASTOR_INDEX i=0; i<Size; ++i)
            if (vals[i]>quan)
                quan = vals[i];
        return quan;
    }
    FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> reverse() {
        // Reversing a 64 bit vector seems really expensive regardless
        // of which of the following methods being used
        // SIMDVector<Int64,simd_abi::avx> out(_mm256_set_epi64x(value[0],value[1],value[2],value[3]));
        // SIMDVector<Int64,simd_abi::avx> out; out.set(value[3],value[2],value[1],value[0]);
        // return out;
        SIMDVector<Int64,simd_abi::avx> out;
        out.value = _mm256_reverse_epi64(value);
        return out;
    }

    FASTOR_INLINE Int64 sum() {
        const Int64 *vals = reinterpret_cast<const Int64*>(&value);
        Int64 quan = 0;
        for (FASTOR_INDEX i=0; i<Size; ++i)
            quan += vals[i];
        return quan;
    }

    FASTOR_INLINE Int64 dot(const SIMDVector<Int64,simd_abi::avx> &other) {
        const Int64 *vals0 = reinterpret_cast<const Int64*>(&value);
        const Int64 *vals1 = reinterpret_cast<const Int64*>(&other.value);
        Int64 quan = 0;
        for (FASTOR_INDEX i=0; i<Size; ++i)
            quan += vals0[i]*vals1[i];
        return quan;
    }

    __m256i value;
};

FASTOR_HINT_INLINE std::ostream& operator<<(std::ostream &os, SIMDVector<Int64,simd_abi::avx> a) {
    const Int64 *value = reinterpret_cast<const Int64*>(&a.value);
    os << "[" << value[0] <<  " " << value[1] << " " << value[2] << " " << value[3] << "]\n";
    return os;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator+(const SIMDVector<Int64,simd_abi::avx> &a, const SIMDVector<Int64,simd_abi::avx> &b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_add_epi64x(a.value,b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator+(const SIMDVector<Int64,simd_abi::avx> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_add_epi64x(a.value,_mm256_set1_epi64x(b));
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator+(Int64 a, const SIMDVector<Int64,simd_abi::avx> &b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_add_epi64x(_mm256_set1_epi64x(a),b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator+(const SIMDVector<Int64,simd_abi::avx> &b) {
    return b;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator-(const SIMDVector<Int64,simd_abi::avx> &a, const SIMDVector<Int64,simd_abi::avx> &b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_sub_epi64x(a.value,b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator-(const SIMDVector<Int64,simd_abi::avx> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_sub_epi64x(a.value,_mm256_set1_epi64x(b));
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator-(Int64 a, const SIMDVector<Int64,simd_abi::avx> &b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_sub_epi64x(_mm256_set1_epi64x(a),b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator-(const SIMDVector<Int64,simd_abi::avx> &b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_castpd_si256(_mm256_neg_pd(_mm256_castsi256_pd(b.value)));
    return out;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator*(const SIMDVector<Int64,simd_abi::avx> &a, const SIMDVector<Int64,simd_abi::avx> &b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_mul_epi64x(a.value,b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator*(const SIMDVector<Int64,simd_abi::avx> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_mul_epi64x(a.value,_mm256_set1_epi64x(b));
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator*(Int64 a, const SIMDVector<Int64,simd_abi::avx> &b) {
    SIMDVector<Int64,simd_abi::avx> out;
    out.value = _mm256_mul_epi64x(_mm256_set1_epi64x(a),b.value);
    return out;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator/(const SIMDVector<Int64,simd_abi::avx> &a, const SIMDVector<Int64,simd_abi::avx> &b) {
    SIMDVector<Int64,simd_abi::avx> out;
    Int64 val[out.size()];   _mm256_storeu_si256((__m256i*)val, out.value);
    Int64 val_a[out.size()]; _mm256_storeu_si256((__m256i*)val_a, a.value);
    Int64 val_b[out.size()]; _mm256_storeu_si256((__m256i*)val_b, b.value);
    for (FASTOR_INDEX i=0; i<out.size(); ++i) {
        val[i] = val_a[i] / val_b[i];
    }
    out.value = _mm256_loadu_si256((__m256i*)val);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator/(const SIMDVector<Int64,simd_abi::avx> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::avx> out;
    Int64 val[out.size()];   _mm256_storeu_si256((__m256i*)val, out.value);
    Int64 val_a[out.size()]; _mm256_storeu_si256((__m256i*)val_a, a.value);
    for (FASTOR_INDEX i=0; i<out.size(); ++i) {
        val[i] = val_a[i] / b;
    }
    out.value = _mm256_loadu_si256((__m256i*)val);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::avx> operator/(Int64 a, const SIMDVector<Int64,simd_abi::avx> &b) {
    SIMDVector<Int64,simd_abi::avx> out;
    Int64 val[out.size()];   _mm256_storeu_si256((__m256i*)val, out.value);
    Int64 val_b[out.size()]; _mm256_storeu_si256((__m256i*)val_b, b.value);
    for (FASTOR_INDEX i=0; i<out.size(); ++i) {
        val[i] = a / val_b[i];
    }
    out.value = _mm256_loadu_si256((__m256i*)val);
    return out;
}

#endif



// SSE VERSION
//-----------------------------------------------------------------------------------------------

#ifdef FASTOR_SSE4_2_IMPL

template<>
struct SIMDVector<Int64,simd_abi::sse> {
    // CAREFUL WHILE USING THIS AS THIS CONVERTS Int64 TO int IN MOST CASES
    using value_type = __m128i;
    static constexpr FASTOR_INDEX Size = internal::get_simd_vector_size<SIMDVector<Int64,simd_abi::sse>>::value;
    static constexpr FASTOR_INLINE FASTOR_INDEX size() {return internal::get_simd_vector_size<SIMDVector<Int64,simd_abi::sse>>::value;}
    static constexpr int unroll_size(FASTOR_INDEX size) {return (static_cast<int>(size) - static_cast<int>(Size));}

    FASTOR_INLINE SIMDVector() : value(_mm_setzero_si128()) {}
    FASTOR_INLINE SIMDVector(Int64 num) {
        value = _mm_set_epi64x(num,num);
    }
    FASTOR_INLINE SIMDVector(__m128i regi) : value(regi) {}
    FASTOR_INLINE SIMDVector(const SIMDVector<Int64,simd_abi::sse> &a) : value(a.value) {}
    FASTOR_INLINE SIMDVector(const Int64 *data, bool Aligned=true) {
        if (Aligned)
            value =_mm_load_si128((__m128i*)data);
        else
            value = _mm_loadu_si128((__m128i*)data);
    }
    FASTOR_INLINE SIMDVector(Int64 *data, bool Aligned=true) {
        if (Aligned)
            value =_mm_load_si128((__m128i*)data);
        else
            value = _mm_loadu_si128((__m128i*)data);
    }

    FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator=(Int64 num) {
        value = _mm_set_epi64x(num,num);
        return *this;
    }
    FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator=(__m128i regi) {
        value = regi;
        return *this;
    }
    FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator=(const SIMDVector<Int64,simd_abi::sse> &a) {
        value = a.value;
        return *this;
    }

    FASTOR_INLINE void load(const Int64 *data, bool Aligned=true) {
        if (Aligned)
            value =_mm_load_si128((__m128i*)data);
        else
            value = _mm_loadu_si128((__m128i*)data);
    }
    FASTOR_INLINE void store(Int64 *data, bool Aligned=true) const {
        if (Aligned)
            _mm_store_si128((__m128i*)data,value);
        else
            _mm_storeu_si128((__m128i*)data,value);
    }

    FASTOR_INLINE void aligned_load(const Int64 *data) {
        value =_mm_load_si128((__m128i*)data);
    }
    FASTOR_INLINE void aligned_store(Int64 *data) const {
        _mm_store_si128((__m128i*)data,value);
    }

    FASTOR_INLINE Int64 operator[](FASTOR_INDEX i) const {return reinterpret_cast<const Int64*>(&value)[i];}
    FASTOR_INLINE Int64 operator()(FASTOR_INDEX i) const {return reinterpret_cast<const Int64*>(&value)[i];}

    FASTOR_INLINE void set(Int64 num) {
        value = _mm_set_epi64x(num,num);
    }
    FASTOR_INLINE void set(Int64 num0, Int64 num1) {
        value = _mm_set_epi64x(num0,num1);
    }
    FASTOR_INLINE void set_sequential(Int64 num0) {
        value = _mm_set_epi64x(num0+1,num0);
    }

    // In-place operators
    FASTOR_INLINE void operator+=(Int64 num) {
        auto numb = _mm_set_epi64x(num,num);
        value = _mm_add_epi32(value,numb);
    }
    FASTOR_INLINE void operator+=(__m128i regi) {
        value = _mm_add_epi32(value,regi);
    }
    FASTOR_INLINE void operator+=(const SIMDVector<Int64,simd_abi::sse> &a) {
        value = _mm_add_epi32(value,a.value);
    }

    FASTOR_INLINE void operator-=(Int64 num) {
        auto numb = _mm_set_epi64x(num,num);
        value = _mm_sub_epi32(value,numb);
    }
    FASTOR_INLINE void operator-=(__m128i regi) {
        value = _mm_sub_epi32(value,regi);
    }
    FASTOR_INLINE void operator-=(const SIMDVector<Int64,simd_abi::sse> &a) {
        value = _mm_sub_epi32(value,a.value);
    }

    FASTOR_INLINE void operator*=(Int64 num) {
        auto numb = _mm_set_epi64x(num,num);
        value = _mm_mul_epi64(value,numb);
    }
    FASTOR_INLINE void operator*=(__m128i regi) {
        value = _mm_mul_epi64(value,regi);
    }
    FASTOR_INLINE void operator*=(const SIMDVector<Int64,simd_abi::sse> &a) {
        value = _mm_mul_epi64(value,a.value);
    }

    FASTOR_INLINE void operator/=(Int64 num) {
        Int64 val[Size]; _mm_storeu_si128((__m128i*)val, value);
        for (FASTOR_INDEX i=0; i<Size; ++i) {
            val[i] /= num;
        }
        value = _mm_loadu_si128((__m128i*)val);
    }
    FASTOR_INLINE void operator/=(__m128i regi) {
        Int64 val[Size]; _mm_storeu_si128((__m128i*)val, value);
        Int64 val_num[Size]; _mm_storeu_si128((__m128i*)val_num, regi);
        for (FASTOR_INDEX i=0; i<Size; ++i) {
            val[i] /= val_num[i];
        }
        value = _mm_loadu_si128((__m128i*)val);
    }
    FASTOR_INLINE void operator/=(const SIMDVector<Int64,simd_abi::sse> &a) {
        Int64 val[Size]; _mm_storeu_si128((__m128i*)val, value);
        Int64 val_a[Size]; _mm_storeu_si128((__m128i*)val_a, a.value);
        for (FASTOR_INDEX i=0; i<Size; ++i) {
            val[i] /= val_a[i];
        }
        value = _mm_loadu_si128((__m128i*)val);
    }

    FASTOR_INLINE Int64 minimum() {
        const Int64 *vals = reinterpret_cast<const Int64*>(&value);
        Int64 quan = 0;
        for (FASTOR_INDEX i=0; i<Size; ++i)
            if (vals[i]<quan)
                quan = vals[i];
        return static_cast<Int64>(quan);
    }
    FASTOR_INLINE Int64 maximum() {
        const Int64 *vals = reinterpret_cast<const Int64*>(&value);
        Int64 quan = 0;
        for (FASTOR_INDEX i=0; i<Size; ++i)
            if (vals[i]>quan)
                quan = vals[i];
        return static_cast<Int64>(quan);
    }
    FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> reverse() {
        SIMDVector<Int64,simd_abi::sse> out;
        out.value = _mm_reverse_epi64(value);
        return out;
    }

    FASTOR_INLINE Int64 sum() {
        const Int64 *vals = reinterpret_cast<const Int64*>(&value);
        Int64 quan = 0;
        for (FASTOR_INDEX i=0; i<2; ++i)
            quan += vals[i];
        return static_cast<Int64>(quan);
    }

    FASTOR_INLINE Int64 dot(const SIMDVector<Int64,simd_abi::sse> &other) {
        const Int64 *vals0 = reinterpret_cast<const Int64*>(&value);
        const Int64 *vals1 = reinterpret_cast<const Int64*>(&other.value);
        Int64 quan = 0;
        for (FASTOR_INDEX i=0; i<2; ++i)
            quan += vals0[i]*vals1[i];
        return static_cast<Int64>(quan);
    }

    __m128i value;
};

FASTOR_HINT_INLINE std::ostream& operator<<(std::ostream &os, SIMDVector<Int64,simd_abi::sse> a) {
    const Int64 *value = reinterpret_cast<const Int64*>(&a.value);
    os << "[" << value[0] <<  " " << value[1] << "]\n";
    return os;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator+(const SIMDVector<Int64,simd_abi::sse> &a, const SIMDVector<Int64,simd_abi::sse> &b) {
    SIMDVector<Int64,simd_abi::sse> out;
    out.value = _mm_add_epi32(a.value,b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator+(const SIMDVector<Int64,simd_abi::sse> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::sse> out;
    auto numb = _mm_set_epi64x(b,b);
    out.value = _mm_add_epi32(a.value,numb);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator+(Int64 a, const SIMDVector<Int64,simd_abi::sse> &b) {
    SIMDVector<Int64,simd_abi::sse> out;
    auto numb = _mm_set_epi64x(a,a);
    out.value = _mm_add_epi32(numb,b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator+(const SIMDVector<Int64,simd_abi::sse> &b) {
    return b;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator-(const SIMDVector<Int64,simd_abi::sse> &a, const SIMDVector<Int64,simd_abi::sse> &b) {
    SIMDVector<Int64,simd_abi::sse> out;
    out.value = _mm_sub_epi32(a.value,b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator-(const SIMDVector<Int64,simd_abi::sse> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::sse> out;
    auto numb = _mm_set_epi64x(b,b);
    out.value = _mm_sub_epi32(a.value,numb);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator-(Int64 a, const SIMDVector<Int64,simd_abi::sse> &b) {
    SIMDVector<Int64,simd_abi::sse> out;
    auto numb = _mm_set_epi64x(a,a);
    out.value = _mm_sub_epi32(numb,b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator-(const SIMDVector<Int64,simd_abi::sse> &b) {
    SIMDVector<Int64,simd_abi::sse> out;
    out.value = _mm_castpd_si128(_mm_neg_pd(_mm_castsi128_pd(b.value)));
    return out;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator*(const SIMDVector<Int64,simd_abi::sse> &a, const SIMDVector<Int64,simd_abi::sse> &b) {
    SIMDVector<Int64,simd_abi::sse> out;
    out.value = _mm_mul_epi64(a.value,b.value);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator*(const SIMDVector<Int64,simd_abi::sse> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::sse> out;
    auto numb = _mm_set_epi64x(b,b);
    out.value = _mm_mul_epi64(a.value,numb);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator*(Int64 a, const SIMDVector<Int64,simd_abi::sse> &b) {
    SIMDVector<Int64,simd_abi::sse> out;
    auto numb = _mm_set_epi64x(a,a);
    out.value = _mm_mul_epi64(numb,b.value);
    return out;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator/(const SIMDVector<Int64,simd_abi::sse> &a, const SIMDVector<Int64,simd_abi::sse> &b) {
    SIMDVector<Int64,simd_abi::sse> out;
    Int64 val[out.size()];   _mm_storeu_si128((__m128i*)val, out.value);
    Int64 val_a[out.size()]; _mm_storeu_si128((__m128i*)val_a, a.value);
    Int64 val_b[out.size()]; _mm_storeu_si128((__m128i*)val_b, b.value);
    for (FASTOR_INDEX i=0; i<out.size(); ++i) {
        val[i] = val_a[i] / val_b[i];
    }
    out.value = _mm_loadu_si128((__m128i*)val);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator/(const SIMDVector<Int64,simd_abi::sse> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::sse> out;
    Int64 val[out.size()];   _mm_storeu_si128((__m128i*)val, out.value);
    Int64 val_a[out.size()]; _mm_storeu_si128((__m128i*)val_a, a.value);
    for (FASTOR_INDEX i=0; i<out.size(); ++i) {
        val[i] = val_a[i] / b;
    }
    out.value = _mm_loadu_si128((__m128i*)val);
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::sse> operator/(Int64 a, const SIMDVector<Int64,simd_abi::sse> &b) {
    SIMDVector<Int64,simd_abi::sse> out;
    Int64 val[out.size()];   _mm_storeu_si128((__m128i*)val, out.value);
    Int64 val_b[out.size()]; _mm_storeu_si128((__m128i*)val_b, b.value);
    for (FASTOR_INDEX i=0; i<out.size(); ++i) {
        val[i] = a / val_b[i];
    }
    out.value = _mm_loadu_si128((__m128i*)val);
    return out;
}


#endif




// SCALAR VERSION
//------------------------------------------------------------------------------------------------------------
template <>
struct SIMDVector<Int64, simd_abi::scalar> {
    using value_type = Int64;
    static constexpr FASTOR_INDEX Size = 1;
    static constexpr FASTOR_INLINE FASTOR_INDEX size() {return 1;}
    static constexpr int unroll_size(FASTOR_INDEX size) {return (static_cast<int>(size) - 1);}

    FASTOR_INLINE SIMDVector() : value(0) {}
    FASTOR_INLINE SIMDVector(Int64 num) : value(num) {}
    FASTOR_INLINE SIMDVector(const SIMDVector<Int64,simd_abi::scalar> &a) : value(a.value) {}
    FASTOR_INLINE SIMDVector(const Int64 *data, bool Aligned=true) : value(*data) {}
    FASTOR_INLINE SIMDVector(Int64 *data, bool Aligned=true) : value(*data) {}

    FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator=(Int64 num) {
        value = num;
        return *this;
    }
    FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator=(const SIMDVector<Int64,simd_abi::scalar> &a) {
        value = a.value;
        return *this;
    }

    FASTOR_INLINE void load(const Int64 *data, bool ) {
        value = *data;
    }
    FASTOR_INLINE void store(Int64 *data, bool ) const {
        data[0] = value;
    }

    FASTOR_INLINE void load(const Int64 *data) {
        value = *data;
    }
    FASTOR_INLINE void store(Int64 *data) const {
        data[0] = value;
    }

    FASTOR_INLINE void aligned_load(const Int64 *data) {
        value = *data;
    }
    FASTOR_INLINE void aligned_store(Int64 *data) const {
        data[0] = value;
    }

    FASTOR_INLINE Int64 operator[](FASTOR_INDEX) const {return value;}
    FASTOR_INLINE Int64 operator()(FASTOR_INDEX) const {return value;}

    FASTOR_INLINE void set(Int64 num) {
        value = num;
    }

    FASTOR_INLINE void set_sequential(Int64 num) {
        value = num;
    }

    // In-place operators
    FASTOR_INLINE void operator+=(Int64 num) {
        value += num;
    }
    FASTOR_INLINE void operator+=(const SIMDVector<Int64,simd_abi::scalar> &a) {
        value += a.value;
    }

    FASTOR_INLINE void operator-=(Int64 num) {
        value -= num;
    }
    FASTOR_INLINE void operator-=(const SIMDVector<Int64,simd_abi::scalar> &a) {
        value -= a.value;
    }

    FASTOR_INLINE void operator*=(Int64 num) {
        value *= num;
    }
    FASTOR_INLINE void operator*=(const SIMDVector<Int64,simd_abi::scalar> &a) {
        value *= a.value;
    }

    FASTOR_INLINE void operator/=(Int64 num) {
        value /= num;
    }
    FASTOR_INLINE void operator/=(const SIMDVector<Int64,simd_abi::scalar> &a) {
        value /= a.value;
    }
    // end of in-place operators

    FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> shift(FASTOR_INDEX) {
        return *this;
    }
    FASTOR_INLINE Int64 minimum() {return value;}
    FASTOR_INLINE Int64 maximum() {return value;}
    FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> reverse() {SIMDVector<Int64,simd_abi::scalar> out; out.value = value; return out;}

    FASTOR_INLINE Int64 sum() {return value;}
    FASTOR_INLINE Int64 dot(const SIMDVector<Int64,simd_abi::scalar> &other) {
        return value*other.value;
    }

    Int64 value;
};


FASTOR_HINT_INLINE std::ostream& operator<<(std::ostream &os, SIMDVector<Int64,simd_abi::scalar> a) {
    os << "[" << a.value << "]\n";
    return os;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator+(const SIMDVector<Int64,simd_abi::scalar> &a, const SIMDVector<Int64,simd_abi::scalar> &b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a.value+b.value;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator+(const SIMDVector<Int64,simd_abi::scalar> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a.value+b;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator+(Int64 a, const SIMDVector<Int64,simd_abi::scalar> &b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a+b.value;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator+(const SIMDVector<Int64,simd_abi::scalar> &b) {
    return b;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator-(const SIMDVector<Int64,simd_abi::scalar> &a, const SIMDVector<Int64,simd_abi::scalar> &b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a.value-b.value;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator-(const SIMDVector<Int64,simd_abi::scalar> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a.value-b;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator-(Int64 a, const SIMDVector<Int64,simd_abi::scalar> &b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a-b.value;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator-(const SIMDVector<Int64,simd_abi::scalar> &b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = -b.value;
    return out;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator*(const SIMDVector<Int64,simd_abi::scalar> &a, const SIMDVector<Int64,simd_abi::scalar> &b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a.value*b.value;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator*(const SIMDVector<Int64,simd_abi::scalar> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a.value*b;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator*(Int64 a, const SIMDVector<Int64,simd_abi::scalar> &b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a*b.value;
    return out;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator/(const SIMDVector<Int64,simd_abi::scalar> &a, const SIMDVector<Int64,simd_abi::scalar> &b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a.value/b.value;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator/(const SIMDVector<Int64,simd_abi::scalar> &a, Int64 b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a.value/b;
    return out;
}
FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> operator/(Int64 a, const SIMDVector<Int64,simd_abi::scalar> &b) {
    SIMDVector<Int64,simd_abi::scalar> out;
    out.value = a/b.value;
    return out;
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> sqrt(const SIMDVector<Int64,simd_abi::scalar> &a) {
    return std::sqrt(a.value);
}

FASTOR_INLINE SIMDVector<Int64,simd_abi::scalar> abs(const SIMDVector<Int64,simd_abi::scalar> &a) {
    return std::abs(a.value);
}


}

#endif // SIMD_VECTOR_INT64_H