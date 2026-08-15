# Inception — 6-Day Intensive CP Prep Roadmap

**Goal:** Maximize contest performance in 6 days. Not learning DSA — sharpening what you already have: speed, pattern recognition, implementation, and strategy.

> **A note on the problem list:** every problem below was checked against Codeforces before being included, so the names/numbers are real. Ratings can drift by ~100-200 points over time as more people solve a problem, so if the rating tag on the CF page looks a bit different from what's listed here, don't stress — the *pattern* is why it's on the list, not the exact number.

---

## Part 1 — Priority Ranking (6 days, highest ROI first)

You cannot give equal time to 30 topics in 6 days. Here's the ranked list — study top to bottom, and treat "Tier 4" as **do not touch**.

### Tier 1 — Master these, they show up in almost every contest
1. **Implementation / simulation** — most points in any contest come from clean implementation, not clever algorithms
2. **Time complexity intuition** — instantly knowing "n ≤ 2×10^5 means O(n log n)" saves you from wrong approaches
3. **Greedy algorithms** — extremely common in Div2 B/C-level problems
4. **Sorting** (as a tool, not the algorithm itself)
5. **Binary search** (on array, and on the answer)
6. **Two pointers**
7. **Prefix sums**
8. **Math basics** — GCD/LCM, modular arithmetic, sieve of Eratosthenes

### Tier 2 — High value, moderate time investment
9. **Strings** (manipulation, not advanced string algorithms)
10. **Sliding window**
11. **Hashing / frequency maps**
12. **Sets and maps (STL fluency)**
13. **Basic DP** (1D recurrences, simple "take or skip")
14. **BFS / DFS**
15. **DSU (Union-Find)**

### Tier 3 — Useful, lower priority given your timeline
16. **Stack / Queue / Deque**
17. **Trees** (traversal only, not LCA/heavy-light etc.)
18. **Recursion** (as a tool for the above, not standalone study)
19. **Combinatorics** (nCr, factorials mod p — just the formula, not deep theory)
20. **Bit manipulation** (basic tricks only)

### Tier 4 — Skip entirely, or 15 minutes max
21. Backtracking — low frequency, expensive to "learn" in days
22. Shortest paths (Dijkstra) — only touch if Day 3 goes very smoothly
23. Linked lists — almost never appears in CP; skip
24. Basic geometry — skip unless you're already comfortable
25. Advanced number theory beyond GCD/sieve/modmath — skip

**Why this ranking:** an Inception-style college contest almost certainly leans on implementation, greedy, math, and basic data-structure fluency for the bulk of the points. Graphs/DP appear but usually as 1-2 problems, not the majority. Spend your limited hours where the point density is highest.

---

## Part 2 — The 6-Day Plan

### Day 1 — Core Patterns + Speed
**Time budget: ~6-7 hours**

**1. Topics to study**
Implementation/simulation patterns, fast I/O, basic math (parity, ceiling division), string manipulation basics, STL fluency (vector, string, map, sort).

**2. Concepts you must know**
- Reading input fast with `cin`/`cout` + `sync_with_stdio(false)`
- 0-indexed vs 1-indexed bugs
- Overflow: when to use `long long` instead of `int`
- `ceil(a/b)` for integers → `(a + b - 1) / b`

**3. Patterns/templates to memorize**
- Frequency counting with `map<char,int>` or `int freq[26]`
- Reading `n` then `n` values in a loop
- Basic string iteration and character checks (`isdigit`, `isalpha`, `tolower`)

**4. Problems to solve:** 7
**5. Difficulty range:** 800–1300
**6. Problem type:** pure implementation, math, and string manipulation

