/*
 * the addition of an int to a char const * results in a char const *
 * Adding a std::string to a char const* on the other hand results in a std::string
 *
 * Determine the return type of a function template:
 */
 
// [1]
template <class T, class U>
auto add(T const & t, U const & u) -> decltype(t+u) {
  return t+u;
}

// [2]
template<typename Container>
auto begin(Container & c) -> decltype(c.begin()) {
  return c.begin();
}

template<typename Container>
auto begin(const Container & c) -> decltype(c.begin()) {
  return c.begin();
}
