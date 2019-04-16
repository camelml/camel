#include <armadillo>
#include <iostream>
using namespace arma;
template <typename T>
inline bool approx_equal_cpp(const T& lhs, const T& rhs, double tol = 0.001) {
  return arma::approx_equal(lhs, rhs, "absdiff", tol);
}
bool check_for_missing_vales(mat to_be_checked, int num_cols)
{
    if(num_cols==to_be_checked.n_cols)
        continue;
    else
        system_error("wrong number of columns passed");
    for(int i=0;i<to_be_checked.n_cols;i++)
    {
        if()
        std::cout << "Column "<<i<<" of the matrix has "<<arma::size(arma::);
    }
    return false;
}
void clear_memories(mat x, bool fill_missing_if_there=false)
{
    if(!fill_missing_if_there)
        continue;
    else
    {
        if (check_for_missing_vales())
    }
}


arma::mat unique_rows(const arma::mat& m) {

  arma::uvec ulmt = arma::zeros<arma::uvec>(m.n_rows);

  for (arma::uword i = 0; i < m.n_rows; i++) {
    for (arma::uword j = i + 1; j < m.n_rows; j++) {
      if (approx_equal_cpp(m.row(i), m.row(j))) { ulmt(j) = 1; break; }
    }
  }

  return m.rows(find(ulmt == 0));

}

arma::mat unique_cols(const arma::mat& m) {

  arma::uvec vlmt = arma::zeros<arma::uvec>(m.n_cols);

  for (arma::uword i = 0; i < m.n_cols; i++) {
    for (arma::uword j = i + 1; j < m.n_cols; j++) {
      if (approx_equal_cpp(m.col(i), m.col(j))) { vlmt(j) = 1; break; }
    }
  }

  return m.cols(find(vlmt == 0));

}
