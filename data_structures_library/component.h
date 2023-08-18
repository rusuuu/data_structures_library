#pragma once

template <typename KeyType>
class component
{
private:

    KeyType key;
    component* up_left;
    component* down_right;

public:

    component(const KeyType & = KeyType());

    void setKey(const KeyType&);
    KeyType getKey();

    void setUp_Left(component*);
    component* getUp_Left();

    void setDown_Right(component*);
    component* getDown_Right();
};

template <typename KeyType>
component<KeyType>::component(const KeyType& key) : key(key)
{
    up_left = nullptr;
    down_right = nullptr;
}

template <typename KeyType>
void component<KeyType>::setKey(const KeyType& key)
{
    this->key = key;
}

template <typename KeyType>
KeyType component<KeyType>::getKey()
{
    return key;
}

template <typename KeyType>
void component<KeyType>::setUp_Left(component* up)
{
    up_left = up;
}

template <typename KeyType>
component<KeyType>* component<KeyType>::getUp_Left()
{
    return up_left;
}

template <typename KeyType>
void component<KeyType>::setDown_Right(component* down)
{
    down_right = down;
}

template <typename KeyType>
component<KeyType>* component<KeyType>::getDown_Right()
{
    return down_right;
}