| Problem | Link | Rating | Pattern | Why | Mode |
|---|---|---|---|---|---|
| A. Watermelon | codeforces.com/problemset/problem/4/A | 800 | Math/parity | Fastest possible warm-up, builds confidence | Solve independently, <5 min |
| A. Way Too Long Words | codeforces.com/problemset/problem/71/A | 800 | String manipulation | Classic string-abbreviation pattern | Solve independently |
| A. Team | codeforces.com/problemset/problem/231/A | 800 | Implementation/counting | Simple counting loop, very fast | Solve independently |
| A. Theatre Square | codeforces.com/problemset/problem/1/A | 1000 | Math (ceiling division) | Teaches the ceil-division trick you'll reuse constantly | Solve independently |
| A. String Task | codeforces.com/problemset/problem/118/A | 1000 | String manipulation | Character filtering/transformation pattern | Solve independently |
| A. Soldier and Bananas | codeforces.com/problemset/problem/546/A | 800 | Math/simulation | Arithmetic series simulation | Solve independently |
| C. Registration System | codeforces.com/problemset/problem/4/C | ~1300 | Hashing with `map<string,int>` | Core "seen before?" pattern used everywhere | Give 20 min, then check editorial if stuck |

**7. Timed practice session:** 45 minutes — solve the first 4 problems back to back with a stopwatch. Target: under 5 minutes each. This is about building typing/reading speed, not difficulty.

**8. Mistakes to watch for**
- Forgetting `long long` on sums that can exceed 2×10^9
- Off-by-one in loops (`i <= n` vs `i < n`)
- Not reading the full problem statement (missing an edge case like "at least 1")

**9. What NOT to study today:** graphs, DP, anything requiring more than an array/string/map. Don't touch advanced STL (priority_queue, set) yet.

---

### Day 2 — Binary Search, Two Pointers, Prefix Sums, Greedy
**Time budget: ~6-7 hours**

**1. Topics to study**
Binary search on sorted arrays and "binary search on the answer," two pointers on sorted/unsorted arrays, prefix sum arrays, greedy exchange-argument thinking.

**2. Concepts you must know**
- `lower_bound` / `upper_bound` and what they return
- Binary search on the answer: when the answer space is monotonic ("if x works, does x+1 also work?")
- Prefix sum: `pre[i] = pre[i-1] + a[i]`, range sum = `pre[r] - pre[l-1]`
- Two pointers: when the array is sorted or when a window is monotonic

**3. Patterns/templates to memorize**
```cpp
// binary search on the answer
int lo = 1, hi = MAXN;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (check(mid)) hi = mid; else lo = mid + 1;
}
```
```cpp
// two pointers (shrinking window)
int l = 0; long long sum = 0;
for (int r = 0; r < n; r++) {
    sum += a[r];
    while (sum > limit) { sum -= a[l]; l++; }
    // window [l, r] is valid
}
```

**4. Problems to solve:** 5
**5. Difficulty range:** 1000–1300
**6. Problem type:** binary search, two pointers, greedy construction

| Problem | Link | Rating | Pattern | Why | Mode |
|---|---|---|---|---|---|
| B. Before an Exam | codeforces.com/problemset/problem/4/B | ~1200 | Greedy construction | Classic "assign extremes first" greedy pattern | Solve independently, 20 min cap |
| C. Less or Equal | codeforces.com/problemset/problem/977/C | ~1200 | Sort + boundary reasoning | Teaches thinking in terms of sorted order/threshold | Solve independently |
| C. K-th Not Divisible by n | codeforces.com/problemset/problem/1352/C | ~1200 | Binary search on the answer / direct formula | Very reusable "search for the k-th value" pattern | Solve independently |
| B. Books | codeforces.com/problemset/problem/279/B | ~1200 | Two pointers + prefix sum | Textbook "max window under a budget" problem | Solve independently |
| B. Taxi | codeforces.com/problemset/problem/158/B | ~1300 | Greedy grouping | Iconic greedy-pairing problem, shows up in many forms | Give 20 min, then editorial if stuck |

**7. Timed practice session:** 60 minutes, 3 problems, no editorial until time is up. Simulates real contest pressure on exactly the topics you'll need most.

**8. Mistakes to watch for**
- Binary search infinite loops (mid calculation, boundary updates)
- Two pointers moving the wrong pointer or not shrinking the window correctly
- Greedy without proving it — if you can't explain *why* the greedy choice is safe in one sentence, don't trust it blindly; test on the sample

