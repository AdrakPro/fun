#ifndef CODEREVIEWTASK_MYVECTOR_HPP
#define CODEREVIEWTASK_MYVECTOR_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <utility>

template <typename T>
class MyVector {
private:
	struct Data {
		std::vector<T> elements;
		std::vector<std::string> names;
	};

	std::shared_ptr<Data> m_data;

	// Check if data is shared
	void detach() {
		if(!m_data.unique()) {
			m_data = std::make_shared<Data>(*m_data);
		}
	}

public:
	using value_type = T;
	using allocator_type = std::allocator<T>;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = typename std::allocator_traits<allocator_type>::pointer;
	using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
	using iterator = typename std::vector<T>::iterator;
	using const_iterator = typename std::vector<T>::const_iterator;
	using reverse_iterator = typename std::vector<T>::reverse_iterator;
	using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

	MyVector() : m_data(std::make_shared<Data>()) {}

	MyVector(const MyVector& other) : m_data(other.m_data) {}

	MyVector(MyVector&& other) noexcept : m_data(std::move(other.m_data)) {}

	MyVector& operator=(const MyVector& other) {
		if (this != &other) {
			m_data = other.m_data;
		}

		return *this;
	}

	~MyVector() = default;

	void push_back(const T& obj, const std::string& name) {
		detach();
		m_data->elements.push_back(obj);
		m_data->names.push_back(name);
	}

	void push_back(T&& obj, std::string&& name) {
		detach();
		m_data->elements.push_back(std::move(obj));
		m_data->names.push_back(std::move(name));
	}

	std::pair<const T&, const std::string&> operator[](int index) const {
		if (index < 0 || static_cast<size_type>(index) >= m_data->elements.size()) {
			throw std::out_of_range("Index is out of range");
		}

		return std::pair<const T&, const std::string&>(m_data->elements[index], m_data->names[index]);
	}

	std::pair<T&, std::string&> operator[](int index) {
		if (index < 0 || static_cast<size_type>(index) >= m_data->elements.size()) {
			throw std::out_of_range("Index is out of range");
		}

		detach();
		return std::pair<T&, std::string&>(m_data->elements[index], m_data->names[index]);
	}

	const T& operator[](const std::string& name) const {
		auto iterator = std::find(m_data->names.begin(), m_data->names.end(), name);

		if (iterator == m_data->names.end()) {
			throw std::invalid_argument(name + " is not found in the MyVector");
		}

		size_type index = static_cast<size_type>(std::distance(m_data->names.begin(), iterator));
		return m_data->elements[index];
	}

	T& operator[](const std::string& name) {
		auto iterator = std::find(m_data->names.begin(), m_data->names.end(), name);

		if (iterator == m_data->names.end()) {
			throw std::invalid_argument(name + " is not found in the MyVector");
		}
		detach();
		size_type index = static_cast<size_type>(std::distance(m_data->names.begin(), iterator));
		return m_data->elements[index];
	}

	iterator begin() {
			detach();
			return m_data->elements.begin();
	}

	const_iterator begin() const {
			return m_data->elements.begin();
	}

	const_iterator cbegin() const {
			return m_data->elements.cbegin();
	}

	iterator end() {
			detach();
			return m_data->elements.end();
	}

	const_iterator end() const {
			return m_data->elements.end();
	}

	const_iterator cend() const {
			return m_data->elements.cend();
	}

	bool empty() const {
			return m_data->elements.empty();
	}

	size_type size() const {
			return m_data->elements.size();
	}

	void reserve(size_type new_capacity) {
			detach();
			m_data->elements.reserve(new_capacity);
			m_data->names.reserve(new_capacity);
	}

	void clear() {
			detach();
			m_data->elements.clear();
			m_data->names.clear();
	}
};

#endif //CODEREVIEWTASK_MYVECTOR_HPP
