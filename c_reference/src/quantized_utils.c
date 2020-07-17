// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include "quantized_utils.h"

void v_q_treesum(INTM_T* const vec, ITER_T len, SCALE_T H1, SCALE_T H2) {
  ITER_T count = len, depth = 0;
  int divbytwo = 1;

  while (depth < (H1 + H2)) {
    if (depth >= H1) {
      divbytwo = 0;
    }

    for (ITER_T p = 0; p < ((len >> 1) + 1); p++) {
      if (p < (count >> 1)) {
        if (divbytwo == 1) {
          #ifdef SHIFT
            vec[p] = (vec[2 * p] >> 1) + (vec[(2 * p) + 1] >> 1);
          #else
            vec[p] = vec[2 * p] / 2 + vec[(2 * p) + 1] / 2;
          #endif
        } else {
          vec[p] = vec[2 * p] + vec[(2 * p) + 1];
        }
      } else if ((p == (count >> 1)) && ((count & 1) == 1)) {
        if (divbytwo == 1) {
          #ifdef SHIFT
            vec[p] = (vec[2 * p] >> 1);
          #else
            vec[p] = vec[2 * p] / 2;
          #endif
        } else {
          vec[p] = vec[2 * p];
        }
      } else {
        vec[p] = 0;
      }
    }
    count = (count + 1) >> 1;
    depth++;
  }
}

void v_q_add(const INT_T* const vec1, const INT_T* const vec2, ITER_T len,
             INT_T* const ret, SCALE_T scvec1, SCALE_T scvec2, SCALE_T scret) {
  for (ITER_T i = 0; i < len; i++) {
    #ifdef SHIFT
      ret[i] = ((vec1[i] >> (scvec1 + scret)) + (vec2[i] >> (scvec2 + scret)));
    #else
      ret[i] = ((vec1[i] / scvec1) / scret) + ((vec2[i] / scvec2) / scret);
    #endif
  }
}

void v_q_sub(const INT_T* const vec1, const INT_T* const vec2, ITER_T len,
             INT_T* const ret, SCALE_T scvec1, SCALE_T scvec2, SCALE_T scret) {
  for (ITER_T i = 0; i < len; i++) {
    #ifdef SHIFT
      ret[i] = ((vec1[i] >> (scvec1 + scret)) - (vec2[i] >> (scvec2 + scret)));
    #else
      ret[i] = ((vec1[i] / scvec1) / scret) - ((vec2[i] / scvec2) / scret);
    #endif
  }
}

void v_q_hadamard(const INT_T* const vec1, const INT_T* const vec2, ITER_T len,
                  INT_T* const ret, SCALE_T scvec1, SCALE_T scvec2) {
  for (ITER_T i = 0; i < len; i++) {
    #ifdef SHIFT
      ret[i] = ((INTM_T)vec1[i] * (INTM_T)vec2[i]) >> (scvec1 + scvec2);
    #else
      ret[i] = ((((INTM_T)vec1[i] * (INTM_T)vec2[i]) / scvec1) / scvec2);
    #endif
  }
}

void v_q_sigmoid(const INT_T* const vec, ITER_T len, INT_T* const ret, INT_T div,
                 INT_T add, INT_T sigmoid_limit, SCALE_T scale_in,
                 SCALE_T scale_out) {
  for (ITER_T i = 0; i < len; i++) {
    INT_T x = (vec[i] / div) + add;

    if (x >= sigmoid_limit) {
      ret[i] = sigmoid_limit << (scale_out - scale_in);
    } else if (x <= 0) {
      ret[i] = 0;
    } else {
      ret[i] = x << (scale_out - scale_in);
    }
  }
}

void v_q_tanh(const INT_T* const vec, ITER_T len, INT_T* const ret,
              SCALE_T scale_in, SCALE_T scale_out) {
  INT_T scale = (1 << scale_in);
  for (ITER_T i = 0; i < len; i++) {
    if (vec[i] >= scale) {
      ret[i] = scale;
    } else if (vec[i] <= -scale) {
      ret[i] = (-scale);
    } else {
      ret[i] = vec[i];
    }
    ret[i] <<= (scale_out - scale_in);
  }
}

void v_q_scalar_add(INT_T scalar, const INT_T* const vec, ITER_T len,
                    INT_T* const ret, SCALE_T scscalar, SCALE_T scvec, SCALE_T scret) {
  for (ITER_T i = 0; i < len; i++) {
    #ifdef SHIFT
      ret[i] = ((scalar >> (scscalar + scret)) + (vec[i] >> (scvec + scret)));
    #else
      ret[i] = ((scalar / scscalar) / scret) + ((vec[i] / scvec) / scret);
    #endif
  }
}

