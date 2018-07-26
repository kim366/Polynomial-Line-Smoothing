template<typename ParamT, int Degree>
Polynomial<ParamT, Degree>::Polynomial(std::initializer_list<ParamT> params_)
    : _params{params_}
{
}