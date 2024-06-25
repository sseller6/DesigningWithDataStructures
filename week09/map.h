/***********************************************************************
 * Header:
 *    map
 * Summary:
 *    Our custom implementation of a std::map
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        map                 : A class that represents a map
 *        map::iterator       : An iterator through a map
 * Author
 *    <Noah, Josh, Steve>
 ************************************************************************/

#pragma once

#include "pair.h"     // for pair
#include "bst.h"      // no nested class necessary for this assignment

#ifndef debug
#ifdef DEBUG
#define debug(x) x
#else
#define debug(x)
#endif // DEBUG
#endif // !debug

class TestMap; // forward declaration for unit tests

namespace custom
{

    /*****************************************************************
     * MAP
     * Create a Map, similar to a Binary Search Tree
     *****************************************************************/
    template <class K, class V>
    class map
    {
        friend ::TestMap; // give unit tests access to the privates
        template <class KK, class VV>
        friend void swap(map<KK, VV>& lhs, map<KK, VV>& rhs);
    public:
        using Pairs = custom::pair<K, V>;

        // 
        // Construct
        //
        map() : bst() {}

        map(const map& rhs) : bst(rhs.bst) {}

        map(map&& rhs) noexcept : bst(std::move(rhs.bst))
        {
            rhs.bst.root = nullptr; // Nullify the source BST root
            rhs.bst.numElements = 0; // Reset the element count
        }

        template <class Iterator>
        map(Iterator first, Iterator last) : bst()
        {
            insert(first, last);
        }

        map(const std::initializer_list<Pairs>& il) : bst()
        {
            insert(il);
        }

        ~map()
        {
            clear(); // Clear
        }

        //
        // Assign
        //
        map& operator = (const map& rhs)
        {
            if (this != &rhs) // Avoid self-assignment
            {
                clear(); // Clear current elements
                bst = rhs.bst; // Copy the BST
            }
            return *this;
        }

        map& operator = (map&& rhs)
        {
            if (this != &rhs)
            {
                clear(); // Clear current elements
                bst = std::move(rhs.bst); // Move the BST
                rhs.bst.root = nullptr; // Nullify the source BST root
                rhs.bst.numElements = 0; // Reset the element count of the source BST
            }
            return *this;
        }

        map& operator = (const std::initializer_list<Pairs>& il)
        {
            clear(); // Clear current elements
            insert(il); // Insert elements from the initializer list
            return *this;
        }

        // 
        // Iterator
        //
        class iterator;
        iterator begin()
        {
            return iterator(bst.begin());
        }

        iterator end()
        {
            return iterator(bst.end());
        }

        // 
        // Access
        //
        const V& operator [] (const K& k) const;
        V& operator [] (const K& k);
        const V& at(const K& k) const;
        V& at(const K& k);
        iterator    find(const K& k)
        {
            return iterator(bst.find(Pairs(k, V()))); //Find it by key
        }

        //
        // Insert
        //
        custom::pair<typename map::iterator, bool> insert(const Pairs& rhs) // Insert a pair (copy)
        {
            auto result = bst.insert(rhs);
            return custom::pair<iterator, bool>(iterator(result.first), result.second);
        }

        custom::pair<typename map::iterator, bool> insert(Pairs&& rhs) // Insert a pair (move)
        {
            auto result = bst.insert(std::move(rhs));
            return custom::pair<iterator, bool>(iterator(result.first), result.second);
        }

        template <class Iterator>
        void insert(Iterator first, Iterator last) // Insert range of elements
        {
            for (auto it = first; it != last; ++it)
                bst.insert(*it);
        }

        void insert(const std::initializer_list<Pairs>& il) // Insert elements from initializer list
        {
            insert(il.begin(), il.end());
        }

        //
        // Remove
        //
        void clear() noexcept
        {
            bst.clear();
        }
        size_t erase(const K& k);
        iterator erase(iterator it);
        iterator erase(iterator first, iterator last);

        //
        // Status
        //
        bool empty() const noexcept { return bst.size() == 0; } // Check if it's empty
        size_t size() const noexcept { return bst.size(); }


    private:

        // the students DO NOT need to use a nested class
        BST < pair <K, V >> bst;
    };


    /**********************************************************
     * MAP ITERATOR
     * Forward and reverse iterator through a Map, just call
     * through to BSTIterator
     *********************************************************/
    template <typename K, typename V>
    class map <K, V> ::iterator
    {
        friend class ::TestMap; // give unit tests access to the privates
        template <class KK, class VV>
        friend class custom::map;
    public:
        //
        // Construct
        //
        iterator()
        {
        }
        iterator(const typename BST<pair<K, V>>::iterator& rhs) : it(rhs) {} // Initialize
        iterator(const iterator& rhs) = default;

