template<class... T> struct foo;

template<class R, class C, class... T> struct foo<R (C::*)(T...)&&> {};


int main()
{
}
