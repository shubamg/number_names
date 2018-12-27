#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <sstream>
using namespace std;
using lli =  long long int;

const vector<string> digits{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const vector<string> ten_to_nineteen{"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const vector<string> multiples_of_ten{"", "", "twen", "thir", "for", "fif", "six", "seven", "eight", "nine"};
const string TWO_DIGIT_SUFFIX{"ty"};
const vector<string> triplet_name{"", "thousand", "million", "billion", "trillion"};
const string HUNDRED{"hundred"};

// converts a number to its number name for three digit number
list<string> get_number_name_of_three_digit_number(int three_digit_block) {
	if(three_digit_block >= 1000 || three_digit_block < 0) {
		cout<<"three digit block out of range"<<endl;
		throw;
	}
	int hundreds, tens, ones;
	list<string> three_digit_number_name{};
	hundreds = three_digit_block / 100;
	tens = (three_digit_block/10) % 10;
	ones = three_digit_block%10;
	if (hundreds) {
		three_digit_number_name.push_back(digits[hundreds]);
		three_digit_number_name.push_back(HUNDRED);
	}
	if(tens == 1)
		three_digit_number_name.push_back(ten_to_nineteen[ones]);
	else {
		if(tens)
			three_digit_number_name.push_back(string(multiples_of_ten[tens])+TWO_DIGIT_SUFFIX);
		if(ones)
			three_digit_number_name.push_back(digits[ones]);
	}
	return three_digit_number_name;
}

// converts a number to its number name
pair<lli, list<string>> get_number_name(lli number) {
	unsigned int three_digit_block, three_digit_block_index=0;
	lli original_number = number;
	list <string> number_name{}, three_digit_number_name;
	while(number) {
		if(three_digit_block_index == triplet_name.size()) {
			cout<<"Oops! Only number < 1000 trillion are allowed"<<endl;
			throw;
		}
		three_digit_block = number % 1000;
		number /= 1000;
		three_digit_number_name = get_number_name_of_three_digit_number(three_digit_block);
		if(three_digit_number_name.size()) {
			three_digit_number_name.push_back(triplet_name[three_digit_block_index]);
			number_name.splice(number_name.begin(), three_digit_number_name);
		}
		three_digit_block_index++;
	}
	return make_pair(original_number, number_name);
}

void print_number_name(lli number) {
	stringstream number_name;
	auto number_and_name = get_number_name(number);
	list<string> number_name_list = number_and_name.second;
	auto begin_itr = number_name_list.begin();
	number_name<<number<<": ";
	if(number_name_list.size()) {
		number_name<<*(begin_itr);
		begin_itr++;
	}
	else
		number_name<<digits[0];
	for_each(begin_itr, number_name_list.end(), [&number_name] (string& s) -> void {number_name<<" "<<s;});
	cout<<number_name.str()<<endl;
}

int main() {
	vector<lli> numbers{0L, 1L, 300L, 324L, 456L, 135678906L, 1230000004567L};
	for_each(numbers.begin(), numbers.end(), print_number_name);
	return 0;
}




