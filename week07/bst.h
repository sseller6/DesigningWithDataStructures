/***********************************************************************
 * Header:
 *    BST
 * Summary:
 *    Our custom implementation of a BST for set and for map
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        BST                 : A class that represents a binary search tree
 *        BST::iterator       : An iterator through BST
 * Author
 *    Noah Li
 *    Steven Sellers
 *    Josh Hamilton
 ************************************************************************/

#pragma once

#ifdef DEBUG
#define debug(x) x
#else // !DEBUG
#define debug(x)
#endif // !DEBUG

#include <cassert>
#include <utility>
#include <memory>     // for std::allocator
#include <functional> // for std::less
#include <utility>    // for std::pair

class TestBST; // forward declaration for unit tests
class TestMap;
class TestSet;

namespace custom
{

    template <class TT>
    class set;
    template <class KK, class VV>
    class map;

    /*****************************************************************
     * BINARY SEARCH TREE
     * Create a Binary Search Tree
     *****************************************************************/
    template <typename T>
    class BST
    {
        friend class ::TestBST; // give unit tests access to the privates
        friend class ::TestMap;
        friend class ::TestSet;

        template <class KK, class VV>
        friend class map;

        template <class TT>
        friend class set;

        template <class KK, class VV>
        friend void swap(map<KK, VV>& lhs, map<KK, VV>& rhs);
    public:
        //
        // Construct
        //

        BST();
        BST(const BST& rhs);
        BST(BST&& rhs);
        BST(const std::initializer_list<T>& il);
        ~BST();

        //
        // Assign
        //

        BST& operator = (const BST& rhs);
        BST& operator = (BST&& rhs);
        BST& operator = (const std::initializer_list<T>& il);
        void swap(BST& rhs);

        //
        // Iterator
        //

        class iterator;
        iterator   begin() const noexcept;
        iterator   end()   const noexcept { return iterator(nullptr); }

        //
        // Access
        //

        iterator find(const T& t);

        // 
        // Insert
        //

        std::pair<iterator, bool> insert(const T& t, bool keepUnique = false);
        std::pair<iterator, bool> insert(T&& t, bool keepUnique = false);

        //
        // Remove
        // 

        iterator erase(iterator& it);
        void   clear() noexcept;

        // 
        // Status
        //

        bool   empty() const noexcept { return size() == 0; } // Check if the BST is empty
        size_t size()  const noexcept { return numElements; } // Return the number of elements in the BST


    private:

        class BNode;
        BNode* root;              // root node of the binary search tree
        size_t numElements;        // number of elements currently in the tree

        // Bro Helfrich's stuff that he added.
        void deleteNode(BNode*& pDelete, bool toRight);
        void deleteBinaryTree(BNode*& pDelete) noexcept;
        void copyBinaryTree(const BNode* pSrc, BNode*& pDest);
    };


    /*****************************************************************
     * BINARY NODE
     * A single node in a binary tree. Note that the node does not know
     * anything about the properties of the tree so no validation can be done.
     *****************************************************************/
    template <typename T>
    class BST <T> ::BNode
    {
    public:
        //
        // Construct
        //
        BNode() : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data() {} // from bnode
        BNode(const T& t) : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(t) {}
        BNode(T&& t) : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(std::move(t)) {}

        //
        // Insert
        //
        void addLeft(BNode* pNode);
        void addRight(BNode* pNode);
        void addLeft(const T& t);
        void addRight(const T& t);
        void addLeft(T&& t);
        void addRight(T&& t);

        // 
        // Status
        //
        bool isRightChild(BNode* pNode) const { return pRight == pNode; } // Check if a node is the right child of its parent
        bool isLeftChild(BNode* pNode) const { return pLeft == pNode; } // Check if a node is the left child of its parent

        //
        // Data
        //
        T data;                  // Actual data stored in the BNode
        BNode* pLeft;          // Left child - smaller
        BNode* pRight;         // Right child - larger
        BNode* pParent;        // Parent
        bool isRed;              // Red-black balancing stuff
    };

