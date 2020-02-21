// Ruben Navarro
// 02/21/2020
// Dinner Plates
// Vector which mimic stacks, keeps track of pushing and popping from specific locations in the vector.

#include <iostream>
#include <vector>
#include <algorithm>


class DinnerPlates {
public:
    int cap = 0;
    int vectIndex = 0;

    // vector to hold index that have been popped from stack
    std::vector<int> piv;
    // 2d vector as main data structure
    std::vector<std::vector<int>> v;
    // vector used as a stack to store pushed in values
    std::vector<int> v2;

    // DinnerPlates constructor
    DinnerPlates(int capacity) {
        cap = capacity;
    }

    // function to puck into vector of vectors
    void push(int val) {
        // create stack in vector
        if (v.empty()) {
            v.push_back(v2);
            if (v.size() == 1)
                vectIndex = 0;
        }
        // if vector is not empty and the inner vector is at max capacity, increases size of vector
        else if (!v.empty() && v[v.size() - 1].size() == cap) {
            v.push_back(v2);
            ++vectIndex;
        }

        // push val to vector from piv vector if it is not empty and the index is less than vector size
        if (!piv.empty() && piv[0] < v.size()) {
            v[piv.front()].push_back(val);
            piv.erase(piv.begin() + 0);
        }
        // push value into vector from piv vector if piv is not empty
        else if (!piv.empty() && piv[0] >= v.size()) {
            v[vectIndex].push_back(val);
            piv.erase(piv.begin() + 0);
        }
        // if piv vector is empty, push value into stack
        else if (piv.empty()) {
            v[vectIndex].push_back(val);
        }
    }
    // pops value from vector
    int pop() {
        // returns -1 is vector of stacks is empty
        if (v.empty())
            return -1;

        // assigns last val to be returned, and pops back of stack.
        int n;

        // if final vector is empty pop from main vector
        for (int i = v.size(); i > 0; --i) {
            if (v[i - 1].empty())
                continue;
            else if (!v[i - 1].empty()) {
                n = v[i - 1].back();
                v[i - 1].pop_back();

                if (v[i - 1].empty())
                    --vectIndex;
                break;
            }
        }

        // traverses through vector and pops trailing empty vectors from main vector
        for (int j = v.size(); j > 0; --j) {
            if (v[j - 1].empty()) {
                v.pop_back();
                if (v[j - 1].empty()) {
                    --vectIndex;
                }
            }
            else if (!v[j - 1].empty())
                break;
        }
        return n;
    }

    int popAtStack(int index) {
        // returns -1 if vector of stacks is empty
        if (v.empty())
            return -1;

        // returns -1 if index is larger than size of vector
        if (index > v.size() - 1)
            return -1;
        // returns -1 if specific vector is empty
        if (v[index].empty())
            return -1;

        // pops back of vector and assigns value to piv vector for tracking
        int n;
        n = v[index].back();
        piv.push_back(index);
        v[index].pop_back();

        // sorts vector
        std::sort(piv.begin(), piv.end());

        // if vector is not empty and back of array is empty pops back of main vector and increases vector index
        if (!v.empty() && v[v.size() - 1].empty()) {
            v.pop_back();
            --vectIndex;
        }
        // returns popped value
        return n;
    }

    void displayVect() {
        std::cout << "---------START OF VECTOR-----------\n";
        for (int i = 0; i < v.size(); ++i) {
            for (int x = 0; x < v[i].size(); ++x) {
                std::cout << v[i][x] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "----------END OF VECTOR-----------\n";
    }
};

int main() {

    DinnerPlates* obj = new DinnerPlates(2);
    obj->push(1);
    obj->push(2);
    obj->push(3);
    obj->push(4);
    obj->push(5);
    obj->popAtStack(0);
    obj->push(20);
    obj->push(21);
    obj->displayVect();
    obj->popAtStack(0);
    obj->popAtStack(2);
    obj->displayVect();

    return 0;
}
