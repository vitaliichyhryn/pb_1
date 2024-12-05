#include <math.h>

bool is_trngl(double a, double b, double c) {
	return a + b > c && b + c > a && c + a > b;
}

double get_prmtr(double a, double b, double c) {
	return a + b + c;
}

double get_semiprmtr(double a, double b, double c) {
	return get_prmtr(a, b, c) / 2.0;
}

double get_area(double a, double b, double c) {
	double s = get_semiprmtr(a, b, c);
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

double get_alt(double a, double b, double c) {
	return 2.0 * get_area(a, b, c) / a;
}

double get_med(double a, double b, double c) {
	return 0.5 * sqrt(2.0 * pow(b, 2.0) + 2.0 * pow(c, 2.0) - pow(a, 2.0));
}

double get_bisec(double a, double b, double c) {
	double s = get_semiprmtr(a, b, c);
	return (2.0 * sqrt(b * c * s * (s - a))) / (b + c);
}