/*
    =============================================================
     UNDERSTANDING std::vector IN C++ — A COMPLETE WALKTHROUGH
    =============================================================

    A vector is a dynamic array from the C++ Standard Template
    Library (STL). Unlike a plain array, it can grow and shrink
    at runtime, and it manages its own memory for you.

    This file is organized into small demo functions, one per
    concept, all called from main() in a logical learning order.
    Compile with:  g++ -std=c++17 vectors_tutorial.cpp -o vectors_tutorial
    Run with:       ./vectors_tutorial
*/

#include <bits/stdc++.h>   // pulls in <vector>, <algorithm>, <numeric>, etc.
using namespace std;

// Small helper just for printing a vector<int> neatly in every demo below.
// Passed by "const reference" so we don't waste time copying the vector
// just to print it (more on why this matters later in the file).
void printVec(const vector<int>& v, const string& label = "") {
    if (!label.empty()) cout << label << ": ";
    cout << "[ ";
    for (int x : v) cout << x << " ";
    cout << "]\n";
}

/* ------------------------------------------------------------
   1. DECLARATION AND INITIALIZATION
   Different ways to create a vector, depending on what you know
   at the time of creation.
   ------------------------------------------------------------ */
void demo_declaration() {
    cout << "\n===== 1. DECLARATION AND INITIALIZATION =====\n";

    vector<int> a;                     // empty vector, size 0
    vector<int> b(5);                  // size 5, all elements default-initialized to 0
    vector<int> c(5, 7);               // size 5, all elements set to 7
    vector<int> d = {1, 2, 3, 4, 5};   // initializer-list syntax (most common in practice)
    vector<int> e(d);                  // copy constructor: e is a full copy of d
    vector<int> f(d.begin(), d.begin() + 3); // construct from a range [begin, begin+3)

    printVec(a, "a (empty)");
    printVec(b, "b (size 5, default 0)");
    printVec(c, "c (size 5, value 7)");
    printVec(d, "d (initializer list)");
    printVec(e, "e (copy of d)");
    printVec(f, "f (first 3 elements of d)");

    // A vector of vectors works exactly the same way — this is how you
    // build a 2D grid. See demo_2d_vector() below for a full example.
    vector<vector<int>> grid(3, vector<int>(4, 0)); // 3 rows x 4 cols, all 0
    cout << "grid is " << grid.size() << " rows x " << grid[0].size() << " cols\n";
}

/* ------------------------------------------------------------
   2. ADDING ELEMENTS
   push_back() vs emplace_back() — both add to the end.
   ------------------------------------------------------------ */
void demo_adding_elements() {
    cout << "\n===== 2. ADDING ELEMENTS =====\n";

    vector<int> v;
    v.push_back(10);       // copies/moves 10 into the vector
    v.push_back(20);
    v.emplace_back(30);    // constructs the element in-place at the end;
                            // for plain int this behaves the same as push_back,
                            // but for objects (like pair/struct) it avoids
                            // building a temporary object first — it's the
                            // more efficient choice for non-trivial types.
    printVec(v, "after push_back/emplace_back");

    // insert() lets you add an element (or range) at any position,
    // not just the end. It's O(n) because everything after the
    // insertion point has to shift over.
    v.insert(v.begin() + 1, 15); // insert 15 at index 1
    printVec(v, "after insert(15) at index 1");
}

/* ------------------------------------------------------------
   3. ACCESSING ELEMENTS
   Several ways to read/write elements, with different safety
   guarantees.
   ------------------------------------------------------------ */
void demo_accessing_elements() {
    cout << "\n===== 3. ACCESSING ELEMENTS =====\n";

    vector<int> v = {100, 200, 300, 400, 500};

    cout << "v[2]       = " << v[2] << "  (operator[], NO bounds checking — fast but unsafe)\n";
    cout << "v.at(2)    = " << v.at(2) << "  (bounds-checked — throws std::out_of_range if invalid)\n";
    cout << "v.front()  = " << v.front() << "  (first element, same as v[0])\n";
    cout << "v.back()   = " << v.back() << "  (last element, same as v[v.size()-1])\n";
    cout << "v.data()   points to the underlying raw array — useful when calling C APIs\n";

    // Demonstrating why at() is safer:
    try {
        cout << v.at(100) << "\n"; // way out of bounds
    } catch (const out_of_range& e) {
        cout << "Caught exception from v.at(100): " << e.what() << "\n";
    }
    // v[100] would NOT throw — it's undefined behavior (could crash, could
    // silently return garbage). Prefer at() when you're not 100% sure the
    // index is valid; prefer [] in hot loops where you've already verified
    // bounds, since it avoids the extra check.
}