**9. What NOT to study today:** graphs, DP, bit manipulation, geometry.

---

### Day 3 — Graphs + Trees
**Time budget: ~5-6 hours (lighter day — this tier is lower priority for you)**

**1. Topics to study**
BFS/DFS traversal, basic tree traversal, DSU basics. Keep this practical — you're learning "can I write BFS/DFS from memory in under 3 minutes," not graph theory.

**2. Concepts you must know**
- Adjacency list representation: `vector<int> adj[N]`
- BFS with a queue for shortest unweighted distance / level counting
- DFS with recursion or an explicit stack
- DSU: `find` with path compression, `union` by size/rank

**3. Patterns/templates to memorize**
```cpp
// BFS
vector<int> dist(n, -1);
queue<int> q;
dist[src] = 0; q.push(src);
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
    }
}
```
```cpp
// DSU
vector<int> parent, sz;
int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    parent[b] = a; sz[a] += sz[b];
}
```

**4. Problems to solve:** 4 (3 core + 1 optional stretch)
**5. Difficulty range:** 900–1600
**6. Problem type:** BFS/DFS on trees and grids, one DSU-flavored graph problem

| Problem | Link | Rating | Pattern | Why | Mode |
|---|---|---|---|---|---|
| A. Party | codeforces.com/problemset/problem/115/A | 900 | BFS/DFS on a tree | Teaches hierarchy depth counting — very common sub-task | Solve independently |
| A. New Year Transportation | codeforces.com/problemset/problem/500/A | 1000 | DFS reachability | Simple "can I reach node X" pattern | Solve independently |
| A. Ice Skating | codeforces.com/problemset/problem/217/A | 1200 | Connected components (DSU or DFS on a grid) | Bridges grid problems with union-find thinking | Give 20 min, then editorial if stuck |
| C. News Distribution | codeforces.com/problemset/problem/1167/C | ~1600 (stretch) | DSU on a bipartite-style structure | Optional bonus — only attempt if the first 3 felt easy | Give 15 min max, then read editorial or skip entirely |

**7. Timed practice session:** 40 minutes on the first two problems only — the goal is writing BFS/DFS from a blank file without hesitating, not solving something hard.

**8. Mistakes to watch for**
- Forgetting to mark nodes visited before pushing to the queue (causes duplicate processing/TLE)
- Stack overflow from deep recursion in DFS on large inputs — know when to convert to iterative DFS or BFS instead
- DSU without path compression on large `n` → TLE

**9. What NOT to study today:** shortest paths (Dijkstra/Bellman-Ford), LCA, advanced tree DP, MST. If graphs appear in the contest, they're very likely to be BFS/DFS/DSU level, not this heavier machinery — skip it.

---

### Day 4 — DP + Number Theory + Bit Manipulation
**Time budget: ~6 hours**

**1. Topics to study**
Basic 1D DP recurrences ("take or skip"), GCD/LCM, sieve of Eratosthenes, modular arithmetic, basic bitwise operations.

**2. Concepts you must know**
- `dp[i] = max(dp[i-1], dp[i-2] + value)` style recurrences
- `__gcd(a, b)` in C++, and `lcm = a / gcd(a,b) * b`
- Sieve of Eratosthenes for primes up to 10^6-10^7
- `%` (mod), and that `(a % MOD + MOD) % MOD` handles negative mods
- `x & 1` for parity, `x << k` / `x >> k`, `__builtin_popcount(x)`

**3. Patterns/templates to memorize**
```cpp
// simple 1D "take or skip" DP
vector<long long> dp(n + 1, 0);
for (int i = 1; i <= n; i++)
    dp[i] = max(dp[i-1], dp[i-1] + a[i]); // adapt per problem
```
```cpp
// sieve
vector<bool> is_prime(N, true);
is_prime[0] = is_prime[1] = false;
for (int i = 2; i * i < N; i++)
    if (is_prime[i])
        for (int j = i * i; j < N; j += i)
            is_prime[j] = false;
```
```cpp
// binary exponentiation (modular)
long long power(long long a, long long b, long long mod) {
    long long res = 1; a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
```

