#ifndef FORWARD_DECLARE_H
#define FORWARD_DECLARE_H


namespace Fastor {

// FORWARD DECLARATIONS
//----------------------------------------------------------------
template<typename TLhs, typename TRhs, size_t DIM0>
struct BinaryAddOp;

template<typename TLhs, typename TRhs, size_t DIM0>
struct BinarySubOp;

template<typename TLhs, typename TRhs, size_t DIM0>
struct BinaryMulOp;

template<typename TLhs, typename TRhs, size_t DIM0>
struct BinaryDivOp;


template<typename Expr, size_t DIMS>
struct UnaryAddOp;

template<typename Expr, size_t DIMS>
struct UnarySubOp;

template<typename Expr, size_t DIMS>
struct UnaryAbsOp;

template<typename Expr, size_t DIMS>
struct UnarySqrtOp;

template<typename Expr, size_t DIMS>
struct UnaryExpOp;

template<typename Expr, size_t DIMS>
struct UnaryLogOp;

template<typename Expr, size_t DIMS>
struct UnarySinOp;

template<typename Expr, size_t DIMS>
struct UnaryCosOp;

template<typename Expr, size_t DIMS>
struct UnaryTanOp;

template<typename Expr, size_t DIMS>
struct UnaryAsinOp;

template<typename Expr, size_t DIMS>
struct UnaryAcosOp;

template<typename Expr, size_t DIMS>
struct UnaryAtanOp;

template<typename Expr, size_t DIMS>
struct UnarySinhOp;

template<typename Expr, size_t DIMS>
struct UnaryCoshOp;

template<typename Expr, size_t DIMS>
struct UnaryTanhOp;


template<typename Expr, size_t DIMS>
struct TensorViewExpr;

template<typename Expr, size_t DIMS>
struct TensorConstViewExpr;

template<typename Expr, typename IterExpr, size_t DIMS>
struct TensorRandomViewExpr;

template<typename Expr, typename IterExpr, size_t DIMS>
struct TensorConstRandomViewExpr;

template<typename Expr, typename Seq0, size_t DIMS>
struct TensorFixedViewExpr1D;

template<typename Expr, typename Seq0, size_t DIMS>
struct TensorConstFixedViewExpr1D;

template<typename Expr, typename Seq0, typename Seq1, size_t DIMS>
struct TensorFixedViewExpr2D;

template<typename Expr, typename Seq0, typename Seq1, size_t DIMS>
struct TensorConstFixedViewExpr2D;

template <FASTOR_INDEX ... All>
struct Index;

template<class Idx, class Seq>
struct nprods;

template<class Idx, class Seq>
struct nprods_views;


#define FASTOR_MAKE_BINARY_CMP_OP_FORWARD_DECLARATION(NAME)\
template<typename TLhs, typename TRhs, size_t DIM0>\
struct BinaryCmpOp##NAME ;\

FASTOR_MAKE_BINARY_CMP_OP_FORWARD_DECLARATION(EQ)
FASTOR_MAKE_BINARY_CMP_OP_FORWARD_DECLARATION(NEQ)
FASTOR_MAKE_BINARY_CMP_OP_FORWARD_DECLARATION(LT)
FASTOR_MAKE_BINARY_CMP_OP_FORWARD_DECLARATION(GT)
FASTOR_MAKE_BINARY_CMP_OP_FORWARD_DECLARATION(LE)
FASTOR_MAKE_BINARY_CMP_OP_FORWARD_DECLARATION(GE)
FASTOR_MAKE_BINARY_CMP_OP_FORWARD_DECLARATION(AND)
FASTOR_MAKE_BINARY_CMP_OP_FORWARD_DECLARATION(OR)

namespace internal {
template<typename Derived>
struct is_binary_cmp_op;
}
//----------------------------------------------------------------

}


#endif // FORWARD_DECLARE_H