/* ------------------------------------------------------------
   4. SIZE vs CAPACITY
   This is the concept that trips up most beginners. size() is
   "how many elements are actually stored." capacity() is "how
   much memory is currently reserved before a reallocation is
   needed." Vectors over-allocate to make push_back() amortized
   O(1) instead of O(n) every single time.
   ------------------------------------------------------------ */
void demo_size_vs_capacity() {
    cout << "\n===== 4. SIZE vs CAPACITY =====\n";

    vector<int> v;
    cout << "size=" << v.size() << " capacity=" << v.capacity() << "\n";

    // Watch capacity grow in jumps, not one at a time, as we push_back.
    for (int i = 1; i <= 10; i++) {
        v.push_back(i);
        cout << "after push_back(" << i << "): size=" << v.size()
             << " capacity=" << v.capacity() << "\n";
    }
    // Typical output shows capacity doubling (1,2,4,8,16...) rather than
    // growing by exactly 1 each time — this is why push_back() is called
    // "amortized O(1)": most calls are instant, occasionally one call
    // pays the cost of copying everything to a bigger block.

    // reserve(n) pre-allocates capacity for n elements up front.
    // Use this BEFORE a loop of many push_backs when you know (or can
    // estimate) the final size — it avoids repeated reallocation/copying.
    vector<int> w;
    w.reserve(1000);
    cout << "\nAfter reserve(1000): size=" << w.size()
         << " capacity=" << w.capacity() << "  (size is still 0!)\n";

    // resize(n) actually changes size — it adds/removes real elements.
    w.resize(5, -1); // now has 5 elements, each set to -1
    printVec(w, "after resize(5, -1)");

    // shrink_to_fit() asks the implementation to release unused capacity
    // (not guaranteed, but usually works) — useful after removing a lot
    // of elements from a vector you plan to keep around for a while.
    w.shrink_to_fit();
    cout << "after shrink_to_fit: capacity=" << w.capacity() << "\n";
}

/* ------------------------------------------------------------
   5. ITERATING OVER A VECTOR
   Four common styles, each useful in different situations.
   ------------------------------------------------------------ */
void demo_iterating() {
    cout << "\n===== 5. ITERATING =====\n";

    vector<int> v = {1, 2, 3, 4, 5};

    // (a) Classic index loop — use this when you need the index itself
    cout << "index loop: ";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << "\n";

    // (b) Range-based for loop — cleanest when you just need the values
    cout << "range-based for (by value): ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // (c) Range-based for with a reference — lets you MODIFY elements
    // in place. Without '&' you'd only be modifying a local copy.
    for (int& x : v) x *= 10;
    cout << "after 'for (int& x : v) x *= 10': ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // (d) Iterators — needed for algorithms like insert/erase that
    // operate on positions rather than values, and for reverse iteration.
    cout << "forward iterator: ";
    for (auto it = v.begin(); it != v.end(); ++it) cout << *it << " ";
    cout << "\n";

    cout << "reverse iterator: ";
    for (auto it = v.rbegin(); it != v.rend(); ++it) cout << *it << " ";
    cout << "\n";
}

/* ------------------------------------------------------------
   6. REMOVING ELEMENTS
   pop_back(), erase(), and clear() — and the classic "erase
   while iterating" trap.
   ------------------------------------------------------------ */