        //
        // Assign
        //
        iterator& operator = (const iterator& rhs)
        {
            if (this != &rhs)
                it = rhs.it; // Copy
            return *this;
        }

        //
        // Compare
        //
        bool operator == (const iterator& rhs) const { return it == rhs.it; }
        bool operator != (const iterator& rhs) const { return it != rhs.it; }

        // 
        // Access
        //
        const pair <K, V>& operator * () const
        {
            return *it;
        }

        //
        // Increment
        //
        iterator& operator++()
        {
            ++it;
            return *this;
        }

        iterator operator++(int postfix)
        {
            iterator tmp = *this;
            ++it;
            return tmp;
        }

        iterator& operator--()
        {
            --it;
            return *this;
        }

        iterator operator--(int postfix)
        {
            iterator tmp = *this;
            --it;
            return tmp;
        }

    private:

        // Member variable
        typename BST < pair <K, V >>  ::iterator it;
    };


    /*****************************************************
     * MAP :: SUBSCRIPT
     * Retrieve an element from the map
     ****************************************************/
    template <typename K, typename V>
    V& map <K, V> :: operator [] (const K& key)
    {
        std::cout << "Inserting/Accessing key: " << key << std::endl;
        auto it = bst.find(Pairs(key, V()));
        if (it != bst.end()) {
            // Key already exists, return the existing value
            return (*it).second;
        }
        else {
            // Key does not exist, insert a new pair with the default value
            auto result = bst.insert(Pairs(key, V()));
            std::cout << "Insert result: " << result.second << "; Value: " << (*result.first).second << std::endl;
            return (*result.first).second;
        }
    }

    /*****************************************************
     * MAP :: SUBSCRIPT
     * Retrieve an element from the map
     ****************************************************/
    template <typename K, typename V>
    const V& map <K, V> :: operator [] (const K& key) const
    {
        auto it = bst.find(Pairs(key, V())); // Find the key in the BST
        if (it == bst.end())
            throw std::out_of_range("invalid map key"); // Throw exception if key is not found
        return it->second;
    }

    /*****************************************************
     * MAP :: AT
     * Retrieve an element from the map
     ****************************************************/
    template <typename K, typename V>
    V& map <K, V> ::at(const K& key)
    {
        auto it = bst.find(Pairs(key, V())); // Find the key in the BST
        if (it == bst.end())
            throw std::out_of_range("invalid map<K, T> key"); // Throw exception if key is not found
        return (*it).second;
    }

    /*****************************************************
     * MAP :: AT
     * Retrieve an element from the map
     ****************************************************/
    template <typename K, typename V>
    const V& map <K, V> ::at(const K& key) const
    {
        auto it = bst.find(Pairs(key, V())); // Find the key in the BST
        if (it == bst.end())
            throw std::out_of_range("invalid map<K, T> key"); // Throw exception if key is not found
        return (*it).second;
    }

    /*****************************************************
     * SWAP
     * Swap two maps
     ****************************************************/
    template <typename K, typename V>
    void swap(map <K, V>& lhs, map <K, V>& rhs)
    {
        using std::swap; // Use the standard swap function
        swap(lhs.bst, rhs.bst); // Swap the BSTs of the two maps
    }

    /*****************************************************
     * ERASE
     * Erase one element
     ****************************************************/
    template <typename K, typename V>
    size_t map<K, V>::erase(const K& k)
    {
        auto it = bst.find(Pairs(k, V())); // Find the key in the BST
        if (it != bst.end())
        {
            bst.erase(it); // Erase the element if found
            return 1; // Return the number of elements erased
        }
        return 0; // Return 0 if the element was not found

    }

    /*****************************************************
     * ERASE
     * Erase several elements
     ****************************************************/
    template <typename K, typename V>
    typename map<K, V>::iterator map<K, V>::erase(map<K, V>::iterator first, map<K, V>::iterator last)
    {
        while (first != last)
        {
            first = erase(first); // Erase elements in the range
        }
        return first; // Return the iterator to the new end
    }

    /*****************************************************
     * ERASE
     * Erase one element
     ****************************************************/
    template <typename K, typename V>
    typename map<K, V>::iterator map<K, V>::erase(map<K, V>::iterator it)
    {
        return iterator(bst.erase(it.it)); // Erase the element and return the new iterator
    }

}; //  namespace custom

