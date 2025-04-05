#pragma once

#include "cs/cs_util.hpp"

#include <memory>

template<typename Type>
class Dynamic_Array
{
public:
    Dynamic_Array() = default;

    void reserve(int64 new_size)
    {
        _resize(new_size);
    }

    void push_back(const Type& value)
    {
        if (_size == _capacity)
        {
            _resize(_capacity == 0 ? 1 : _capacity * 2);
        }

        new (_data + _size++) Type(value);
    }

    void push_back(Type&& value)
    {
        if (_size == _capacity)
        {
            _resize(_capacity == 0 ? 1 : _capacity * 2);
        }

        new (_data + _size++) Type(std::move(value));
    }

    void clear() 
    {
        for (int64 i = 0; i < _size; ++i)
        {
            _data[i].~Type();
        }
        _size = 0;
    }

    void pop_back() 
    {
        if (_size == 0) return;
        _data[_size - 1].~Type();
        --_size;
    }

    void erase(size_t index) 
    {
        _data[index].~Type();  // Destroy the element at the index

        // Shift elements to the left
        for (int64 i = index; i < _size - 1; ++i)
        {
            new (_data + i) Type(std::move(_data[i + 1]));  // Move next element
        }
        --_size;
    }

    void enqueue(const Type& value)
    {
        push_back(value);
    }

    void enqueue(Type&& value)
    {
        push_back(value);
    }

    Type& dequeue()
    {
        assert(_size > 0);
        Type ret = _data[0];
        erase(0);
        return ret;
    }

    Type& operator[](int64 index)
    {
        assert(_size > 0 && index >= 0 && index < _size);
        return _data[index];
    }

    Type& operator[](int64 index) const
    {
        assert(_size > 0 && index >= 0 && index < _size);
        return _data[index];
    }

    template<typename Predicate>
    int64 find_if(Predicate predicate) const
    {
        for (int64 i = 0; i < _size; ++i)
        {
            if (predicate(_data[i]))
            {
                return i;
            }
        }

        return -1;
    }

    template<typename Predicate>
    bool erase_if(Predicate predicate)
    {
        for (int64 i = 0; i < _size; ++i)
        {
            if (predicate(_data[i]))
            {
                erase(i);
                return true;
            }
        }

        return false;
    }

    template<typename Predicate>
    int64 erase_all_if(Predicate predicate)
    {
        int64 count = 0;

        for (int64 i = 0; i < _size;)
        {
            if (predicate(_data[i]))
            {
                erase(i);
                ++count;
            }
            else
            {
                ++i;
            }
        }

        return count;
    }

    int64 get_size() const { return _size; }
    int64 get_capacity() const { return _capacity; }

    Type& front() { assert(_size > 0); return _data[0]; }
    Type& front() const { assert(_size > 0); return _data[0]; }

    Type& back() { assert(_size > 0); return _data[_size - 1]; }
    Type& back() const { assert(_size > 0); return _data[_size - 1]; }

    // Iterator support
    Type* begin() { return _data; }
    Type* end() { return _data + _size; }

    const Type* begin() const { return _data; }
    const Type* end() const { return _data + _size; }

    const Type* cbegin() const { return _data; }
    const Type* cend() const { return _data + _size; }

    std::reverse_iterator<Type*> rbegin() { return std::reverse_iterator<Type*>(end()); }
    std::reverse_iterator<Type*> rend() { return std::reverse_iterator<Type*>(begin()); }
    
    std::reverse_iterator<const Type*> rbegin() const { return std::reverse_iterator<const Type*>(end()); }
    std::reverse_iterator<const Type*> rend() const { return std::reverse_iterator<const Type*>(begin()); }
    
    std::reverse_iterator<const Type*> crbegin() const { return std::reverse_iterator<const Type*>(cend()); }
    std::reverse_iterator<const Type*> crend() const { return std::reverse_iterator<const Type*>(cbegin()); }
private:
    Type* _data { nullptr };
    int64 _capacity { 0 }, _size { 0 };

    using Allocator = std::allocator<Type>;
    Allocator _allocator;

private:
    void _resize(int64 new_capacity)
    {
        // No need to resize
        if (new_capacity <= _capacity)
        {
            return;
        }

        Type* new_data = _allocator.allocate(new_capacity);
        for (int64 i = 0; i < _size; ++i) 
        {
            new (new_data + i) Type(std::move(_data[i]));
            _data[i].~Type();
        }

        _allocator.deallocate(_data, _capacity);
        _data = new_data;
        _capacity = new_capacity;
    }
};
