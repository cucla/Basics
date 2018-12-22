/* OOP
 * the Big-Five: destructor, copy constructor, move constructor,
 * copy assignment operator=, move assignment operator=
 *
 * Pointer data member
 */

class IntCell {
public:
	explicit IntCell(int initialValue = 0) { val = new int{ initialValue }; }
	~IntCell() { delete val; }
	IntCell(const IntCell & rhs) { val = new int{ *rhs.val }; }
	IntCell(IntCell && rhs) noexcept : val{ rhs.val } { rhs.val = nullptr; }
	IntCell & operator= (const IntCell & rhs) {
		if (this != &rhs) {
			*val = *rhs.val;
			return *this;
		}
	}
	IntCell & operator= (IntCell && rhs) noexcept {
		std::swap(val, rhs.val);
		return *this;
	}
	int getVal() const { return *val; }
	void setVal(int x) { *val = x; }
private:
	int * val;
};

