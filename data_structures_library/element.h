#pragma once

#include <iostream>

template <typename KeyType, typename ValueType>
class element
{
private:
    char status;
    KeyType key;
    ValueType value;

public:
    element();
    element(KeyType, ValueType);

    void setStatus(char);
    char getStatus();

    void setKey(KeyType);
    KeyType getKey();

    void setValue(ValueType);
    ValueType getValue();
};

template <typename KeyType, typename ValueType>
element<KeyType, ValueType>::element()
{
    this->status = 'f';
    this->key = KeyType();
    this->value = ValueType();
}

template <typename KeyType, typename ValueType>
element<KeyType, ValueType>::element(KeyType key, ValueType value)
{
    this->status = 'f';
    this->key = key;
    this->value = value;
}

template <typename KeyType, typename ValueType>
void element<KeyType, ValueType>::setStatus(char status)
{
    if (status == 'o' || status == 'f' || status == 'd')
        this->status = status;
}

template <typename KeyType, typename ValueType>
char element<KeyType, ValueType>::getStatus()
{
    return this->status;
}

template <typename KeyType, typename ValueType>
void element<KeyType, ValueType>::setKey(KeyType key)
{
    this->key = key;
}

template <typename KeyType, typename ValueType>
KeyType element<KeyType, ValueType>::getKey()
{
    return this->key;
}

template <typename KeyType, typename ValueType>
void element<KeyType, ValueType>::setValue(ValueType value)
{
    this->value = value;
}

template <typename KeyType, typename ValueType>
ValueType element<KeyType, ValueType>::getValue()
{
    return this->value;
}