void demo_removing_elements() {
    cout << "\n===== 6. REMOVING ELEMENTS =====\n";

    vector<int> v = {1, 2, 3, 4, 5};
    v.pop_back(); // removes last element, O(1)
    printVec(v, "after pop_back()");

    v.erase(v.begin() + 1); // removes element at index 1, O(n) — shifts everything after it
    printVec(v, "after erase(index 1)");

    v.erase(v.begin(), v.begin() + 2); // erase a RANGE: removes indices [0,2)
    printVec(v, "after erase(range [0,2))");

    // --- Common pitfall: erasing while looping with a normal for-loop ---
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    // WRONG-STYLE (shown here only to explain the bug, not to copy):
    //   for (int i = 0; i < nums.size(); i++)
    //       if (nums[i] % 2 == 0) nums.erase(nums.begin() + i);
    // This skips elements! Erasing shifts everything left, so the next
    // index you check has already moved into position i, and you jump
    // right past it without checking it.

    // CORRECT pattern using the erase-remove idiom:
    nums.erase(remove_if(nums.begin(), nums.end(),
                          [](int x) { return x % 2 == 0; }),
               nums.end());
    printVec(nums, "after erase-remove idiom (removed all even numbers)");
    // remove_if() shifts all the elements you want to KEEP to the front
    // and returns an iterator to the new "logical end". erase() then
    // actually deletes the leftover junk from that point to the real end.

    vector<int> toClear = {9, 9, 9};
    toClear.clear(); // removes all elements, size becomes 0 (capacity may remain)
    cout << "after clear(): size=" << toClear.size()
         << " empty()=" << (toClear.empty() ? "true" : "false") << "\n";
}

/* ------------------------------------------------------------
   7. 2D VECTORS (VECTOR OF VECTORS)
   The standard way to represent a grid/matrix in competitive
   programming and general C++.
   ------------------------------------------------------------ */
void demo_2d_vector() {
    cout << "\n===== 7. 2D VECTORS =====\n";

    int rows = 3, cols = 4;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    // Fill it with row*10 + col just so we have distinct values to see
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            grid[r][c] = r * 10 + c;

    cout << "grid contents:\n";
    for (const auto& row : grid) {
        for (int val : row) cout << val << "\t";
        cout << "\n";
    }

    // IMPORTANT PITFALL: vector<vector<int>> grid(rows, vector<int>(cols));
    // creates 'rows' INDEPENDENT copies of the inner vector — modifying
    // grid[0] does NOT affect grid[1]. This is different from a raw
    // pointer-based 2D array where a mistake could alias rows together.
    grid[0][0] = 999;
    cout << "after grid[0][0]=999, grid[1][0] is still " << grid[1][0] << " (unaffected)\n";
}

/* ------------------------------------------------------------
   8. VECTOR OF PAIRS / STRUCTS
   Very common in competitive programming for storing (value, index)
   or (x, y) style data that you want to sort together.
   ------------------------------------------------------------ */
void demo_vector_of_pairs() {
    cout << "\n===== 8. VECTOR OF PAIRS =====\n";

    vector<pair<int,int>> points = {{3, 1}, {1, 2}, {2, 0}};

    // Default sort on pairs compares .first, then .second as a tiebreaker.
    sort(points.begin(), points.end());
    cout << "sorted by (first, then second): ";
    for (auto& p : points) cout << "(" << p.first << "," << p.second << ") ";
    cout << "\n";

    // Custom comparator: sort by .second instead, using a lambda.
    sort(points.begin(), points.end(),
         [](const pair<int,int>& a, const pair<int,int>& b) {
             return a.second < b.second;
         });
    cout << "sorted by second only:            ";
    for (auto& p : points) cout << "(" << p.first << "," << p.second << ") ";
    cout << "\n";

    // structured bindings (C++17) make reading pairs much cleaner
    for (const auto& [x, y] : points) {
        cout << "x=" << x << " y=" << y << "  ";
    }
    cout << "\n";
}

/* ------------------------------------------------------------
   9. COMMON ALGORITHMS FROM <algorithm> / <numeric>
   These work on vectors via iterators and are usually faster
   and clearer than writing the loop yourself.
   ------------------------------------------------------------ */
