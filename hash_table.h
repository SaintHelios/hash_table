#pragma once
#include <string>
#include <iostream>

template <typename data_type>
class hash_table {
private:
	struct node {
		std::string key;
		data_type value;
		node* next;
		node(std::string key, data_type value, node* next = nullptr) {
			this->key = key;
			this->value = value; 
			this->next = next;
		}
	};
	node** arr;
	size_t size;
private:
	size_t hash_value(std::string key) { return ( (key[0] * 26 - 97) + key[1]) % size; }
public:
	explicit hash_table(size_t size = 100);
	void add(std::string key, data_type value);
	data_type find(std::string key);
	~hash_table();
};

template <typename data_type> hash_table<data_type>::hash_table(size_t size) {
	this->size = size;
	arr = new node*[this->size];
	for (size_t i = 0; i < this->size; ++i) {
		arr[i] = nullptr;
	}
}

template <typename data_type> void hash_table<data_type>::add(std::string key, data_type value) {
	size_t position = hash_value(key);
	if (arr[position] == nullptr) arr[position] = new node(key, value);

	else {
		node* iterator;
		iterator = arr[position];
		while (iterator->next != nullptr) {
			iterator = iterator->next;
		}
		iterator->next = new node(key, value);
	}
}

template <typename data_type> data_type hash_table<data_type>::find(std::string key) {
	size_t position = hash_value(key);
	if (arr[position] == nullptr) std::cout << "there is no row with such key" << std::endl;

	else if (arr[position]->key == key) return arr[position]->value;

	else {
		node* iterator;
		iterator = arr[position]->next;
		while (iterator->next != nullptr) {
			if (iterator->key == key) return iterator->value;
			iterator = iterator->next;
		}
		if (iterator->key == key) return iterator->value;
		else std::cout << "there is no row with such key" << std::endl;
	}
}

template <typename data_type> hash_table<data_type>::~hash_table() {
	for (size_t i = 0; i < size; ++i) {
		if (arr[i] != nullptr) {
			if (arr[i]->next == nullptr) delete arr[i];
			else {
				node* victim;
				node* iterator = arr[i];
				while (iterator != nullptr) {
					victim = iterator;
					iterator = iterator->next;
					delete victim;
				}
			}
		}
	}
	delete arr;
}