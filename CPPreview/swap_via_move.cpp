void swap01(double & x, double & y) {
	double tmp = x;
	x = y;
	y = tmp;
}

void swap02(std::vector<std::string> & x, std::vector<std::string> & y) {
	std::vector<std::string> tmp = static_cast<std::vector<std::string> &&>(x);
	x = static_cast<std::vector<std::string> &&>(y);
	y = static_cast<std::vector<std::string> &&>(tmp);
}

void swap03(std::vector<std::string> & x, std::vector<std::string> & y) {
	std::vector<std::string> tmp = std::move(x);
	x = std::move(y);
	y = std::move(tmp);
}
