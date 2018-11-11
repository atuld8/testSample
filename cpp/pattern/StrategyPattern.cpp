/*
 * =====================================================================================
 *
 *       Filename:  StrategyPattern.cpp
 *
 *    Description:  The strategy pattern used to define a family of algorithms and encapsulate each one as object,
 *                  and make them interchangeble.
 *
 *        Version:  1.0
 *        Created:  11/10/18 23:27:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>

using namespace std;

class CSortStrategy {
    public:
        virtual void sort () = 0;
};

class CSearchStrategy {
    public:
        virtual void search () = 0;
};

class CMergeSort : public CSortStrategy {
    public:
        virtual void sort () {
            cout << "Merge sort" << endl;
        }
};

class CQuickSort : public CSortStrategy {
    public:
        virtual void sort () {
            cout << "Quick sort" << endl;
        }
};

class CHeapSort : public CSortStrategy {
    public:
        virtual void sort () {
            cout << "Heap sort" << endl;
        }
};

class CSequencialSearch : public CSearchStrategy {
    public:
        virtual void search () {
            cout << "Sequencial search" << endl;
        }
};

class CBinaryTreeSearch : public CSearchStrategy {
    public:
        virtual void search () {
            cout << "BinaryTree search" << endl;
        }
};

class CHashTableSearch : public CSearchStrategy {
    public:
        virtual void search () {
            cout << "HashTable search" << endl;
        }
};

class CContext {
    public:
        enum SORT_TYPE {
            NON_SORT,
            MERGE_SORT,
            QUICK_SORT,
            HEAP_SORT
        };

        enum SEARCH_TYPE {
            NON_SEARCH,
            SEQUENCIAL_SEARCH,
            BINARY_TREE_SEARCH,
            HASH_TABLE_SEARCH

        };

        CContext () : m_pSortStrategy (NULL), m_pSearchStrategy (NULL) {
        }

        ~CContext () {
            if (m_pSortStrategy) delete m_pSortStrategy;

            if (m_pSearchStrategy) delete m_pSearchStrategy;
        }

        void setStrategy (SORT_TYPE eSortType = NON_SORT, SEARCH_TYPE eSearchType = NON_SEARCH) {

           switch (eSortType) {
               case MERGE_SORT:
                   setSortStrategy ( new CMergeSort );
                   break;
               case QUICK_SORT:
                   setSortStrategy ( new CQuickSort );
                   break;
               case HEAP_SORT:
                   setSortStrategy ( new CHeapSort );
                   break;
               case NON_SORT:
               default:
                   setSortStrategy (NULL);
           }

           switch (eSearchType) {
               case SEQUENCIAL_SEARCH:
                   setSearchStrategy ( new CSequencialSearch );
                   break;
               case BINARY_TREE_SEARCH:
                   setSearchStrategy ( new CBinaryTreeSearch );
                   break;
               case HASH_TABLE_SEARCH:
                   setSearchStrategy ( new CHashTableSearch );
                   break;
               case NON_SEARCH:
               default:
                   setSearchStrategy (NULL);
           }
        }

        void performAction () {
            m_pSortStrategy->sort ();
            m_pSearchStrategy->search ();
        }

    protected:
        void setSortStrategy (CSortStrategy * pSortStrategy) {
            if (m_pSortStrategy) delete m_pSortStrategy;

            m_pSortStrategy = pSortStrategy;
        }

        void setSearchStrategy (CSearchStrategy * pSearchStrategy) {
            if (m_pSearchStrategy) delete m_pSearchStrategy;

            m_pSearchStrategy = pSearchStrategy;
        }

    private:
        CSortStrategy   * m_pSortStrategy;
        CSearchStrategy * m_pSearchStrategy;
};

int main () {
    CContext context;

    context.setStrategy (context.MERGE_SORT, context.HASH_TABLE_SEARCH);
    context.performAction ();

    return 0;
}