    /**********************************************************
     * BINARY SEARCH TREE ITERATOR
     * Forward and reverse iterator through a BST
     *********************************************************/
    template <typename T>
    class BST <T> ::iterator
    {
        friend class ::TestBST; // give unit tests access to the privates
        friend class ::TestMap;
        friend class ::TestSet;

        template <class KK, class VV>
        friend class map;

        template <class TT>
        friend class set;
    public:
        // constructors and assignment
        iterator(BNode* p = nullptr)
        {
            pNode = p;
        }
        iterator(const iterator& rhs)
        {
            pNode = rhs.pNode;
        }
        iterator& operator = (const iterator& rhs) // Copy assignment operator
        {
            pNode = rhs.pNode;
            return *this;
        }

        // compare
        bool operator == (const iterator& rhs) const
        {
            return rhs.pNode == pNode; // Equality comparison
        }
        bool operator != (const iterator& rhs) const
        {
            return rhs.pNode != pNode; // Inequality comparison
        }

        // de-reference. Cannot change because it will invalidate the BST
        const T& operator * () const
        {
            return pNode->data; // Dereference operator to access the data
        }

        // increment and decrement
        iterator& operator ++ ();
        iterator   operator ++ (int postfix)
        {
            iterator itReturn = *this;
            ++(*this);
            return itReturn;
        }
        iterator& operator -- ();
        iterator   operator -- (int postfix)
        {
            iterator itReturn = *this;
            --(*this);
            return itReturn;
        }

        // must give friend status to remove so it can call getNode() from it
        friend BST <T> ::iterator BST <T> ::erase(iterator& it);

    private:

        // the node
        BNode* pNode;
    };


    /*********************************************
     *********************************************
     *********************************************
     ******************** BST ********************
     *********************************************
     *********************************************
     *********************************************/


     /*********************************************
      * BST :: DEFAULT CONSTRUCTOR
      ********************************************/
    template <typename T>
    BST <T> ::BST()
    {
        root = nullptr;
        numElements = 0;
    }

    /*********************************************
     * BST :: COPY CONSTRUCTOR
     * Copy one tree to another
     ********************************************/
    template <typename T>
    BST <T> ::BST(const BST<T>& rhs)
    {
        root = nullptr;
        numElements = 0;

        // simply use the = operator
        *this = rhs;
    }

    /*********************************************
     * BST :: MOVE CONSTRUCTOR
     * Move one tree to another
     ********************************************/
    template <typename T>
    BST <T> ::BST(BST <T>&& rhs)
    {
        // blank slate
        root = nullptr;
        numElements = 0;

        // setting rhs to nullptr moves the rhs
        root = rhs.root;
        rhs.root = nullptr;

        // setting rhs.numElements to 0 finishes the move
        numElements = rhs.numElements;
        rhs.numElements = 0;
    }

    /*********************************************
     * BST :: INITIALIZER LIST CONSTRUCTOR
     * Create a BST from an initializer list
     ********************************************/
    template <typename T>
    BST <T> ::BST(const std::initializer_list<T>& il)
    {
        root = nullptr;
        numElements = 0;

        for (const T& value : il)
        {
            insert(value);
        }
    }

    /*********************************************
     * BST :: DESTRUCTOR
     ********************************************/
    template <typename T>
    BST <T> :: ~BST()
    {
        clear();
    }


    /*********************************************
     * BST :: ASSIGNMENT OPERATOR
     * Copy one tree to another
     ********************************************/
    template <typename T>
    BST <T>& BST <T> :: operator = (const BST <T>& rhs)
    {
        // Copy the binary tree from rhs to this tree
        copyBinaryTree(rhs.root, this->root);
        // Ensure the root's parent is null (root nodes should not have parents)
        assert(nullptr == this->root || this->root->pParent == nullptr);
        // Copy the number of elements
        this->numElements = rhs.numElements;

        // Return the current object to allow chained assignments
        return *this;
    }

    /*********************************************
     * BST :: ASSIGNMENT OPERATOR with INITIALIZATION LIST
     * Copy nodes onto a BTree
     ********************************************/
    template <typename T>
    BST <T>& BST <T> :: operator = (const std::initializer_list<T>& il)
    {
        // Delete the existing tree
        deleteBinaryTree(root);
        numElements = 0;

        // Insert elements from the initializer list
        for (auto&& element : il)
        {
            insert(element);
        }

        // Return the current object to allow chained assignments
        return *this;
    }

