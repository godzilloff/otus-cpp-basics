#include <iostream>
#include <limits>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;

	bool valid_data = false;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::min()} {
	}

	void update(double next) override {
		if (!valid_data) {
			valid_data = true;
			m_min = next;
			return;
		}

		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min = 0.;
};

class Max : public IStatistics {
public:
	Max() : m_max{ std::numeric_limits<double>::max() } {
	}

	void update(double next) override {
		if (!valid_data) {
			valid_data = true;
			m_max = next;
			return;
		}

		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char* name() const override {
		return "max";
	}

private:
	double m_max = 0.;
};

class Mean : public IStatistics {
public:
	Mean() : m_mean{} {
	}

	void update(double next) override {
		m_mean = m_mean * (cnt / (cnt + 1)) + next / (cnt + 1);
		cnt++;
	}

	double eval() const override {
		return m_mean;
	}

	const char* name() const override {
		return "mean";
	}

private:
	double m_mean = 0.;
	double cnt = 0.;
};

class StdDeviation : public IStatistics {
public:
	StdDeviation() : m_mean{} {
	}

	void update(double next) override {
		m_mean = m_mean * (cnt / (cnt + 1)) + next / (cnt + 1);
		cnt++;

		xn.push_back(next);

		double summ = 0.;
		for (int ii = 0; ii < xn.size(); ii++) {
			summ += (xn[ii] - m_mean) * (xn[ii] - m_mean);
		}

		m_std_deviation = sqrt(summ / xn.size());
	}

	double eval() const override {
		return m_std_deviation;
	}

	const char* name() const override {
		return "std";
	}

private:
	double m_mean = 0.;
	double m_std_deviation = 0.;
	double cnt = 0.;
	std::vector<double> xn{};
};

int main() {

	const size_t statistics_count = 4;
	IStatistics* statistics[statistics_count]{};

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new StdDeviation{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}