void demo_algorithms() {
    cout << "\n===== 9. COMMON ALGORITHMS =====\n";

    vector<int> v = {5, 3, 8, 1, 9, 3, 2};
    printVec(v, "original");

    sort(v.begin(), v.end());
    printVec(v, "sort() ascending");

    sort(v.begin(), v.end(), greater<int>());
    printVec(v, "sort() descending");

    reverse(v.begin(), v.end());
    printVec(v, "reverse()");

    cout << "*max_element = " << *max_element(v.begin(), v.end()) << "\n";
    cout << "*min_element = " << *min_element(v.begin(), v.end()) << "\n";

    long long total = accumulate(v.begin(), v.end(), 0LL); // 0LL = long long start value
    cout << "accumulate (sum) = " << total << "\n";

    // binary search functions REQUIRE a sorted range
    sort(v.begin(), v.end());
    bool found = binary_search(v.begin(), v.end(), 8);
    cout << "binary_search(8) = " << (found ? "true" : "false") << "\n";

    auto it = lower_bound(v.begin(), v.end(), 3); // first element >= 3
    cout << "lower_bound(3) points to value " << *it
         << " at index " << (it - v.begin()) << "\n";

    auto it2 = upper_bound(v.begin(), v.end(), 3); // first element > 3
    cout << "upper_bound(3) points to value " << *it2
         << " at index " << (it2 - v.begin()) << "\n";

    // unique() removes CONSECUTIVE duplicates only — that's why we sort first
    v.erase(unique(v.begin(), v.end()), v.end());
    printVec(v, "after sort + unique + erase (deduplicated)");

    // find() does a linear O(n) scan — no sorting required
    vector<int> unsorted = {40, 10, 30, 20};
    auto found_it = find(unsorted.begin(), unsorted.end(), 30);
    if (found_it != unsorted.end())
        cout << "find(30) found it at index " << (found_it - unsorted.begin()) << "\n";

    int cnt = count(unsorted.begin(), unsorted.end(), 10);
    cout << "count(10) = " << cnt << "\n";
}

/* ------------------------------------------------------------
   10. PASSING VECTORS TO FUNCTIONS
   This matters a lot for performance — copying a large vector
   is expensive.
   ------------------------------------------------------------ */

// (a) By value: makes a full COPY of the vector. Safe (the original is
//     untouched) but wasteful for large vectors — avoid unless you
//     genuinely need an independent copy inside the function.
void byValue(vector<int> v) {
    v.push_back(-1); // only affects the local copy
}

// (b) By reference: no copy is made, and changes DO affect the caller's
//     vector. Use this when the function needs to modify the original.
void byReference(vector<int>& v) {
    v.push_back(-1); // affects the caller's actual vector
}

// (c) By const reference: no copy, and the compiler guarantees the
//     function can't modify it. This is the best default for functions
//     that only need to READ the vector (like our printVec at the top).
void byConstReference(const vector<int>& v) {
    cout << "byConstReference sees size=" << v.size() << " (read-only)\n";
    // v.push_back(1); // <-- this would be a COMPILE ERROR, which is the point
}

void demo_passing_to_functions() {
    cout << "\n===== 10. PASSING VECTORS TO FUNCTIONS =====\n";

    vector<int> original = {1, 2, 3};

    byValue(original);
    printVec(original, "after byValue() call (unchanged, as expected)");

    byReference(original);
    printVec(original, "after byReference() call (modified!)");

    byConstReference(original);
}

/* ------------------------------------------------------------
   11. QUICK-REFERENCE SUMMARY OF PITFALLS
   Printed at the end as a recap — not new code, just a reminder.
   ------------------------------------------------------------ */
void print_pitfall_summary() {
    cout << "\n===== 11. PITFALLS TO REMEMBER =====\n";
    cout << "- v[i] does NOT bounds-check; v.at(i) does (throws on bad index)\n";
    cout << "- size() is elements stored; capacity() is memory reserved\n";
    cout << "- Erasing/inserting mid-vector is O(n) and invalidates iterators\n";
    cout << "  at/after the change point -- don't keep using old iterators after that\n";
    cout << "- Never erase() inside a plain index loop without adjusting the index\n";
    cout << "  or using the erase-remove idiom instead\n";
    cout << "- unique() only removes CONSECUTIVE duplicates -- sort first\n";
    cout << "- binary_search/lower_bound/upper_bound require a SORTED range\n";
    cout << "- Passing by value copies the whole vector -- prefer const& when\n";
    cout << "  you're only reading, and & when you need to modify the original\n";
    cout << "- reserve(n) if you know the approximate final size before a loop\n";
    cout << "  of many push_back() calls -- avoids repeated reallocation\n";
}

/* ------------------------------------------------------------
   MAIN — runs every demo in a sensible learning order
   ------------------------------------------------------------ */
int main() {
    demo_declaration();
    demo_adding_elements();
    demo_accessing_elements();
    demo_size_vs_capacity();
    demo_iterating();
    demo_removing_elements();
    demo_2d_vector();
    demo_vector_of_pairs();
    demo_algorithms();
    demo_passing_to_functions();
    print_pitfall_summary();
    return 0;
}