    /*********************************************
     * BST :: ASSIGN-MOVE OPERATOR
     * Move one tree to another
     ********************************************/
    template <typename T>
    BST <T>& BST <T> :: operator = (BST <T>&& rhs)
    {
        //clear the old bst
        clear();

        //swap the trees
        swap(rhs);

        return *this;
    }

    /*********************************************
     * BST :: SWAP
     * Swap two trees
     ********************************************/
    template <typename T>
    void BST <T> ::swap(BST <T>& rhs)
    {
        std::swap(rhs.root, root);
        std::swap(rhs.numElements, numElements);
    }

    /*****************************************************
     * BST :: INSERT
     * Insert a node at a given location in the tree
     ****************************************************/
    template <typename T>
    std::pair<typename BST <T> ::iterator, bool> BST <T> ::insert(const T& t, bool keepUnique)
    {
        std::pair<iterator, bool> pairReturn(end(), false);
        try
        {
            // If the tree is empty, create a new node for the root
            if (root == nullptr)
            {
                assert(numElements == 0); // Ensure tree is indeed empty
                root = new BNode(t); // Create the root node
                numElements = 1; // Increment number of elements
                pairReturn.first = iterator(root); // Set the iterator to the root
                pairReturn.second = true; // Indicate that the insertion was successful
                return pairReturn; // Return the iterator and success status
            }

            // Search for the correct spot to insert the new node
            BNode* node = root;
            bool done = false;
            while (!done)
            {
                // Check for uniqueness if required
                if (keepUnique && t == node->data)
                {
                    pairReturn.first = iterator(node); // Node already exists
                    pairReturn.second = false; // Indicate failure due to duplicate
                    return pairReturn; // Return the iterator and failure status
                }

                // Traverse to the left if the new value is less than current node's value
                if (t < node->data)
                {
                    if (node->pLeft)
                    {
                        node = node->pLeft; // Move to the left child
                    }
                    else
                    {
                        node->addLeft(t); // Add new node as left child
                        done = true; // Insertion done
                        pairReturn.first = iterator(node->pLeft); // Set iterator to new node
                        pairReturn.second = true; // Indicate success
                    }
                }
                // Traverse to the right if the new value is greater than or equal to current node's value
                else
                {
                    if (node->pRight)
                    {
                        node = node->pRight; // Move to the right child
                    }
                    else
                    {
                        node->addRight(t); // Add new node as right child
                        done = true; // Insertion done
                        pairReturn.first = iterator(node->pRight); // Set iterator to new node
                        pairReturn.second = true; // Indicate success
                    }
                }
            }
            assert(root != nullptr); // Ensure root is not lost
            numElements++; // Increment the element count

            // If we lost the root, find it
            while (root->pParent != nullptr)
                root = root->pParent;
            assert(root->pParent == nullptr); // Ensure root's parent is null
        }
        catch (...)
        {
            throw "ERROR: unable to allocate node"; // Handle allocation errors
        }
        return pairReturn;
    }

