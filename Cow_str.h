#include <memory>
#include <iostream>
#include <string>
#include <utility>

#ifndef COW_STR_COW_STR_H
#define COW_STR_COW_STR_H

class StringWrapper {
private:
    std::string data;

public:
    explicit StringWrapper(std::string init) : data(std::move(init)) {
        std::cout << "StringWrapper constructed" << "\n";
    }

    explicit StringWrapper(std::string_view init) : data(init) {
        std::cout << "StringWrapper constructed" << "\n";
    }

    explicit StringWrapper(const char *init) : data(init) {
        std::cout << "StringWrapper constructed" << "\n";
    }

    StringWrapper(StringWrapper const &other): data(other.data){
        std::cout << "StringWrapper copied" << "\n";
    }

    StringWrapper(StringWrapper&& other) noexcept : data(std::move(other.data)){
        std::cout << "StringWrapper moved" << "\n";
    }

    StringWrapper& operator=(const StringWrapper &other) {
        if (this != &other) {
            data = other.data;
            std::cout << "StringWrapper copy assigned" << "\n";
        }
        return *this;
    }

    StringWrapper& operator=(StringWrapper &&other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            std::cout << "StringWrapper move assigned" << "\n";
        }
        return *this;
    }

    char& operator[](size_t index) {
        std::cout << "StringWrapper operator[] called" << "\n";
        return data[index];
    }

    const char& operator[](size_t index) const {
        std::cout << "StringWrapper const operator[] called" << "\n";
        return data[index];
    }

    ~StringWrapper(){
        std::cout << "StringWrapper Destroyed" << "\n";

    }

    void debug() const {
        std::cout << "Data: " << data << std::endl;
    }

    std::string printData() const {
        return data;
    }

    friend std::ostream &operator<<(std::ostream &os, const StringWrapper &str) {
        return os << str.data;
    }
};

class CowString {
private:
    std::shared_ptr<StringWrapper> counter_data_;

public:
    explicit CowString(std::string_view init = "") : counter_data_(std::make_shared<StringWrapper>(init)) {
        std::cout << "CowString constructed with data: " << *counter_data_ << "\n";
    }

    CowString(const CowString &other) : counter_data_(other.counter_data_) {
        std::cout << "CowString copied" << "\n";
    }

    CowString& operator=(const CowString &other) {
        if (this != &other) {
            counter_data_ = other.counter_data_;
            std::cout << "CowString assigned" << "\n";
        }
        return *this;
    }

    const char &operator[](size_t index) const {
        std::cout << "operator[] called" << "\n";
        return (*counter_data_)[index];
    }

    char &operator[](size_t index) {
        std::cout << "Non-const operator[] called" << "\n";

        if (!counter_data_.unique()) {
            counter_data_ = std::make_shared<StringWrapper>(*counter_data_);
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

#endif //COW_STR_COW_STR_H
