//----------------------------//
// This file is part of RaiSim//
// Copyright 2020, RaiSim Tech//
//----------------------------//

#ifndef RAISIM_INCLUDE_RAISIM_MATH_BLOCKS_H_
#define RAISIM_INCLUDE_RAISIM_MATH_BLOCKS_H_

#include "Expression.hpp"

namespace raisim {

template<class T>
class ElementRef {
 public:
  ElementRef(T& array, size_t id) : ref(array), idx(id) { }
  T& ref;
  size_t idx;
};

template<class T, size_t n, size_t m>
class BlockRef : public MatExpr<BlockRef<T, n, m>> {
 public:
  BlockRef(T& array, size_t r_s, size_t c_s) :
      ref(array), rowStart(r_s), colStart(c_s) { }
  #define RAIMATH_BLOCKREF_SINGLE_ACCESOR ref(i+rowStart)

  constexpr inline size_t size() const { return n*m; }
  constexpr inline size_t rows() const { return n; }
  constexpr inline size_t cols() const { return m; }

  inline double operator()(size_t i) const { return ref(i+rowStart); }
  inline double &operator()(size_t i) { return ref(i+rowStart); }

  inline double operator[](size_t i) const { return ref(i+rowStart); }
  inline double &operator[](size_t i) { return ref(i+rowStart); }

  inline double operator()(size_t i, size_t j) const { return ref(i+rowStart, j+colStart); }
  inline double &operator()(size_t i, size_t j) { return ref(i+rowStart, j+colStart); }
  RAIMATH_MATEXPR_OPERATORS
  T& ref;
  size_t rowStart, colStart;
};

template<class T, size_t n>
class DiagonalRef : public MatExpr<DiagonalRef<T, n>> {
 public:
  DiagonalRef(T& array) :
      ref(array) { }

  T& ref;
};

template<class T, size_t m>
class RowRef : public MatExpr<RowRef<T, m>> {
 public:
  RowRef(T& array, size_t r) :
      ref(array), row(r) { }
  #define RAIMATH_ROWREF_SINGLE_ACCESOR ref(row, i)

  inline double operator()(size_t i) const { return ref(row, i); }
  inline double &operator()(size_t i) { return ref(row, i); }
  inline double operator[](size_t i) const { return ref(row, i); }
  inline double &operator[](size_t i) { return ref(row, i); }
  inline double operator()(size_t i, size_t j) const { return ref(row, j); }
  inline double &operator()(size_t i, size_t j) { return ref(row, j); }

  constexpr inline size_t size() const { return m; }
  constexpr inline size_t rows() const { return size_t(1); }
  constexpr inline size_t cols() const { return m; }

  template<class T2>
  inline RowRef<T, m>& operator = (const MatExpr<T2>& expr) {
    for (size_t j = 0; j < ref.rows(); ++j) ref(row, j) = expr(j);
    return *this;
  }

  RAIMATH_MATEXPR_OPERATORS
  T& ref;
  size_t row;
};

template<class T, size_t n>
class ColRef : public MatExpr<ColRef<T, n>> {
 public:
  ColRef(T& array, size_t c) :
      ref(array), col(c) { }
#define RAIMATH_COLREF_SINGLE_ACCESOR ref(i, col)

  inline double operator()(size_t i) const { return ref(i, col); }
  inline double &operator()(size_t i) { return ref(i, col); }
  inline double operator[](size_t i) const { return ref(i, col); }
  inline double &operator[](size_t i) { return ref(i, col); }

  inline double operator()(size_t i, size_t j) const { return ref(i, col); }
  inline double &operator()(size_t i, size_t j) { return ref(i, col); }

  constexpr inline size_t size() const { return n; }
  constexpr inline size_t rows() const { return n; }
  constexpr inline size_t cols() const { return 1; }

  template<class T2>
  inline ColRef<T, n>& operator = (const T2& expr) {
    for (size_t j = 0; j < ref.rows(); ++j) ref(j, col) = expr(j);
    return *this;
  }

  RAIMATH_MATEXPR_OPERATORS
  T& ref;
  size_t col;
};

}

#endif //RAISIM_INCLUDE_RAISIM_MATH_BLOCKS_H_