    template <typename T>
    std::pair<typename BST <T> ::iterator, bool> BST <T> ::insert(T&& t, bool keepUnique)
    {
        std::pair<iterator, bool> pairReturn(end(), false);
        try
        {
            // If the tree is empty, create a new node for the root
            if (root == nullptr)
            {
                assert(numElements == 0); // Ensure tree is indeed empty
                root = new BNode(std::move(t)); // Create the root node with moved value
                numElements = 1; // Increment number of elements
                pairReturn.first = iterator(root); // Set the iterator to the root
                pairReturn.second = true; // Indicate that the insertion was successful
                return pairReturn; // Return the iterator and success status
            }

            // Search for the correct spot to insert the new node
            BNode* node = root;
            bool done = false;
            while (!done)
            {
                // Check for uniqueness if required
                if (keepUnique && t == node->data)
                {
                    pairReturn.first = iterator(node); // Node already exists
                    pairReturn.second = false; // Indicate failure due to duplicate
                    return pairReturn; // Return the iterator and failure status
                }

                // Traverse to the left if the new value is less than current node's value
                if (t < node->data)
                {
                    if (node->pLeft)
                    {
                        node = node->pLeft; // Move to the left child
                    }
                    else
                    {
                        node->addLeft(std::move(t)); // Add new node as left child with moved value
                        done = true; // Insertion done
                        pairReturn.first = iterator(node->pLeft); // Set iterator to new node
                        pairReturn.second = true; // Indicate success
                    }
                }
                // Traverse to the right if the new value is greater than or equal to current node's value
                else
                {
                    if (node->pRight)
                    {
                        node = node->pRight; // Move to the right child
                    }
                    else
                    {
                        node->addRight(std::move(t)); // Add new node as right child with moved value
                        done = true; // Insertion done
                        pairReturn.first = iterator(node->pRight); // Set iterator to new node
                        pairReturn.second = true; // Indicate success
                    }
                }
            }
            assert(root != nullptr); // Ensure root is not lost
            numElements++; // Increment the element count

            // If we lost the root, find it
            while (root->pParent != nullptr)
                root = root->pParent;
            assert(root->pParent == nullptr); // Ensure root's parent is null
        }
        catch (...)
        {
            throw "ERROR: unable to allocate node"; // Handle allocation errors
        }
        return pairReturn;
    }

    /*************************************************
     * BST :: ERASE
     * Remove a given node as specified by the iterator
     ************************************************/
    template <typename T>
    typename BST <T> ::iterator BST <T> ::erase(iterator& it)
    {
        if (it == end())
        {
            return end(); // If iterator is at end, do nothing
        }

        iterator itNext = it; // Iterator to return the next node
        BNode* pDelete = it.pNode; // Node to delete

        // Case 1: Node has no left child
        if (pDelete->pLeft == nullptr)
        {
            itNext++; // Move to next node
            if (pDelete->pParent)
            {
                // Reattach the parent's pointer to the right child
                if (pDelete->pParent->pLeft == pDelete)
                {
                    pDelete->pParent->pLeft = pDelete->pRight;
                }
                else
                {
                    pDelete->pParent->pRight = pDelete->pRight;
                }

                if (pDelete->pRight)
                {
                    pDelete->pRight->pParent = pDelete->pParent;
                }
            }
            else
            {
                // Node is root, set root to right child
                root = pDelete->pRight;
                if (root)
                {
                    root->pParent = nullptr;
                }
            }
        }
        // Case 2: Node has no right child
        else if (pDelete->pRight == nullptr)
        {
            itNext++; // Move to next node
            if (pDelete->pParent)
            {
                // Reattach the parent's pointer to the left child
                if (pDelete->pParent->pLeft == pDelete)
                {
                    pDelete->pParent->pLeft = pDelete->pLeft;
                }
                else
                {
                    pDelete->pParent->pRight = pDelete->pLeft;
                }

                if (pDelete->pLeft)
                {
                    pDelete->pLeft->pParent = pDelete->pParent;
                }
            }
            else
            {
                // Node is root, set root to left child
                root = pDelete->pLeft;
                if (root)
                {
                    root->pParent = nullptr;
                }
            }
        }
        // Case 3: Node has two children
        else
        {
            BNode* pIOS = pDelete->pRight; // Find in-order successor
            while (pIOS->pLeft != nullptr)
            {
                pIOS = pIOS->pLeft;
            }

            if (pIOS->pParent != pDelete)
            {
                // Reattach the in-order successor's parent to its right child
                if (pIOS->pParent->pLeft == pIOS)
                {
                    pIOS->pParent->pLeft = pIOS->pRight;
                }
                else
                {
                    pIOS->pParent->pRight = pIOS->pRight;
                }

                if (pIOS->pRight)
                {
                    pIOS->pRight->pParent = pIOS->pParent;
                }

                pIOS->pRight = pDelete->pRight;
                pDelete->pRight->pParent = pIOS;
            }

            if (pDelete->pParent)
            {
                // Reattach the parent's pointer to the in-order successor
                if (pDelete->pParent->pLeft == pDelete)
                {
                    pDelete->pParent->pLeft = pIOS;
                }
                else
                {
                    pDelete->pParent->pRight = pIOS;
                }
            }
            else
            {
                // Node is root, set root to in-order successor
                root = pIOS;
            }

            pIOS->pParent = pDelete->pParent;
            pIOS->pLeft = pDelete->pLeft;
            pDelete->pLeft->pParent = pIOS;

            itNext = iterator(pIOS); // Set iterator to the in-order successor
        }

        delete pDelete; // Delete the node
        numElements--; // Decrement the number of elements

        return itNext; // Return the iterator to the next node
    }

