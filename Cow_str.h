#include <memory>
#include <iostream>
#include <string>

#ifndef COW_STR_COW_STR_H
#define COW_STR_COW_STR_H

class CowString {
private:
    std::shared_ptr<std::string> counter_data_;

public:
    explicit CowString(std::string_view init = "") : counter_data_(std::make_shared<std::string>(init)) {

    }

    CowString(const CowString &other) = default;

    const char &operator[](size_t index) const {
        return (*counter_data_)[index];
    }

    char &operator[](size_t index) {
        // some logic for detaching
        if (!counter_data_.unique()) {
            counter_data_ = std::make_shared<std::string>(*counter_data_);
        }

        return (*counter_data_)[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const CowString &str) {
        return os << *str.counter_data_;
    }
};

#endif //COW_STR_COW_STR_H
