#include <memory>
#include <iostream>
#include <string>
#include <utility>

#ifndef COW_STR_COW_STR_H
#define COW_STR_COW_STR_H

class CowString {
private:
    std::shared_ptr<std::string> counter_data_;

public:
    explicit CowString(std::string_view init = "") : counter_data_(std::make_shared<std::string>(init)) {
        std::cout << "CowString constructed with data: " << *counter_data_ << "\n";
    }

    CowString(const CowString &other) : counter_data_(other.counter_data_) {
        std::cout << "CowString copied" << "\n";
    }

    const char &operator[](size_t index) const {
        std::cout << "operator[] called" << "\n";
        return (*counter_data_)[index];
    }

    CowString& operator=(const CowString &other) {
        if (this != &other) {
            counter_data_ = other.counter_data_;
            std::cout << "CowString assigned" << "\n";
        }
        return *this;
    }

    char &operator[](size_t index) {
        std::cout << "Non-const operator[] called" << "\n";

        if (!counter_data_.unique()) {
            counter_data_ = std::make_shared<std::string>(*counter_data_);
        }
        std::cout << "Detached for modification" << "\n";

        return (*counter_data_)[index];
    }

    void debug() {
        std::cout << "Pointers: " << counter_data_.get() << " , Data: " << *counter_data_
                  << ", RefCounter: " << counter_data_.use_count() << "\n";
    }

    friend std::ostream &operator<<(std::ostream &os, const CowString &str) {
        return os << *str.counter_data_;
    }
};

class StringWrapper {
private:
    std::string data;

public:
    explicit StringWrapper(std::string init) : data(std::move(init)) {
        std::cout << "StringWrapper constructed" << std::endl;
    }

    char& operator[](size_t index) {
        std::cout << "StringWrapper operator[] called" << std::endl;
        return data[index];
    }

    void debug() const {
        std::cout << "Data: " << data << std::endl;
    }
};

#endif //COW_STR_COW_STR_H