    /*****************************************************
     * BST :: CLEAR
     * Removes all the BNodes from a tree
     ****************************************************/
    template <typename T>
    void BST <T> ::clear() noexcept
    {
        if (root)
        {
            deleteBinaryTree(root); // Delete all nodes recursively
        }
        numElements = 0; // Reset the number of elements
    }

    /*****************************************************
     * BST :: BEGIN
     * Return the first node (left-most) in a binary search tree
     ****************************************************/
    template <typename T>
    typename BST <T> ::iterator custom::BST <T> ::begin() const noexcept
    {
        if (root == nullptr)
            return end(); // If tree is empty, return end iterator

        BNode* p = root;
        while (p->pLeft)
            p = p->pLeft; // Traverse to the leftmost node
        return iterator(p); // Return iterator to the leftmost node

    }


    /****************************************************
     * BST :: FIND
     * Return the node corresponding to a given value
     ****************************************************/
    template <typename T>
    typename BST <T> ::iterator BST<T> ::find(const T& t)
    {
        // Start the search from the root node
        for (BNode* p = root; p != nullptr; p = (t < p->data ? p->pLeft : p->pRight))
        {
            // Check if the current node's data matches the target value
            if (p->data == t)
            {
                return iterator(p); // Return an iterator to the found node
            }
        }

        // If the value is not found, return the end iterator
        return end();

    }

    /******************************************************
     ******************************************************
     ******************************************************
     *********************** B NODE ***********************
     ******************************************************
     ******************************************************
     ******************************************************/


     /******************************************************
      * BINARY NODE :: ADD LEFT
      * Add a node to the left of the current node
      ******************************************************/
    template <typename T>
    void BST <T> ::BNode::addLeft(BNode* pNode)
    {
        pLeft = pNode;
        if (pNode)
            pNode->pParent = this;
    }

    /******************************************************
     * BINARY NODE :: ADD RIGHT
     * Add a node to the right of the current node
     ******************************************************/
    template <typename T>
    void BST <T> ::BNode::addRight(BNode* pNode)
    {
        pRight = pNode;
        if (pNode)
            pNode->pParent = this;
    }

    /******************************************************
     * BINARY NODE :: ADD LEFT
     * Add a node to the left of the current node
     ******************************************************/
    template <typename T>
    void BST<T> ::BNode::addLeft(const T& t)
    {
        assert(pLeft == nullptr);

        try
        {
            BNode* pNode = new BNode(t);
            addLeft(pNode);
        }
        catch (...)
        {
            throw "ERROR: Unable to allocate a node";
        }
    }

    /******************************************************
     * BINARY NODE :: ADD LEFT
     * Add a node to the left of the current node
     ******************************************************/
    template <typename T>
    void BST<T> ::BNode::addLeft(T&& t)
    {
        assert(pLeft == nullptr);

        try
        {
            BNode* pNode = new BNode(std::move(t));
            addLeft(pNode);
        }
        catch (...)
        {
            throw "ERROR: Unable to allocate a node";
        }
    }

    /******************************************************
     * BINARY NODE :: ADD RIGHT
     * Add a node to the right of the current node
     ******************************************************/
    template <typename T>
    void BST <T> ::BNode::addRight(const T& t)
    {
        assert(pRight == nullptr);

        try
        {
            BNode* pNode = new BNode(t);
            addRight(pNode);
        }
        catch (...)
        {
            throw "ERROR: Unable to allocate a node";
        }
    }

