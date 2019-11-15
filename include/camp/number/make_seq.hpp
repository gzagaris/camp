#ifndef CAMP_NUMBER_SEQ_HPP
#define CAMP_NUMBER_SEQ_HPP

#include "number.hpp"

namespace camp
{

namespace detail
{
  template <typename T, typename N>
  struct gen_seq;
#if defined(CAMP_USE_MAKE_INTEGER_SEQ) && !__NVCC__
  template <typename T, T N>
  struct gen_seq<T, integral_constant<T, N>> {
    using type = __make_integer_seq<int_seq, T, N>;
  };
#elif CAMP_USE_INTEGER_PACK && !__NVCC__
  template <typename T, T N>
  struct gen_seq<T, integral_constant<T, N>> {
    using type = int_seq<T, __integer_pack(N)...>;
  };
#else
  template <typename T, typename S1, typename S2>
  struct concat;

  template <typename T, T... I1, T... I2>
  struct concat<T, int_seq<T, I1...>, int_seq<T, I2...>> {
    using type = typename int_seq<T, I1..., (sizeof...(I1) + I2)...>::type;
  };

  template <typename T, typename N_t>
  struct gen_seq
      : concat<T,
               typename gen_seq<T, integral_constant<T, N_t::value / 2>>::type,
               typename gen_seq<
                   T,
                   integral_constant<T, N_t::value - N_t::value / 2>>::type>::
            type {
  };

  template <typename T>
  struct gen_seq<T, integral_constant<T, 0>> : int_seq<T> {
  };
  template <typename T>
  struct gen_seq<T, integral_constant<T, 1>> : int_seq<T, 0> {
  };
#endif
}  // namespace detail

// TODO: document
template <idx_t Upper>
struct make_idx_seq {
  using type =
      typename detail::gen_seq<idx_t, integral_constant<idx_t, Upper>>::type;
};


// TODO: document
template <idx_t Upper>
using make_idx_seq_t = typename make_idx_seq<Upper>::type;

// TODO: document
template <class... Ts>
using idx_seq_for_t = typename make_idx_seq<sizeof...(Ts)>::type;

// TODO: document
template <typename T>
struct idx_seq_from;

// TODO: document
template <template <typename...> class T, typename... Args>
struct idx_seq_from<T<Args...>> : make_idx_seq<sizeof...(Args)> {
};

// TODO: document
template <typename T, T... Args>
struct idx_seq_from<int_seq<T, Args...>> : make_idx_seq<sizeof...(Args)> {
};

// TODO: document
template <typename T>
using idx_seq_from_t = typename idx_seq_from<camp::decay<T>>::type;

// TODO: document
template <typename T, T Upper>
struct make_int_seq : detail::gen_seq<T, integral_constant<T, Upper>>::type {
};

// TODO: document
template <typename T, idx_t Upper>
using make_int_seq_t = typename make_int_seq<T, Upper>::type;

// TODO: document
template <typename T>
struct not_ {
  using type = typename if_s<T, false_type, true_type>::type;
};


template <idx_t N, typename IdxSeg>
struct seq_at;

template <idx_t N, idx_t Idx0, idx_t... IdxRest>
struct seq_at<N, camp::idx_seq<Idx0, IdxRest...>> {
  static constexpr idx_t value =
      seq_at<N - 1, camp::idx_seq<IdxRest...>>::value;
};

template <idx_t Idx0, idx_t... IdxRest>
struct seq_at<0, camp::idx_seq<Idx0, IdxRest...>> {
  static constexpr idx_t value = Idx0;
};
}  // namespace camp

#endif /* CAMP_NUMBER_SEQ_HPP */
