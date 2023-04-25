#include <iostream>
#include <cstdlib>

float MAX_EXTENSION = 2.700;
long ini_val = 838800;	 	///To varry as ini_val < 838860, 838860 > ini_val < 1677721, 838860 > 1677721,
float EXT_COUNTS = 440000.00;
float ext_value = 000.000;
long ifvfb = 0;
int total_count = 0;
float ctba = 0;
float abr_diff = 0;
float ard_val = 0;
long temp_ext_count = 0;   ///actual sensor signal


float raw_ext_count();
float get_ext_count(float ext_val);
float get_ext_value();



int main() {
	std::cin >> temp_ext_count;
	float temp;
	temp = get_ext_value();
	std::cout << temp << std::endl;
	return 0;
}


float raw_ext_count () {			///removes last digit?!
	temp_ext_count = temp_ext_count / 10;
	return temp_ext_count;
}


float get_ext_count (float ext_val) {		///actual byte conversion logic
	if (total_count == 0){
		total_count = 1;
		ifvfb = ini_val;
		}
	if (ext_val != 838860 && ext_val != 1677721) {
		if (abs(ifvfb - ext_val) > 1000000 && ctba == 0) {
			if (ext_val >= 0 && ext_val <= 838860) {
				abr_diff = abs(ifvfb - 1677721);
				ctba = abr_diff;
			}
			if (ext_val <= 1677721 && ext_val >= 838860) {
				abr_diff = abs(ifvfb);
			}
			else {
				return abr_diff;
			}
		}
		if (ifvfb < 838860) {
			if (ctba == 0) {
				ard_val = abs(ext_val - ifvfb);
			}
			else if (ctba != 0) {
				if (abs(1677721-ext_val) > 1000000) {
					if (ext_val >= 0 && ext_val <= 838860) {
						ard_val = abs(ext_val - ctba);
					}
					if (ext_val <= 1677721 && ext_val >= 838860) {
						ard_val = abs(ctba - abs(ext_val - 1677721));
					}
					else {
						ard_val = abs(ctba + abs(ext_val - 1677721));
					}
				}
			}
			else {
				return ard_val;
			}
		}
		if (ifvfb > 838860) {
			if (ctba == 0) {
				ard_val = abs(ext_val - ifvfb);
			}
			else if (ctba != 0) {
				if (abs(1677721-ext_val) > 1000000) {
					if (ext_val >= 0 && ext_val <= 838860) {
						ard_val = abs(ext_val + ctba);
					}
					if (ext_val <= 1677721 && ext_val >= 838860) {
						ard_val = abs(ctba + abs(ext_val - 1677721));
					};
				}
				else {
					ard_val = abs(ctba + abs(ext_val - 1677721));
				}
			}
			return ard_val;
			}
		}
		return ext_val;
}

float get_ext_value() {
	temp_ext_count = raw_ext_count();
	if (temp_ext_count > 0) {
		float temp;
		temp = (get_ext_count(temp_ext_count) * MAX_EXTENSION) / EXT_COUNTS;
		return temp;
	}
	else {
	return 0;
	}
}