    /******************************************************
     * BINARY NODE :: ADD RIGHT
     * Add a node to the right of the current node
     ******************************************************/
    template <typename T>
    void BST <T> ::BNode::addRight(T&& t)
    {
        assert(pRight == nullptr);

        try
        {
            BNode* pNode = new BNode(std::move(t));
            addRight(pNode);
        }
        catch (...)
        {
            throw "ERROR: Unable to allocate a node";
        }
    }



    /**************************************************
       * BST node :: deletebinary tree
       *
       *************************************************/
    template <typename T>
    void BST <T> ::deleteBinaryTree(BNode*& pDelete) noexcept
    {
        if (pDelete == nullptr)
            return;
        deleteBinaryTree(pDelete->pLeft);
        deleteBinaryTree(pDelete->pRight);

        delete pDelete;
        pDelete = nullptr;
    }

    /**************************************************
     * BST node :: copy binary tree
     *
     *************************************************/
    template <typename T>
    void BST <T> ::copyBinaryTree(const BNode* pSrc, BNode*& pDest)
    {
        if (pSrc == nullptr)
        {
            deleteBinaryTree(pDest);
            return;
        }

        assert(pSrc);
        try
        {
            if (nullptr == pDest)
                pDest = new BST::BNode(pSrc->data);

            else
                pDest->data = pSrc->data;
        }
        catch (...)
        {
            throw "ERROR: Unable to allocate a node";
        }
        assert(pDest != nullptr);

        copyBinaryTree(pSrc->pLeft, pDest->pLeft);
        if (pSrc->pLeft)
            pDest->pLeft->pParent = pDest;

        copyBinaryTree(pSrc->pRight, pDest->pRight);
        if (pSrc->pRight)
            pDest->pRight->pParent = pDest;
    }

    /**************************************************
     * BST node :: delete node
     *
     *************************************************/
    template <typename T>
    void BST <T> ::deleteNode(BNode*& pDelete, bool toRight)
    {
        BNode* pNext = (toRight ? pDelete->pRight : pDelete->pLeft);

        if (pDelete != root)
        {
            if (pDelete->pParent->pLeft == pDelete)
            {
                pDelete->pParent->pLeft = pNext;
            }
            else
            {
                pDelete->pParent->pRight = pNext;
            }

            if (pNext)
            {
                pNext->pParent = pDelete->pParent;
            }
        }
        else
        {
            root = pNext;
            if (pNext)
            {
                pNext->pParent = nullptr;
            }
        }
    }
    /*************************************************
     *************************************************
     *************************************************
     ****************** ITERATOR *********************
     *************************************************
     *************************************************
     *************************************************/

     /**************************************************
      * BST ITERATOR :: INCREMENT PREFIX
      * advance by one
      *************************************************/
    template <typename T>
    typename BST <T> ::iterator& BST <T> ::iterator :: operator ++ ()
    {
        if (pNode == nullptr) return *this; // If at end, do nothing
        if (pNode->pRight)
        {
            pNode = pNode->pRight; // Move to the right child
            while (pNode->pLeft)
            {
                pNode = pNode->pLeft; // Then move to the leftmost child
            }
        }
        else
        {
            BNode* pSave = pNode;
            pNode = pNode->pParent;
            while (pNode && pNode->pRight == pSave)
            {
                pSave = pNode; // Move up until we find a node that is a left child
                pNode = pNode->pParent;
            }
        }
        return *this; // Return the updated iterator

    }

    /**************************************************
     * BST ITERATOR :: DECREMENT PREFIX
     * advance by one
     *************************************************/
    template <typename T>
    typename BST <T> ::iterator& BST <T> ::iterator :: operator -- ()
    {
        if (pNode == nullptr) return *this; // If at end, do nothing
        if (pNode->pLeft)
        {
            pNode = pNode->pLeft; // Move to the left child
            while (pNode->pRight)
            {
                pNode = pNode->pRight; // Then move to the rightmost child
            }
        }
        else
        {
            BNode* pSave = pNode;
            pNode = pNode->pParent;
            while (pNode && pNode->pLeft == pSave)
            {
                pSave = pNode; // Move up until we find a node that is a right child
                pNode = pNode->pParent;
            }
        }
        return *this; // Return the updated iterator


    }


} // namespace custom


