#include "vectorCow.hpp"
#include <iostream>

int main() {
	try {
		MyVector<int> vector;

		vector.push_back(42, "Hello");
		vector.push_back(2324, "Adam");

		std::cout << "Element 0: " << vector[0].first << " (" << vector[0].second << ")" << std::endl;

		vector["Adam"] = 13;
		std::cout << "Modified element 'Adam': " << vector["Adam"] << std::endl;

        std::cout << "Is vector empty? " << vector.empty() << std::endl;

        vector.reserve(10);
        std::cout << "Size after reserve: " << vector.size() << std::endl;

        vector.clear();
        std::cout << "Size after clear: " << vector.size() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
