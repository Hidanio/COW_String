#pragma once

#include <iostream>
#include <cstring>

class StringWrapper {
private:
    char *data;

public:
    explicit StringWrapper(const char *init) : data(new char[strlen(init) + 1]) {
        strcpy(data, init);
    }

    StringWrapper(const StringWrapper &other) : data(new char[strlen(other.data) + 1]) {
        strcpy(data, other.data);
    }

    ~StringWrapper() {
        delete[] data;
    }

    char &operator[](size_t index) {
        std::cout << "StringWrapper operator[] called" << "\n";
        return data[index];
    }

    const char &operator[](size_t index) const {
        std::cout << "StringWrapper const operator[] called" << "\n";
        return data[index];
    }

    StringWrapper &operator=(const StringWrapper &other) {
        if (this != &other) {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
            std::cout << "StringWrapper copy assigned" << "\n";
        }
        return *this;
    }

    StringWrapper &operator=(StringWrapper &&other) noexcept {
        if (this != &other) {
            data = other.data;
            std::cout << "StringWrapper move assigned" << "\n";
        }
        return *this;
    }

    StringWrapper operator+(const StringWrapper &other) {
        size_t new_length = strlen(data) + strlen(other.data);
        char *new_data = new char[new_length + 1];
        strcpy(new_data, data);
        strcat(new_data, other.data);
        StringWrapper result(new_data);
        delete[] new_data;
        return result;
    }

    StringWrapper substr(size_t start, size_t length) {
        if (start + length > strlen(data)) length = strlen(data) - start;
        char *sub = new char[length + 1];
        strncpy(sub, data + start, length);
        sub[length] = '\0';
        StringWrapper result(sub);
        delete[] sub;
        return result;
    }

    void debug() const {
        std::cout << "Data: " << data << std::endl;
    }

    [[nodiscard]] const char *getData() const {
        return data;
    }

    friend std::ostream &operator<<(std::ostream &os, const StringWrapper &str) {
        os << str.data;
        return os;
    }
};

class CowString {
private:
    StringWrapper *data;
    int *ref_count;

    void detach() {
        if (*ref_count > 1) {
            (*ref_count)--;
            data = new StringWrapper(*data);
            ref_count = new int(1);
        }
    }

public:
    CowString(const char *init = "") : data(new StringWrapper(init)), ref_count(new int(1)) {}

    CowString(const CowString &other) : data(other.data), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    CowString &operator=(const CowString &other) {
        if (this != &other) {
            if (--(*ref_count) == 0) {
                delete data;
                delete ref_count;
            }
            data = other.data;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    ~CowString() {
        if (--(*ref_count) == 0) {
            delete data;
            delete ref_count;
        }
    }

    CowString operator+(const CowString &other) {
        detach();
        return CowString((*data + *other.data).getData());
    }

    CowString substr(size_t start, size_t length) {
        return CowString(data->substr(start, length).getData());
    }

    const char &operator[](size_t index) const {
        return (*data)[index];
    }

    char &operator[](size_t index) {
        detach();
        return (*data)[index];
    }

    void debug() const {
        std::cout << "Data: " << data->getData() << ", RefCount: " << *ref_count << "\n";
    }

    friend std::ostream &operator<<(std::ostream &os, const CowString &str) {
        return os << *str.data;
    }
};
