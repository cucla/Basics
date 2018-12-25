template<typename Object>
class Matrix {
public:
	Matrix(int rows, int cols) : m(rows) {
		for (auto & el : m)
			el.resize(cols);
	}
	Matrix(std::vector<std::vector<Object>> v) : m{ v } {}
	Matrix(std::vector<std::vector<Object>> && v) : m{ std::move(v) } {}

	const std::vector<Object> & operator[](int row) const {
		return m[row];
	}
	std::vector<Object> & operator[](int row) {
		return m[row];
	}
	int numrows() const {
		return m.size();
	}
	int numcols() const {
		return numrows() ? m[0].size() : 0;
	}
private:
	std::vector<std::vector<Object>> m;
};