void v_q_scalar_sub(INT_T scalar, const INT_T* const vec, ITER_T len,
                    INT_T* const ret, SCALE_T scscalar, SCALE_T scvec, SCALE_T scret) {
  for (ITER_T i = 0; i < len; i++) {
    #ifdef SHIFT
      ret[i] = ((scalar >> (scscalar + scret)) - (vec[i] >> (scvec + scret)));
    #else
      ret[i] = ((scalar / scscalar) / scret) - ((vec[i] / scvec) / scret);
    #endif
  }
}

void v_q_sub_scalar(const INT_T* const vec, INT_T scalar, ITER_T len,
                    INT_T* const ret, SCALE_T scvec, SCALE_T scscalar, SCALE_T scret) {
  for (ITER_T i = 0; i < len; i++) {
    #ifdef SHIFT
      ret[i] = ((vec[i] >> (scvec + scret)) - (scalar >> (scscalar + scret)));
    #else
      ret[i] = ((vec[i] / scvec) / scret) - ((scalar / scscalar) / scret);
    #endif
  }
}

void v_q_scalar_mul(INT_T scalar, const INT_T* const vec, ITER_T len,
                    INT_T* const ret, SCALE_T scscalar, SCALE_T scvec) {
  for (ITER_T i = 0; i < len; i++) {
    #ifdef SHIFT
      ret[i] = ((INTM_T)scalar * (INTM_T)vec[i]) >> (scscalar + scvec);
    #else
      ret[i] = ((((INTM_T)scalar * (INTM_T)vec[i]) / scscalar) / scvec);
    #endif
  }
}

void v_q_argmax(const INT_T* const vec, ITER_T len, ITER_T* const ret) {
  INT_T max_value = vec[0];
  ITER_T max_index = 0;

  for (ITER_T i = 1; i < len; i++) {
    if (max_value < vec[i]) {
      max_index = i;
      max_value = vec[i];
    }
  }

  *ret = max_index;
}

void v_q_relu(INT_T* const vec, ITER_T len) {
  for (ITER_T i = 0; i < len; i++) {
    if (vec[i] < 0) {
      vec[i] = 0;
    }
  }
}

void v_q_exp(const INT_T* const vec, ITER_T len, INT_T* const ret,
             SCALE_T scvec, SCALE_T scret) {
  for (ITER_T i = 0; i < len; i++) {
    ret[i] = ((INT_T)(exp(((float)vec[i]) / scvec) * scret));
  }
}

void v_q_scale_up(INT_T* const vec, ITER_T len, SCALE_T scvec) {
  for (ITER_T i = 0; i < len; i++) {
    #ifdef SHIFT
      vec[i] <<= scvec;
    #else
      vec[i] *= scvec;
    #endif
  }
}

void v_q_scale_down(INT_T* const vec, ITER_T len, SCALE_T scvec) {
  for (ITER_T i = 0; i < len; i++) {
    #ifdef SHIFT
      vec[i] >>= scvec;
    #else
      vec[i] /= scvec;
    #endif
  }
}

void m_q_transpose(const INT_T* const mat, ITER_T nrows, ITER_T ncols,
                   INT_T* const ret) {
  ITER_T len = nrows * ncols, counter = 0;
  for (ITER_T i = 0; i < len; i++) {
    if (counter >= len) {
      counter -= len - 1;
    }

    ret[i] = mat[counter];
    counter += nrows;
  }
}

void m_q_reverse(const INT_T* const mat, ITER_T nrows, ITER_T ncols, ITER_T axis,
                 INT_T* const ret) {
  ITER_T len = nrows * ncols;

  if (axis == 0) {
    ITER_T col_counter = 0, row_index = len - ncols;

    for (ITER_T i = 0; i < len; i++) {
      if (col_counter >= ncols) {
        col_counter = 0;
        row_index -= ncols;
      }

      ret[i] = mat[row_index + col_counter];
      col_counter++;
    }
  } else {
    S_ITER_T row_counter = ncols - 1;
    ITER_T col_index = 0;

    for (ITER_T i = 0; i < len; i++) {
      if (row_counter < 0) {
        row_counter = ncols - 1;
        col_index += ncols;
      }

      ret[i] = mat[col_index + (ITER_T)row_counter];
      row_counter--;
    }
  }
}