**4. Problems to solve:** 4 named + light tag-browsing
**5. Difficulty range:** 800–1400
**6. Problem type:** basic DP, number theory, and a short bit-manipulation drill

| Problem | Link | Rating | Pattern | Why | Mode |
|---|---|---|---|---|---|
| A. Maximum GCD | codeforces.com/problemset/problem/1370/A | 800 | Number theory (GCD reasoning, no brute force needed) | Fast pattern-recognition math problem | Solve independently |
| A. Boredom | codeforces.com/problemset/problem/455/A | ~1400 | 1D DP (take-or-skip on frequency array) | THE classic intro DP problem — appears in nearly every roadmap for a reason | Give 25 min, then study editorial closely if stuck — understanding this recurrence is worth more than solving 3 easier DP problems |

For number theory and bit manipulation beyond this, don't hunt for specific problems — instead:
- Browse `codeforces.com/problemset?tags=number+theory` filtered to 800–1200 and solve 2 more for reps
- Browse `codeforces.com/problemset?tags=bitmasks` filtered to 800–1100 and solve 1-2 to get comfortable with the templates above

**7. Timed practice session:** 30 minutes on Maximum GCD + one number-theory tag problem, back to back, no lookups.

**8. Mistakes to watch for**
- DP base cases (`dp[0]`, `dp[1]`) — most DP bugs live here
- Forgetting `%MOD` on every addition/multiplication in modular problems, not just the final answer
- Sieve array size off-by-one (need `N+1` if checking up to `N`)

