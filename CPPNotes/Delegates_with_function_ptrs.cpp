using FP = const char * (*)();

const char * ErrorMessage1() { return "Empty"; }
const char * ErrorMessage2() { return "Timeout"; }

void ShowError(FP fpe) { std::cout << fpe() << std::endl; }

int main() 
{
	FP fpe = ErrorMessage1;
	ShowError(fpe);
	fpe = ErrorMessage2;
	ShowError(fpe);
}