void m_q_add_vec(const INT_T* const mat, const INT_T* const vec,
                 ITER_T nrows, ITER_T ncols, INT_T* const ret,
                 SCALE_T scmat, SCALE_T scvec, SCALE_T scret) {
  ITER_T len = nrows * ncols;
  for (ITER_T i = 0, w = 0; i < len; i++, w++) {
    if (w >= ncols) {
      w = 0;
    }

    #ifdef SHIFT
      ret[i] = ((mat[i] >> (scmat + scret)) + (vec[w] >> (scvec + scret)));
    #else
      ret[i] = ((mat[i] / scmat) / scret) + ((vec[w] / scvec) / scret);
    #endif
  }
}

void m_q_sub_vec(const INT_T* const mat, const INT_T* const vec,
                 ITER_T nrows, ITER_T ncols, INT_T* const ret,
                 SCALE_T scmat, SCALE_T scvec, SCALE_T scret) {
  ITER_T len = nrows * ncols;
  for (ITER_T i = 0, w = 0; i < len; i++, w++) {
    if (w >= ncols) {
      w = 0;
    }

    #ifdef SHIFT
      ret[i] = ((mat[i] >> (scmat + scret)) - (vec[w] >> (scvec + scret)));
    #else
      ret[i] = ((mat[i] / scmat) / scret) - ((vec[w] / scvec) / scret);
    #endif
  }
}

void m_q_mulvec(const INT_T* const mat, const INT_T* const vec, ITER_T nrows,
                ITER_T ncols, INT_T* const ret, SCALE_T scmat, SCALE_T scvec,
                SCALE_T H1, SCALE_T H2) {
  INTM_T treesumBuffer[ncols];
  for (ITER_T row = 0; row < nrows; row++) {
    INT_T* mat_offset = (INT_T*)mat + row * ncols;

    for (ITER_T col = 0; col < ncols; col++) {
      treesumBuffer[col] = ((INTM_T)(*mat_offset++) * (INTM_T)vec[col]);
    }

    v_q_treesum(&treesumBuffer[0], ncols, H1, H2);
    #ifdef SHIFT
      ret[row] = (treesumBuffer[0] >> (scmat + scvec));
    #else
      ret[row] = ((treesumBuffer[0] / scmat) / scvec);
    #endif
  }
}

void m_q_sparse_mulvec(const ITER_T* const col_indices, const INT_T* const mat_values,
                       const INT_T* const vec, ITER_T ndims, INT_T* const ret,
                       SCALE_T scmat, SCALE_T scvec, SCALE_T scret) {
  ITER_T iter_index = 0, iter_value = 0;
  for (ITER_T k = 0; k < ndims; k++) {
    ITER_T index = col_indices[iter_index];

    while (index != 0) {
      #ifdef SHIFT
        ret[index - 1] += (((INTM_T)mat_values[iter_value] * (INTM_T)vec[k]) >> (scmat + scvec + scret));
      #else
        ret[index - 1] += (((INTM_T)mat_values[iter_value] * (INTM_T)vec[k]) / ((INTM_T)scmat * (INTM_T)scvec * (INTM_T)scret));
      #endif
      iter_index++;
      iter_value++;
      index = col_indices[iter_index];
    }

    iter_index++;
  }
}

void t_q_add_vec(const INT_T* const mat, const INT_T* const vec,
                 ITER_T nbatches, ITER_T nrows, ITER_T ncols,
                 ITER_T nchannels, INT_T* const ret, SCALE_T scmat,
                 SCALE_T scvec, SCALE_T scret) {
  ITER_T len = nbatches * nrows * ncols * nchannels;
  for (ITER_T i = 0, c = 0; i < len; i++, c++) {
    if (c >= nchannels) {
      c = 0;
    }

    #ifdef SHIFT
      ret[i] = ((mat[i] >> (scmat + scret)) + (vec[c] >> (scvec + scret)));
    #else
      ret[i] = ((mat[i] / scmat) / scret) + ((vec[c] / scvec) / scret);
    #endif
  }
}

void t_q_sub_vec(const INT_T* const mat, const INT_T* const vec,
                 ITER_T nbatches, ITER_T nrows, ITER_T ncols,
                 ITER_T nchannels, INT_T* const ret, SCALE_T scmat,
                 SCALE_T scvec, SCALE_T scret) {
  ITER_T len = nbatches * nrows * ncols * nchannels;
  for (ITER_T i = 0, c = 0; i < len; i++, c++) {
    if (c >= nchannels) {
      c = 0;
    }

    #ifdef SHIFT
      ret[i] = ((mat[i] >> (scmat + scret)) - (vec[c] >> (scvec + scret)));
    #else
      ret[i] = ((mat[i] / scmat) / scret) - ((vec[c] / scvec) / scret);
    #endif
  }
}