**9. What NOT to study today:** 2D DP, digit DP, DP on trees/graphs, combinatorics beyond a basic nCr formula, deep number theory (Euler's totient, extended GCD) — high effort, low probability of appearing in a 6-day-prep contest.

---

### Day 5 — Mixed Problem Solving + Full Mock Contest #1
**Time budget: ~5-6 hours**

**1. Topics to study:** none new — this is pure integration and simulation.

**2. Concepts you must know:** everything from Days 1-4, ready to recall instantly.

**3. Patterns/templates to memorize:** none new — instead, re-type your competitive programming template (Part 5 below) from memory 2-3 times until it's automatic.

**4. Problems to solve:** the mock contest below (aim for all, realistically 3-4)
**5. Difficulty range:** 800–1500 (mixed, increasing)
**6. Problem type:** mixed — this is a simulation, not topic practice

**Mock Contest #1 — details**
- **Format:** don't hand-pick problems for this — instead use Codeforces's **Virtual Participation** feature (open any past contest page → "Virtual participation" button). This gives you a real, correctly-calibrated difficulty curve and genuine time pressure, which hand-picked problems can't replicate.
- **Which round to pick:** search "Codeforces Div 3" or "Codeforces Div 4" contests list and pick one you haven't seen. These rounds are specifically calibrated for exactly your situation (5-6 problems, increasing difficulty, implementation/greedy/math-heavy).
- **Duration:** 2 hours (standard Div 3/4 length)
- **Number of problems:** 5-6
- **Difficulty progression:** ~800 → ~1600 across the problem set

**7. How to behave during the mock**
- Read all problem titles/statements in the first 10 minutes before committing to one
- Solve in order unless a problem clearly looks harder than its position suggests
- No searching for hints, no pausing the clock, no external help — treat it exactly like Inception

**8. When to give up on a problem:** if you're stuck for 20+ minutes with no new idea, move to the next problem and come back only if time remains.

**9. How to analyze results afterward** (spend 45-60 minutes on this — it matters more than the mock itself)
- For every problem you didn't solve: read the editorial, understand *why* your idea was wrong or incomplete
- For every problem you solved slowly: note what wasted time (misreading the problem? bad implementation choice? a bug that took 10 min to find?)
- Write down 3 concrete takeaways to apply on Day 6 and in the real contest

---

### Day 6 — Revision + Mock Contest #2 + Final Contest Strategy
**Time budget: ~5-6 hours, lighter and calmer than other days**

**1. Topics to study:** whatever came up as your weakest area from Day 5's mock — 30-45 minutes max, don't start anything new.

**2. Concepts you must know:** all templates below should be typeable from memory without hesitation.

**3. Patterns/templates to memorize:** final pass over your CP template + all code snippets in this document.

**4. Problems to solve:** Mock Contest #2 (below)
**5. Difficulty range:** same as Day 5's mock, ideally a notch easier if Day 5 felt rough, or the same level if it felt manageable
**6. Problem type:** mixed simulation again

**Mock Contest #2 — details**
- Same method: Virtual Participation on another Div 3/Div 4 round you haven't done
- **Duration:** 2 hours
- **Number of problems:** 5-6, increasing difficulty
- **How to behave:** identical rules to Mock #1 — but this time, actively apply the 3 takeaways you wrote down yesterday
- **When to give up on a problem:** same 20-minute rule
- **Analyze afterward:** shorter this time (20-30 min) — you're checking "did I fix yesterday's mistakes," not doing a full post-mortem

**7. Rest of the day:** review your mistake log from both mocks, skim your template one more time, and stop studying at least 3 hours before you'd normally sleep. Cramming new material the night before a contest has negative ROI — a rested brain solves more problems than a tired one that saw one more topic.

**8. Mistakes to watch for:** the same categories that hit you in Mock #1 — this is a check, not new discovery.

**9. What NOT to study today:** anything new. Today is entirely about consolidation and calm.

---

## Part 3 — Contest Day Strategy

**First 10-15 minutes**
- Read every problem's title and skim the statement/constraints, don't start coding yet
- Rank problems mentally by how confident you feel, not strictly by letter order — contest problems aren't always sorted perfectly by difficulty for you personally
- Start with the problem you're most certain you can solve fast, usually A

**Which problem to attempt first:** the one where you can picture the full solution (algorithm + rough code) in your head within 60 seconds of reading it. Confidence beats "official" difficulty order.

**How long to stay stuck:** 15-20 minutes without a new idea → switch. Coming back later with fresh eyes after solving something else is extremely common and effective.

**When to switch problems:** the moment you notice you're re-reading the same paragraph of your own broken code without new insight, or re-reading the statement for the 4th time without a new idea.

**How to identify easy problems quickly:** short problem statement, small constraints (n ≤ 1000 or n ≤ 10^5 with no algorithm buzzwords), or a statement that reduces to "simulate this."

**Handling implementation-heavy problems:**
- Break the problem into sub-steps on paper/scratch area before typing
- Write helper functions for repeated logic instead of copy-pasting
- Test each sub-step against the sample as you go, not just at the end

**Idea but can't implement it:**
- Simplify: solve a smaller/special case first (n=1, n=2) to validate your idea
- Write pseudocode in comments before real code
- If truly stuck implementing, move on — a correct idea you can't ship yet is worth less than points from an easier unsolved problem

**How to debug quickly**
- Test the given sample(s) first, always
- Print intermediate variables rather than staring at logic
- Check the usual suspects first: off-by-one, `int` overflow, uninitialized variables, array bounds

**Avoiding silly WA/TLE/RE**
- WA: re-read constraints for edge cases (n=1, all same values, empty input where allowed)
- TLE: check your complexity against n before submitting, not after
- RE: array bounds, division by zero, `.back()`/`.top()` on empty containers

**Last 30 minutes**
- Stop attempting new hard problems unless you have a near-complete idea already
- Focus on submitting anything partially working, and squeezing in an easier unsolved problem if one remains
- Re-check submitted solutions for silly edge cases you may have missed under time pressure

**Maximizing score if you can't solve everything:** prioritize solving more problems over perfecting one. In most CF-style scoring, 3 solved cleanly beats 2 solved + 1 half-finished. Don't sink 40 minutes into problem D while an easier problem C sits unread.

---

## Part 4 — C++ Essentials Checklist

- [ ] **STL containers:** `vector`, `pair`, `map`/`unordered_map`, `set`/`unordered_set`, `stack`, `queue`, `deque`, `priority_queue`
- [ ] **Sorting:** `sort(v.begin(), v.end())`, custom comparator (lambda or function), sorting pairs
- [ ] **`lower_bound` / `upper_bound`:** on sorted vectors, and on `set`/`map` (member function version)
- [ ] **Binary search:** both manual (`while(lo<hi)`) and STL-based
- [ ] **`set` / `multiset`:** insert, erase, find, ordered iteration
- [ ] **`map` / `unordered_map`:** insert/access, `count()` vs `[]` access pitfalls
- [ ] **`priority_queue`:** default max-heap, min-heap via `greater<int>` or negation
- [ ] **`stack` / `queue` / `deque`:** push/pop/front/back operations
- [ ] **`pair` / `tuple`:** `.first`/`.second`, `make_pair`, structured access
- [ ] **Custom comparators:** for `sort`, and for `priority_queue`
- [ ] **Lambda functions:** `[](int a, int b){ return a < b; }` syntax for comparators
- [ ] **`__gcd(a, b)`** and manual `lcm`
- [ ] **Useful string ops:** `substr`, `find`, `to_string`, `stoi`/`stoll`, `reverse`
- [ ] **Bit operations:** `&`, `|`, `^`, `<<`, `>>`, `__builtin_popcount`, `__builtin_ctz`
- [ ] **Fast I/O:** `ios_base::sync_with_stdio(false); cin.tie(NULL);`
- [ ] **Debugging techniques:** print statements with labels, `assert()` for invariants, testing on samples first, checking array bounds manually when RE happens

### Minimal competitive programming template

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define all(x) (x).begin(), (x).end()

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    // solution logic here

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t; // comment out if single test case per file
    while (t--) {
        solve();
    }
    return 0;
}
```
Practice typing this from memory every day this week until it's automatic — you should never spend contest time thinking about boilerplate.

---

## Part 5 — 6-Day Master Checklist

- [ ] **Day 1:** Implementation/string/math warm-up — 7 problems solved, template typed from memory 3x
- [ ] **Day 2:** Binary search / two pointers / prefix sums / greedy — 5 problems solved, 60-min timed session done
- [ ] **Day 3:** BFS/DFS/DSU — 3 core problems solved (+ optional stretch), BFS and DSU templates typed from memory
- [ ] **Day 4:** DP / number theory / bit manipulation — Maximum GCD + Boredom solved and understood, sieve + modpow templates memorized
- [ ] **Day 5:** Mock Contest #1 completed (2 hrs), full post-mortem with 3 written takeaways
- [ ] **Day 6:** Weak-area touch-up (≤45 min), Mock Contest #2 completed (2 hrs), light review only after

---

## Part 6 — Final 2-Hour Pre-Contest Routine (Day of Inception)

| Time before contest | What to do |
|---|---|
| 2h 00m | Light breakfast/meal — nothing heavy that makes you sluggish. Hydrate. |
| 1h 45m | Skim your template and STL checklist one final time — don't solve anything new |
| 1h 30m | Type your template from scratch once, untimed, just to warm up your hands |
| 1h 15m | Solve ONE very easy problem (800 rating) end-to-end, just to get into "contest mode" |
| 1h 00m | Stop looking at code. Short walk or stretch — let your brain settle |
| 0h 45m | Re-read your mistake log from the two mocks — reinforce what to avoid |
| 0h 30m | Set up your environment: editor open, compiler ready, CF tab open, quiet space, phone on silent |
| 0h 15m | Do nothing algorithmic. Breathe. Confirm login works on the contest platform. |
| 0h 05m | Mentally commit to your opening strategy: read all problems first, start with your most confident one, 15-20 min stuck-limit per problem |
| 0h 00m | Contest starts — read every problem statement before writing a single line of code |

Good luck with Inception.
