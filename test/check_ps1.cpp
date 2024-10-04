template<class... T> struct foo;

template<class R, class... T> struct foo<R(T...)> {};


int main()
{
}
