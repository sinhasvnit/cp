# Greedy Algorithms for Competitive Programming

A practical guide focused on **thinking**, not just theory. The goal here is not to memorize definitions — it's to build the instinct to recognize a greedy problem, find the right greedy choice, prove it's correct (or catch yourself before you submit a wrong solution), and implement it cleanly under contest pressure.

---

## Table of Contents

1. [What is a Greedy Algorithm?](#1-what-is-a-greedy-algorithm)
2. [How Do I Know This Problem Might Be Greedy?](#2-how-do-i-know-this-problem-might-be-greedy)
3. [Greedy Thinking Process](#3-greedy-thinking-process)
4. [The Greedy Choice](#4-the-greedy-choice)
5. [Proving Greedy Correctness](#5-proving-greedy-correctness)
6. [How to Disprove a Greedy Idea](#6-how-to-disprove-a-greedy-idea)
7. [Greedy vs Dynamic Programming](#7-greedy-vs-dynamic-programming)
8. [Greedy vs Brute Force](#8-greedy-vs-brute-force)
9. [Sorting + Greedy](#9-sorting--greedy)
10. [Important Greedy Patterns](#10-important-greedy-patterns)
11. [Classic Greedy Problems](#11-classic-greedy-problems)
12. [Problems Where Greedy Looks Correct but Fails](#12-problems-where-greedy-looks-correct-but-fails)
13. [Choosing the Sorting Comparator](#13-choosing-the-sorting-comparator)
14. [Greedy + STL](#14-greedy--stl)
15. [Priority Queue Greedy](#15-priority-queue-greedy)
16. [Interval Greedy](#16-interval-greedy)
17. [Mathematical Greedy](#17-mathematical-greedy)
18. [Greedy with Strings](#18-greedy-with-strings)
19. [Greedy with Arrays](#19-greedy-with-arrays)
20. [Greedy with Graphs](#20-greedy-with-graphs)
21. [Greedy Decision Checklist](#21-greedy-decision-checklist)
22. [Greedy Debugging Checklist](#22-greedy-debugging-checklist)
23. [Complexity](#23-complexity)
24. [Competitive Programming Workflow](#24-competitive-programming-workflow)
25. [How to Practice Greedy](#25-how-to-practice-greedy)
26. [Problem Analysis Template](#26-problem-analysis-template)
27. [Final Cheat Sheet](#27-final-cheat-sheet)

---

## 1. What is a Greedy Algorithm?

A **greedy algorithm** builds a solution step by step. At every step it makes the choice that looks best **right now**, and it never goes back to change that choice later.

- **Local choice**: the decision you make at one step, based only on the current state, without knowing the full future.
- **Globally optimal**: the best possible answer over the whole problem, considering everything.

A greedy algorithm is a bet: *"If I always make the best local choice, I will end up with the best global answer."* Sometimes this bet is correct. Sometimes it isn't. The entire skill of greedy problem solving is learning when this bet is safe.

**Small example.** You want to give change using the fewest coins, with coins `{1, 5, 10, 25}`, target `41`.
Greedy: take the largest coin that fits, repeat.
`25 → 16 left`, `10 → 6 left`, `5 → 1 left`, `1 → 0 left`. Result: `25+10+5+1 = 4 coins`. This is optimal here, and it feels natural — take as much as you can right now.

Now change the coin set to `{1, 3, 4}`, target `6`.
Greedy: `4 → 2 left`, then `1+1 → 0 left`. Result: `4+1+1 = 3 coins`.
But the actual best answer is `3+3 = 2 coins`. Greedy picked the biggest coin first and it hurt the outcome. This tiny example already shows the danger: **greedy can look correct and still be wrong.**

### Greedy vs Brute Force
Brute force tries every possibility (or a large structured subset of them) and picks the best. It's always correct if implemented right, but usually too slow. Greedy skips this search entirely and commits to one choice per step — fast, but only correct if that choice is provably safe.

### Greedy vs Dynamic Programming
DP also builds a solution step by step, but instead of committing to one choice, it keeps track of **many possible states** and their best values, because the best decision now might depend on decisions made later. Greedy assumes you don't need to keep multiple possibilities open — one commitment per step is enough. When that assumption is false, you need DP.

### Greedy vs Divide and Conquer
Divide and conquer splits a problem into independent subproblems, solves each one, and combines the results (e.g., merge sort). Greedy doesn't split the problem — it processes elements or decisions in some order and commits one at a time.

### Why greedy is usually fast
Because there's no branching, no backtracking, and no need to store multiple states. Most greedy algorithms are `O(n log n)` (dominated by sorting) or `O(n)`. Compare that to brute force, which is often exponential, or DP, which is often `O(n²)` or worse.

### Why greedy is dangerous without justification
Because "looks locally best" is a feeling, not a proof. Many wrong solutions in contests come from a greedy idea that passed the first two examples the author tried by hand and then failed on hidden tests. The fix is always the same: **actively try to break your own idea before you trust it.**

---
## 2. How Do I Know This Problem Might Be Greedy?

Use this checklist while reading a problem. None of these **prove** greedy works — they only tell you it's worth trying.

**Signals that suggest greedy:**
- The problem asks for a maximum or minimum value (max profit, min cost, min operations, max count).
- You're choosing a subset, ordering, or assignment of items.
- The problem involves scheduling, deadlines, or intervals.
- The problem involves resource allocation (limited capacity, limited time, limited budget).
- The phrase "minimum number of X" or "maximum number of Y" appears.
- Sorting the input in some way seems to reveal a useful structure.
- At each step, there's a natural candidate for "best current option."
- Once you make a choice, it feels like it can't be undone (you consume an item, close an interval, spend a resource).
- An earlier decision seems to simplify or restrict later decisions in a predictable way.

**These clues do NOT prove that greedy works.** They only mean the problem *might* have a greedy structure. A huge number of problems trigger these signals (deadlines, intervals, "minimum number of...") and still require DP, because a later decision can depend on more than what a single greedy pass can track. Treat every clue as an invitation to **test the idea**, never as a guarantee.

**How to test the idea before trusting it:**
1. State your greedy rule in one sentence ("always take the item with X").
2. Run it by hand on 2–3 small examples, including edge cases.
3. Try to actively construct a case where the rule fails (see Section 6).
4. If it survives your attempts to break it, look for a real proof (see Section 5), not just "it worked on my examples."

---

## 3. Greedy Thinking Process

A repeatable process to run during a contest.

1. **Understand exactly what is being optimized.** Write it as one sentence: "minimize total cost," "maximize number of items selected," etc. If you can't state it precisely, you don't understand the problem yet.
2. **Identify the decision that repeats.** What are you choosing, over and over, until the input is exhausted? (Which item to take next, which interval to keep, which task to schedule.)
3. **Ask what information matters for that decision.** Do you need the item's value? Its cost? Its deadline? Its ratio of value to cost? This narrows down what to sort or compare by.
4. **Guess the locally best choice.** Pick the rule that feels most natural (largest, smallest, earliest, cheapest, best ratio...). Write it down explicitly.
5. **Test the choice on small examples.** Do this by hand, on paper. Use 3–5 elements, not 20.
6. **Try to construct a counterexample.** Deliberately try to make your rule fail — see Section 6 for concrete techniques.
7. **If no counterexample appears, look for a proof.** Use exchange argument, staying ahead, or another technique from Section 5. If you can't find a full proof under time pressure, at least convince yourself with a semi-formal argument — but know that this is a risk.
8. **Determine how to implement the choice efficiently.** Does it need sorting? A heap? A two-pointer scan? A set for fast lookup?
9. **Analyze complexity.** Make sure it fits within the time limit for the given constraints.
10. **Test edge cases.** Empty input, one element, all equal values, already sorted, reverse sorted, duplicates, extreme values (very large/very small), ties.

This process is meant to be fast in a contest — most of the time steps 4–6 take under two minutes for easier problems. The discipline of *always* trying to break your own idea (step 6) before submitting is what separates strong greedy solvers from people who guess and hope.

---

## 4. The Greedy Choice

There is **no universal rule** for what the "right" greedy choice is. It depends entirely on the structure of the problem. Below are the common candidate choices and when each tends to work.

| Choice | Works well when... | Example |
|---|---|---|
| Choose the **largest** first | Big items are "safer" to place early, or greedily grabbing value now never blocks a better future option | Coin systems with well-behaved denominations (e.g., standard currency) |
| Choose the **smallest** first | Small costs/items should be cleared out before they compound, or small items fit into more future slots | Assign Cookies, minimizing max value used |
| Choose the **earliest finishing/deadline** | You want to keep as many future options open as possible | Activity Selection, Job Sequencing |
| Choose the **latest** possible slot | You want to reserve early flexibility for other tasks | Job Sequencing with Deadlines (working backward) |
| Choose by **cost** (cheapest) | You're filling a budget and want to maximize count/coverage | Fractional Knapsack (by cost when capacity-bound) |
| Choose by **ratio** (value/cost) | Items are divisible or you're comparing efficiency, not raw value | Fractional Knapsack |
| Choose the item with the **largest immediate gain** | Gains don't interact — taking one doesn't reduce the benefit of others | Simple selection problems with independent items |

**Should I sort first?** Almost always ask this. Sorting is often what *creates* the greedy structure — before sorting, the "best next choice" is expensive to find; after sorting, it's just "the next element."

**Examples where different rules work:**
- *Largest works*: In coin change with denominations `{1, 5, 10, 25}`, always taking the largest coin that fits gives the optimal count.
- *Smallest works*: In "Assign Cookies" (children with greed factors, cookies with sizes), sorting both ascending and matching the smallest cookie that satisfies the smallest unsatisfied child maximizes satisfied children.
- *Earliest works*: In Activity Selection, always picking the activity that finishes earliest (among those compatible with what's chosen) maximizes the count of non-overlapping activities.
- *Latest works*: In Job Sequencing with Deadlines, processing jobs by descending profit and placing each job in the **latest** available slot before its deadline maximizes total profit.
- *Ratio works*: In Fractional Knapsack, sorting by value/weight ratio descending and taking as much as possible of each item (allowing fractions) maximizes total value.
- *Seemingly obvious rule fails*: In 0/1 Knapsack, sorting by ratio and greedily taking whole items **does not** guarantee the optimal value, because items can't be split and a high-ratio item might not fit while a combination of lower-ratio items would use the capacity better. This needs DP, not greedy — see Section 12.

---
## 5. Proving Greedy Correctness

"It worked on my examples" is not a proof. Here are four real techniques, in plain language.

### A. Exchange Argument

**Idea**: Take any optimal solution. Show that you can transform it — swapping one element for the greedy element — without making it worse. If you can always do this exchange, the greedy solution is at least as good as any optimal solution, so it IS optimal.

**Steps:**
1. Assume `OPT` is an optimal solution that differs from the greedy solution at the first point of difference.
2. Look at what `OPT` chose at that step versus what greedy chose.
3. Show that swapping `OPT`'s choice for greedy's choice doesn't decrease the quality of the solution (and doesn't break feasibility).
4. Repeat this exchange until `OPT` looks exactly like the greedy solution, with quality never decreasing.
5. Conclude: greedy's solution is at least as good as `OPT`, so greedy is optimal.

**Example — Activity Selection.** Claim: always picking the activity with the earliest finish time (among remaining compatible ones) is optimal.
Suppose an optimal solution `OPT` doesn't start with the earliest-finishing activity `a`. Let `b` be the first activity `OPT` picks instead. Since `a` finishes no later than `b`, we can replace `b` with `a` in `OPT` — everything that was compatible with `b` (starts after `b` ends) is still compatible with `a` (which ends even earlier or at the same time). The new solution has the same size, so it's still optimal, and now it starts with `a`, the greedy choice. Repeating this argument for every step proves greedy matches an optimal solution.

**When to use it**: whenever your greedy choice is "the extreme element by some measure" and you can argue that swapping it in for any other candidate doesn't hurt.
**Common mistake**: forgetting to check that the exchange keeps the solution *feasible* (not just "not worse"). You must verify constraints still hold after the swap.

### B. Staying Ahead

**Idea**: Show that after every step, the greedy solution is "at least as good so far" as any other valid solution, when compared step by step (e.g., partial sums, prefix counts).

**Steps:**
1. Define a measure that can be compared after each step (e.g., "after `k` steps, total value used" or "finish time of the `k`-th activity").
2. Prove by induction that greedy's measure after step `k` is always at least as good as any other solution's measure after `k` steps.
3. Conclude that since greedy never falls behind, it can't end up worse than any other solution.

**Example — Activity Selection (again, different lens).** Let greedy's `k`-th chosen activity finish at time `f_k`, and let any other valid solution's `k`-th activity finish at time `f'_k`. By induction, `f_k ≤ f'_k` for every `k`: greedy always finishes its `k`-th activity no later than any competitor could. This means greedy always has at least as much "room" left for future activities, so it can never be beaten in the final count.

**When to use it**: sequential problems where you're building up a solution step by step and can define a natural "progress" measure to compare.
**Common mistake**: picking a measure that doesn't actually stay comparable step by step (e.g., comparing unordered totals instead of a properly aligned sequence).

### C. Greedy Stays Optimal (Optimal Substructure)

**Idea**: Show that after making the greedy choice, the remaining problem — with the greedy choice removed — is itself a smaller instance of the same problem, and solving it optimally (recursively) combined with the greedy choice gives an overall optimal solution.

**Steps:**
1. Make the greedy choice for the first decision.
2. Argue that there exists *some* optimal solution that includes this greedy choice (often via an exchange argument).
3. Show that the rest of that optimal solution is an optimal solution to the remaining subproblem.
4. Conclude by induction that always making the greedy choice and recursing gives a global optimum.

**Example — Huffman Coding.** The two least frequent symbols can always be made siblings at the deepest level of *some* optimal prefix-code tree. Once merged into one combined node, the problem reduces to building an optimal tree for a smaller alphabet (the same problem, one symbol fewer). This is why Huffman coding repeatedly merges the two smallest-frequency nodes.

**When to use it**: when your problem naturally reduces to a smaller version of itself after the greedy step (this is also how you'd recognize it *could* be DP — the difference is that here, only one "smaller instance" needs to be considered, not many).
**Common mistake**: assuming optimal substructure exists without checking it — some problems reduce to a smaller instance but the greedy choice does NOT remain valid in a globally optimal solution (this is exactly how 0/1 Knapsack breaks).

### D. Contradiction

**Idea**: Assume the greedy choice is *not* part of some optimal solution, and derive a contradiction (usually by showing you could modify that optimal solution to be strictly better, which is impossible since it was optimal).

**Steps:**
1. Assume, for contradiction, that an optimal solution `OPT` does not include the greedy choice.
2. Construct a modified solution `OPT'` that does include the greedy choice.
3. Show `OPT'` is at least as good as `OPT` (feasible and not worse).
4. This contradicts nothing directly, but combined with "OPT was assumed optimal and didn't include the choice" it shows the greedy choice *could* have been included without loss — supporting that greedy is a safe move.

**When to use it**: often used together with exchange argument; it's really the same family of reasoning, framed differently. Useful when the "swap" step is more natural to argue as "assume it's not there, then show a contradiction to your assumption of strict optimality."
**Common mistake**: proving "not worse" but sloppily concluding "strictly better," or forgetting to check feasibility of the constructed solution.

---
## 6. How to DISPROVE a Greedy Idea

This is the single most useful contest skill for greedy problems: **actively trying to break your own idea before submitting.** Most wrong greedy submissions could have been caught in under a minute with this discipline.

**Techniques for finding counterexamples:**
- **Start with very small cases.** 2 or 3 elements are often enough to break a wrong rule.
- **Try cases where the greedy choice blocks a better future choice.** Ask: "If I take this now, what do I give up later?"
- **Try equal values.** Ties often expose sloppy assumptions about ordering.
- **Try extreme values.** One item much bigger/smaller than the rest, or one deadline far in the future/past.
- **Try duplicate values.** Repeated elements can break rules that secretly assumed distinctness.
- **Try the smallest possible input.** Zero elements, one element — does the rule even make sense?
- **Try the largest possible single item** relative to a limited resource (e.g., an item bigger than total capacity).
- **Deliberately construct a case where the locally best choice has a bad future consequence** — this is the core idea. Ask: "What input would punish this specific rule?"

**Format: Problem → Wrong Greedy Idea → Counterexample → Correct Idea**

**Example 1 — Coin Change with denominations `{1, 3, 4}`, target `6`.**
- Wrong idea: always take the largest coin that fits.
- Counterexample: greedy picks `4, 1, 1` = 3 coins; optimal is `3, 3` = 2 coins.
- Correct idea: this greedy rule only works for "canonical" coin systems. For arbitrary denominations, use DP (minimum coins per amount).

**Example 2 — Maximum sum by picking non-adjacent array elements.**
- Wrong idea: always take the current largest remaining element (ignoring adjacency).
- Counterexample: array `[5, 1, 1, 5]`. Greedy might take both `5`s if not careful about adjacency bookkeeping, or if forced to respect adjacency but still "grab largest first" pattern, it can miss the better combination compared to a proper DP scan.
- Correct idea: this is a classic DP problem (House Robber pattern) — the decision at each index depends on a choice made two steps back, which a single-pass "take the biggest" rule cannot track correctly.

**Example 3 — Job Sequencing: always do the shortest job first, ignoring deadlines.**
- Wrong idea: sort by job duration ascending and schedule in that order.
- Counterexample: Job A takes 1 unit, deadline 1, profit 5. Job B takes 1 unit, deadline 2, profit 100. Both take the same duration, so "shortest first" gives no clear order — but if the rule ties and picks A then B, or ignores deadlines entirely under time pressure, you can miss that A's deadline is tight and must be prioritized in scheduling order, not duration.
- Correct idea: sort by profit descending, and place each job as late as possible before its deadline (Section 11 has full detail).

**Example 4 — Assign the largest available resource to the largest request, always.**
- Wrong idea: sort both descending and match position by position naively without checking feasibility.
- Counterexample: requests `[10, 1]`, resources `[10, 2]`. Matching by position gives `10→10` (ok) and `1→2` (ok) — looks fine, but change resources to `[9, 2]`: naive descending match gives `10→9` which is **infeasible** if resource must be ≥ request. The correct approach requires checking feasibility, not just pairing by sorted position.
- Correct idea: often needs a two-pointer approach with an explicit feasibility check, not blind pairing.

The pattern to internalize: **every "obviously correct" greedy rule should survive an active attempt to break it** using small, equal, extreme, or duplicate inputs before you trust it.

---

## 7. Greedy vs Dynamic Programming

| | Greedy | DP |
|---|---|---|
| Decisions | Commits to one choice per step, never revisited | Considers multiple possible choices, keeps the best result for each state |
| When it works | The locally best choice is provably never worse in the long run | The best current decision can depend on future information you don't have yet |
| Speed | Usually `O(n log n)` or `O(n)` | Usually `O(n²)` or depends on state space size |
| Proof burden | Requires proving the greedy choice is safe | Requires proving state transitions cover all cases (usually more mechanical) |

**When greedy can make one irreversible decision**: when the value of each choice doesn't depend on which other choices you make elsewhere (independence), or when there's a proven exchange/optimal-substructure argument.

**When DP must consider multiple possibilities**: when the best choice **now** depends on trade-offs that only become clear later, and different early choices lead to genuinely different sets of future options that must be compared, not assumed away.

**How to recognize overlapping subproblems (a DP sign):** if solving the problem for a smaller instance requires trying multiple different "first choices" and remembering the best result of each, rather than one obvious first choice, you likely need DP.

**How to recognize future decisions affecting current choices:** ask "does the value of choosing item A now depend on what I choose later?" If yes (e.g., capacity constraints where combinations matter, like Knapsack), it's a DP flag.

**How to decide between Greedy and DP — a quick test:**
1. Propose the greedy rule.
2. Try to prove it (Section 5). If a clean proof exists, use greedy.
3. Try to break it (Section 6). If you find a counterexample, the problem likely needs DP (or a smarter greedy with more state).
4. If items interact through a shared limited resource where *combinations* matter (like weight capacity), lean DP.
5. If the problem is about **ordering/selecting independent items** where one choice doesn't structurally block a better combination elsewhere, lean greedy.

**Example — Greedy works: Activity Selection.** Choosing the earliest-finishing activity never removes a better combination, because any activity compatible with a later-finishing choice is also compatible with an earlier-finishing one. Proven via exchange argument.

**Example — Greedy fails, DP required: 0/1 Knapsack.** Because items can't be split, and capacity is shared, the best combination depends on interactions between item weights that a single sorting rule cannot capture. DP tracks the best value for every (item, remaining capacity) state.

---

## 8. Greedy vs Brute Force

Brute force isn't just a "fallback when greedy fails" — it's a **tool for discovering the correct greedy rule**, especially on unfamiliar problems.

**Workflow:**
```
Small brute force
  → generate examples
  → observe pattern
  → guess greedy rule
  → search for counterexample
  → prove
  → implement
```

1. **Write a brute force** for small `n` (try all permutations, all subsets, or full search). It doesn't need to be fast — it needs to be obviously correct.
2. **Generate many small random examples** and record the brute-force optimal answer alongside the input.
3. **Look at the optimal solutions and search for a pattern**: what property do the chosen elements share? What order do they tend to appear in?
4. **Guess a greedy rule** based on the pattern (e.g., "the answer always sorts by X ascending").
5. **Write a stress test**: generate random small inputs, run both brute force and your greedy guess, and compare outputs automatically.
6. **If they disagree, you have a counterexample** — inspect it, understand why greedy failed, and refine the rule (or conclude greedy doesn't apply).
7. **Once thousands of random tests pass, look for an actual proof** — passing tests is strong evidence, not a substitute for proof, but it's often enough confidence to submit under contest time pressure when a full proof isn't feasible in the time available.
8. **Implement the efficient version** once you trust the rule.

This workflow is one of the most valuable competitive programming techniques in general, not just for greedy — stress testing against brute force catches subtle bugs and wrong assumptions far faster than manual reasoning alone.

---
## 9. Sorting + Greedy

Sorting is the single most common enabler of a greedy strategy. Why? Because greedy needs to repeatedly ask "what's the best available option right now?" — and if the input is sorted by the right property, that question becomes "look at the next element," which is `O(1)` instead of an expensive search.

**Common sort choices:**

| Sort by | Ascending or Descending | Typical use case |
|---|---|---|
| Value | Descending | Take highest-value items first (e.g., Job Sequencing profit) |
| Cost | Ascending | Fill a budget with cheapest items first |
| End time | Ascending | Interval scheduling to maximize count (Activity Selection) |
| Start time | Ascending | Merging intervals, checking overlaps in order |
| Deadline | Ascending or used with descending profit | Scheduling with deadlines |
| Ratio (value/cost) | Descending | Fractional Knapsack |
| Custom (pair, tuple) | Depends | Multi-criteria problems needing tie-breaking |

**How to decide what to sort by**: ask what the greedy choice is (Section 4), and sort by exactly that property. If the greedy choice is "always take the earliest-finishing option," sort by finish time. If it's "always take the highest ratio," sort by ratio. The sort key and the greedy choice should be the same thing.

**Examples:**
- **Activity Selection**: sort by end time ascending → always pick the next compatible activity.
- **Fractional Knapsack**: sort by value/weight ratio descending → fill capacity with best ratio first.
- **Job Sequencing with Deadlines**: sort by profit descending → place each job as late as possible before its deadline.
- **Merge Intervals**: sort by start time ascending → scan once, merging overlapping ranges.
- **Minimum Platforms**: sort arrivals and departures separately → two-pointer scan to find max overlap.
- **Boats to Save People**: sort by weight ascending → two-pointer pairing of lightest and heaviest.

---

## 10. Important Greedy Patterns

### Pattern 1: Take the Smallest Possible Value
**Recognition**: you're trying to minimize a max value, satisfy the "cheapest" requirement first, or clear small obligations before they compound.
**Reasoning**: small items are often flexible — they fit into more slots later, so using them early rarely closes off good options.
**Proof idea**: exchange argument — swapping a larger item for a smaller one earlier never makes the tail worse, because the larger item still fits wherever the smaller one would have (assuming monotonic constraints).
**Example**: Assign Cookies — give the smallest sufficient cookie to the least greedy unsatisfied child.

### Pattern 2: Take the Largest Possible Value
**Recognition**: you're trying to maximize immediate gain and gains don't conflict with each other.
**Reasoning**: if there's no hidden cost to using a large item now, grabbing it early guarantees you don't miss out on it.
**Proof idea**: exchange argument in the other direction — delaying the largest item can only be equally good or worse.
**Example**: Standard coin systems, choosing the highest-value coin that still fits the remaining amount.

### Pattern 3: Earliest Finishing Time
**Recognition**: interval/activity scheduling where you want to maximize the count of chosen non-overlapping intervals.
**Reasoning**: an activity that finishes earlier leaves the most room for future activities — it can never be a worse choice than one that finishes later, because anything compatible with the later one is also compatible with the earlier one.
**Proof**: full exchange argument given in Section 5A.
**Implementation**: sort by end time, keep a `lastEnd` variable, greedily accept if `start >= lastEnd`.

### Pattern 4: Latest Possible Choice
**Recognition**: you want to preserve early flexibility, often combined with sorting by another property like profit or value.
**Reasoning**: placing a low-priority commitment as late as possible keeps earlier slots open for higher-priority items that arrive later in your processing order.
**Example**: Job Sequencing with Deadlines — after sorting jobs by profit descending, place each job in the latest available slot ≤ its deadline, so higher-profit jobs (processed first) get the freedom to grab the latest slot, and later jobs still have earlier slots available.

### Pattern 5: Sort and Process
**Recognition**: the general shape of most greedy problems — sort by the property that matches your greedy choice, then do a single linear pass applying the rule.
**Why it works**: sorting turns "find the best remaining option" into "look at the next element," which is what makes greedy fast.

### Pattern 6: Sort + Two Pointers
**Recognition**: pairing or matching problems (smallest with largest, or matching two sorted lists under a constraint).
**Explanation**: after sorting one or two arrays, use two pointers (one from each end, or one per array) to make matching decisions in `O(n)` after the sort.
**Example**: Boats to Save People — sort weights ascending, pair the lightest with the heaviest if they fit together, else send the heaviest alone.

### Pattern 7: Priority Queue + Greedy
**Recognition**: the "best available choice" changes dynamically as you process the input — you can't just sort once upfront because new candidates appear over time, or you repeatedly need the current min/max after removals.
**Explanation**: a heap (`priority_queue`) gives `O(log n)` access to the current best candidate as the set of candidates changes.
**Example**: scheduling with a min-heap of end times (Minimum Meeting Rooms), or repeatedly picking the two smallest items (Huffman Coding).

### Pattern 8: Greedy with Deadlines
**Recognition**: each item/job has a deadline and you're maximizing count or profit while respecting deadlines.
**Explanation**: usually combines sorting (by deadline or by profit) with either a "latest available slot" search or a min-heap tracking scheduled items so far.
**Example**: Job Sequencing with Deadlines; also "minimum number of missed deadlines" type problems using a max-heap to evict the least valuable already-scheduled job when a conflict appears.

### Pattern 9: Greedy by Ratio
**Recognition**: items can be compared by "benefit per unit of cost," and the problem allows either divisibility or independence between items.
**When it works**: Fractional Knapsack — items can be split, so taking the best ratio first and filling remaining capacity fractionally is always optimal.
**When it fails**: 0/1 Knapsack — items can't be split, so a high-ratio item that doesn't fit can block a better combination. Ratio sorting alone doesn't account for combinatorial fit.

### Pattern 10: Minimize Loss / Maximize Gain
**Recognition**: the problem can be reframed as "minimize what you give up" instead of "maximize what you keep," or vice versa. Sometimes one framing makes the greedy choice obvious while the other doesn't.
**Example**: instead of "maximize non-overlapping intervals kept," think "minimize intervals removed" (Non-overlapping Intervals problem) — same answer, but the removal framing makes the greedy rule (keep earliest-finishing, remove the rest of the overlaps) more intuitive.

### Pattern 11: Cover as Much as Possible
**Recognition**: interval or range coverage problems — you want to cover a full range using the fewest intervals, or find the minimum number of "darts" (points) to hit all intervals.
**Explanation**: sort by end point, and greedily place your "coverage" as late as possible while still satisfying the current requirement, which maximizes how much future range it also covers.
**Example**: Minimum Number of Arrows to Burst Balloons — sort by end coordinate, shoot an arrow at the end of the first unburst balloon, which bursts every overlapping balloon.

### Pattern 12: Maintain the Best Candidate
**Recognition**: single-pass problems where you track a running minimum/maximum (or running best index) while scanning.
**Example**: Gas Station — track the running fuel tank total and the starting index; if the tank goes negative, the start must be after the current position.

### Pattern 13: Greedy with Swapping
**Recognition**: you can locally swap two adjacent elements to check if the order improves the result, and repeating this leads to a globally optimal order.
**Explanation**: this is really a disguised form of the exchange argument — the "proof" is that any two adjacent out-of-order elements can be swapped without making things worse, so the whole array sorts into an optimal order.
**Example**: arranging numbers to form the largest possible concatenated number — compare pairs `(a, b)` by whether `a+b > b+a` as strings.

### Pattern 14: Constructive Greedy
**Recognition**: the problem asks you to *build* a valid object (a string, a sequence, an arrangement) step by step, choosing the best valid next piece at each step.
**Explanation**: at each position, try the greedy candidate (e.g., smallest available character); if it keeps the rest of the construction feasible, commit; otherwise backtrack to the next candidate.
**Example**: building the lexicographically smallest string after removing `k` characters, using a monotonic stack.

---
## 11. Classic Greedy Problems

For each problem: idea, why it looks greedy, wrong approaches, the correct greedy observation and choice, why it works, proof idea, algorithm, C++ code, complexity, edge cases, and the pattern to remember.

### Activity Selection

**Problem**: given activities with start and end times, select the maximum number of non-overlapping activities.
**Looks greedy because**: it's a "maximum count" selection problem with intervals.
**Wrong approach**: pick the shortest activities first (duration-based) — a short activity can still block two longer, non-overlapping ones elsewhere.
**Greedy observation**: the finish time determines how much room is left for future picks.
**Greedy choice**: always pick the remaining activity with the earliest finish time that starts after the last chosen activity ends.
**Why it works / proof idea**: exchange argument (Section 5A) — an earlier finish time is never worse for future compatibility.
**Algorithm**: sort by end time; iterate; keep `lastEnd`; accept if `start >= lastEnd`.
```cpp
int activitySelection(vector<pair<int,int>>& activities) {
    sort(activities.begin(), activities.end(),
         [](auto &a, auto &b){ return a.second < b.second; }); // sort by end time
    int count = 0, lastEnd = INT_MIN;
    for (auto &[start, end] : activities) {
        if (start >= lastEnd) {   // compatible with last chosen activity
            count++;
            lastEnd = end;
        }
    }
    return count;
}
```
**Complexity**: `O(n log n)` for sorting, `O(n)` for the scan.
**Space**: `O(1)` extra (in-place sort).
**Edge cases**: activities with equal start/end (zero-length), overlapping boundaries (does `end == next start` count as compatible? confirm with problem statement), duplicate intervals.
**Pattern to remember**: Pattern 3 (earliest finishing time).

### Fractional Knapsack

**Problem**: given items with weight and value, and a knapsack capacity, maximize total value; items can be split into fractions.
**Looks greedy because**: "maximize value under capacity" with independent items.
**Wrong approach**: sort by value descending only — a heavy high-value item can waste capacity that many small high-ratio items would use better.
**Greedy observation**: since items are divisible, filling with the best "value per unit weight" first always uses capacity most efficiently.
**Greedy choice**: sort by value/weight ratio descending; take full items until capacity runs out, then take a fraction of the next item.
**Why it works**: any unit of capacity is best spent on the highest available ratio; divisibility removes the combinatorial fitting problem that makes 0/1 Knapsack hard.
**Proof idea**: exchange argument — swapping a unit of a lower-ratio item for a unit of a higher-ratio item (when available) never decreases value.
```cpp
double fractionalKnapsack(vector<pair<int,int>>& items, int capacity) { // {weight, value}
    sort(items.begin(), items.end(), [](auto &a, auto &b){
        return (double)a.second / a.first > (double)b.second / b.first; // ratio descending
    });
    double totalValue = 0;
    for (auto &[weight, value] : items) {
        if (capacity <= 0) break;
        if (weight <= capacity) {
            capacity -= weight;
            totalValue += value;
        } else {
            totalValue += value * ((double)capacity / weight); // take a fraction
            capacity = 0;
        }
    }
    return totalValue;
}
```
**Complexity**: `O(n log n)`. **Space**: `O(1)` extra.
**Edge cases**: capacity `0`, item weight `0` (avoid division issues), all items with the same ratio.
**Pattern to remember**: Pattern 9 (greedy by ratio) — works because items are divisible.

### Job Sequencing with Deadlines

**Problem**: each job has a deadline and profit, each job takes one unit of time, only one job runs per time unit; maximize total profit.
**Looks greedy because**: "maximize profit" with scheduling and deadlines.
**Wrong approach**: schedule jobs by earliest deadline only — this ignores profit and can leave high-profit jobs unscheduled.
**Greedy observation**: higher-profit jobs should get priority for slot selection; among available slots, the latest one before the deadline should be reserved so earlier slots stay open for other jobs.
**Greedy choice**: sort jobs by profit descending; for each job, place it in the latest free slot ≤ its deadline (using a disjoint-set or simple backward scan).
**Why it works**: this greedily protects the most profitable jobs first while preserving maximum flexibility for the rest.
**Proof idea**: exchange argument — if a lower-profit job occupies a slot that a higher-profit job could have used, swapping increases (or keeps equal) total profit.
```cpp
int jobSequencing(vector<array<int,3>>& jobs) { // {deadline, profit, id} -- profit stored to sort
    sort(jobs.begin(), jobs.end(), [](auto &a, auto &b){
        return a[1] > b[1]; // profit descending
    });
    int maxDeadline = 0;
    for (auto &job : jobs) maxDeadline = max(maxDeadline, job[0]);
    vector<int> slot(maxDeadline + 1, -1); // slot[d] = job index using day d (1-indexed)
    int totalProfit = 0;
    for (auto &job : jobs) {
        for (int d = job[0]; d >= 1; d--) { // search latest free slot up to deadline
            if (slot[d] == -1) {
                slot[d] = 1;
                totalProfit += job[1];
                break;
            }
        }
    }
    return totalProfit;
}
```
**Complexity**: `O(n log n + n * maxDeadline)` naive, improvable to `O(n log n + n log n)` with a DSU "find latest free slot" trick.
**Space**: `O(maxDeadline)`.
**Edge cases**: multiple jobs with the same deadline, deadline `0` or invalid, no jobs, deadline larger than job count.
**Pattern to remember**: Pattern 4 (latest possible choice) + Pattern 8 (deadlines).

### Huffman Coding

**Problem**: build a prefix-free binary code minimizing expected code length, given symbol frequencies.
**Looks greedy because**: "minimize total encoded length" with a combinatorial structure.
**Wrong approach**: assign shorter codes arbitrarily by symbol order, ignoring frequency.
**Greedy observation**: the two least frequent symbols should be as deep as possible in the tree (get the longest codes) since they contribute least to total cost.
**Greedy choice**: repeatedly merge the two nodes with smallest frequency into a new node (sum of frequencies), until one tree remains.
**Why it works / proof idea**: optimal substructure (Section 5C) — merging the two smallest reduces to a smaller instance of the same problem.
```cpp
long long huffmanCost(vector<long long> freq) {
    priority_queue<long long, vector<long long>, greater<long long>> pq(freq.begin(), freq.end());
    long long totalCost = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        totalCost += a + b;   // cost of merging = sum of the two frequencies
        pq.push(a + b);
    }
    return totalCost;
}
```
**Complexity**: `O(n log n)`. **Space**: `O(n)`.
**Edge cases**: one symbol only (no merges needed), all equal frequencies, frequency `0`.
**Pattern to remember**: Pattern 7 (priority queue + greedy).

### Minimum Number of Platforms

**Problem**: given train arrival and departure times, find the minimum number of platforms needed so no train waits.
**Looks greedy because**: "minimum resource count" with overlapping time intervals.
**Wrong approach**: count trains at a single fixed time snapshot instead of tracking the running maximum overlap.
**Greedy observation**: the answer is the maximum number of trains simultaneously present, found by tracking arrivals and departures as sorted event streams.
**Greedy choice**: sort arrivals and departures separately; sweep with two pointers, incrementing a counter on arrival and decrementing on departure, tracking the maximum.
```cpp
int minPlatforms(vector<int> arrival, vector<int> departure) {
    sort(arrival.begin(), arrival.end());
    sort(departure.begin(), departure.end());
    int platforms = 0, maxPlatforms = 0, i = 0, j = 0;
    int n = arrival.size();
    while (i < n && j < n) {
        if (arrival[i] <= departure[j]) { // a train arrives (using <= to handle same-time edge)
            platforms++;
            maxPlatforms = max(maxPlatforms, platforms);
            i++;
        } else {
            platforms--;
            j++;
        }
    }
    return maxPlatforms;
}
```
**Complexity**: `O(n log n)`. **Space**: `O(1)` extra.
**Edge cases**: a train's arrival equals another's departure (define whether that needs a new platform), single train, all trains overlapping.
**Pattern to remember**: Pattern 6 (sort + two pointers) combined with interval overlap counting.

### Interval Scheduling & Interval Merging

**Interval Scheduling** is the general name for Activity Selection (see above).
**Interval Merging problem**: given a set of intervals, merge all overlapping ones.
**Greedy choice**: sort by start time; scan and merge whenever the current interval's start is ≤ the last merged interval's end.
```cpp
vector<pair<int,int>> mergeIntervals(vector<pair<int,int>> intervals) {
    sort(intervals.begin(), intervals.end());
    vector<pair<int,int>> merged;
    for (auto &interval : intervals) {
        if (merged.empty() || merged.back().second < interval.first) {
            merged.push_back(interval);
        } else {
            merged.back().second = max(merged.back().second, interval.second);
        }
    }
    return merged;
}
```
**Complexity**: `O(n log n)`. **Space**: `O(n)`.
**Edge cases**: touching intervals (`[1,5]` and `[5,10]` — do they merge? clarify inclusivity), fully nested intervals, unsorted input.
**Pattern to remember**: Pattern 5 (sort and process), Section 16 (interval greedy).

### Minimum Number of Arrows to Burst Balloons

**Problem**: balloons as intervals on a number line; find the minimum number of arrows (vertical shots) to burst all balloons.
**Greedy choice**: sort by end coordinate; shoot an arrow at the end of the first unburst balloon; skip all balloons this arrow bursts (those with start ≤ arrow position); repeat.
```cpp
int minArrows(vector<pair<int,int>>& balloons) {
    if (balloons.empty()) return 0;
    sort(balloons.begin(), balloons.end(),
         [](auto &a, auto &b){ return a.second < b.second; });
    int arrows = 1;
    long long arrowPos = balloons[0].second;
    for (auto &[start, end] : balloons) {
        if (start > arrowPos) { // this balloon is not burst by the current arrow
            arrows++;
            arrowPos = end;
        }
    }
    return arrows;
}
```
**Complexity**: `O(n log n)`. **Space**: `O(1)` extra.
**Edge cases**: overflow with large coordinates (use `long long`), single balloon, all balloons identical.
**Pattern to remember**: Pattern 11 (cover as much as possible).

### Jump Game

**Problem**: given an array where each value is the max jump length from that index, determine if you can reach the last index.
**Greedy choice**: track the farthest reachable index while scanning left to right; if the current index exceeds the farthest reachable point, it's impossible.
```cpp
bool canJump(vector<int>& nums) {
    int farthest = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > farthest) return false;  // current index unreachable
        farthest = max(farthest, i + nums[i]);
    }
    return true;
}
```
**Complexity**: `O(n)`. **Space**: `O(1)`.
**Edge cases**: array of size 1 (always reachable), a `0` at the very first index blocking everything, large jump values.
**Pattern to remember**: Pattern 12 (maintain the best candidate).

### Gas Station

**Problem**: circular route of gas stations with `gas[i]` fuel gained and `cost[i]` fuel needed to reach the next station; find the starting station to complete the circuit, or determine it's impossible.
**Greedy choice**: if total gas ≥ total cost, a solution exists; scan once, tracking running tank total — whenever it goes negative, the start must move to the next station.
```cpp
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    long long totalTank = 0, currTank = 0;
    int start = 0;
    for (int i = 0; i < (int)gas.size(); i++) {
        long long diff = gas[i] - cost[i];
        totalTank += diff;
        currTank += diff;
        if (currTank < 0) {   // can't reach i+1 from current start
            start = i + 1;
            currTank = 0;
        }
    }
    return totalTank >= 0 ? start : -1;
}
```
**Complexity**: `O(n)`. **Space**: `O(1)`.
**Edge cases**: single station, total gas exactly equal to total cost, all stations negative.
**Pattern to remember**: Pattern 12 (maintain the best candidate).

### Assign Cookies

**Problem**: children with greed factors and cookies with sizes; maximize the number of satisfied children (a cookie satisfies a child if its size ≥ the child's greed factor).
**Greedy choice**: sort both arrays ascending; use two pointers, assigning the smallest sufficient cookie to the least greedy unsatisfied child.
```cpp
int findContentChildren(vector<int>& greed, vector<int>& cookies) {
    sort(greed.begin(), greed.end());
    sort(cookies.begin(), cookies.end());
    int child = 0, cookie = 0, satisfied = 0;
    while (child < (int)greed.size() && cookie < (int)cookies.size()) {
        if (cookies[cookie] >= greed[child]) {
            satisfied++;
            child++;
        }
        cookie++; // move to next cookie regardless (too-small cookies are wasted)
    }
    return satisfied;
}
```
**Complexity**: `O(n log n)`. **Space**: `O(1)` extra.
**Edge cases**: no cookies, no children, all cookies too small.
**Pattern to remember**: Pattern 1 (take the smallest possible value) + Pattern 6 (two pointers).

### Candy

**Problem**: children in a line, each with a rating; each child needs at least 1 candy, and a child with a higher rating than a neighbor must get more candy than that neighbor; minimize total candy.
**Greedy choice**: two passes — left to right, increase candy if `rating[i] > rating[i-1]`; right to left, take the max of the current value and `candy[i+1]+1` if `rating[i] > rating[i+1]`.
```cpp
int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1);
    for (int i = 1; i < n; i++)                     // left-to-right pass
        if (ratings[i] > ratings[i-1]) candies[i] = candies[i-1] + 1;
    for (int i = n - 2; i >= 0; i--)                 // right-to-left pass
        if (ratings[i] > ratings[i+1]) candies[i] = max(candies[i], candies[i+1] + 1);
    int total = 0;
    for (int c : candies) total += c;
    return total;
}
```
**Complexity**: `O(n)`. **Space**: `O(n)`.
**Edge cases**: all equal ratings (everyone gets 1), strictly increasing/decreasing ratings, single child.
**Pattern to remember**: this needs two directional passes because a single left-to-right greedy pass cannot satisfy both neighbor constraints at once — a good example of why you must check whether one pass is enough.

### Boats to Save People

**Problem**: people with weights, boats hold at most 2 people and a weight limit; minimize number of boats.
**Greedy choice**: sort weights ascending; two pointers from both ends — pair the lightest and heaviest if their sum fits the limit, otherwise send the heaviest alone.
```cpp
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int left = 0, right = people.size() - 1, boats = 0;
    while (left <= right) {
        if (people[left] + people[right] <= limit) left++; // lightest can join heaviest
        right--;    // heaviest always leaves on this boat
        boats++;
    }
    return boats;
}
```
**Complexity**: `O(n log n)`. **Space**: `O(1)` extra.
**Edge cases**: single person, all weights equal to the limit, one very heavy person exceeding pairing with anyone.
**Pattern to remember**: Pattern 6 (sort + two pointers).

### Partition Labels

**Problem**: partition a string into as many parts as possible so each letter appears in at most one part.
**Greedy choice**: for each letter, find its last occurrence; scan and extend the current partition's end to the max last-occurrence seen so far; close the partition when the scan position reaches that end.
```cpp
vector<int> partitionLabels(string s) {
    vector<int> last(26, 0);
    for (int i = 0; i < (int)s.size(); i++) last[s[i]-'a'] = i;
    vector<int> result;
    int start = 0, end = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        end = max(end, last[s[i]-'a']);
        if (i == end) {              // reached the boundary of this partition
            result.push_back(end - start + 1);
            start = i + 1;
        }
    }
    return result;
}
```
**Complexity**: `O(n)`. **Space**: `O(26)`.
**Edge cases**: single character, string where every character repeats at the very end (one partition only), empty string.
**Pattern to remember**: Pattern 12 (maintain the best candidate) applied to ranges instead of values.

### Non-overlapping Intervals

**Problem**: given intervals, find the minimum number to remove so the rest don't overlap.
**Greedy choice**: sort by end time; keep an interval if it starts after (or at) the last kept interval's end; otherwise it must be removed.
```cpp
int eraseOverlapIntervals(vector<pair<int,int>>& intervals) {
    if (intervals.empty()) return 0;
    sort(intervals.begin(), intervals.end(),
         [](auto &a, auto &b){ return a.second < b.second; });
    int kept = 1, lastEnd = intervals[0].second;
    for (int i = 1; i < (int)intervals.size(); i++) {
        if (intervals[i].first >= lastEnd) {
            kept++;
            lastEnd = intervals[i].second;
        }
    }
    return (int)intervals.size() - kept;
}
```
**Complexity**: `O(n log n)`. **Space**: `O(1)` extra.
**Edge cases**: fully identical intervals, already non-overlapping input, touching boundaries.
**Pattern to remember**: this is Pattern 10 (minimize loss) applied to Pattern 3 (earliest finish) — same core idea as Activity Selection, reframed as "removal."

### Meeting Rooms (Minimum Rooms Needed)

**Problem**: given meeting intervals, find the minimum number of rooms required.
**Greedy choice**: use a min-heap of end times; for each meeting (sorted by start), if the earliest-ending room's meeting has already ended, reuse that room; otherwise allocate a new one.
```cpp
int minMeetingRooms(vector<pair<int,int>>& meetings) {
    if (meetings.empty()) return 0;
    sort(meetings.begin(), meetings.end()); // sort by start time
    priority_queue<int, vector<int>, greater<int>> endTimes; // min-heap of end times
    for (auto &[start, end] : meetings) {
        if (!endTimes.empty() && endTimes.top() <= start) {
            endTimes.pop(); // reuse the earliest-freed room
        }
        endTimes.push(end);
    }
    return endTimes.size();
}
```
**Complexity**: `O(n log n)`. **Space**: `O(n)`.
**Edge cases**: meetings that touch exactly at boundaries, all meetings overlapping, single meeting.
**Pattern to remember**: Pattern 7 (priority queue + greedy) — same idea as Minimum Platforms, implemented with a heap instead of two sorted arrays.

### Minimum Coins (When Greedy IS Valid)

**Problem**: minimum number of coins to make a target amount, for a "canonical" coin system (e.g., standard currency `{1, 5, 10, 25, ...}`).
**Important caveat**: greedy is only valid here because these specific denominations are canonical (every value can be optimally built by always taking the largest fitting coin). This does NOT generalize — see Section 12 for when it fails.
```cpp
int minCoinsGreedy(vector<int>& coins, int amount) { // coins sorted descending, canonical system
    int count = 0;
    for (int c : coins) {
        count += amount / c;
        amount %= c;
    }
    return amount == 0 ? count : -1; // -1 shouldn't happen for a true canonical system covering amount
}
```
**Complexity**: `O(n)` after sorting. **Space**: `O(1)`.
**Edge cases**: amount `0`, amount not reachable (shouldn't occur in a canonical system if `1` is included), verifying canonicity before trusting this approach.
**Pattern to remember**: Pattern 2 (take the largest possible value) — but always verify the coin system is canonical first; when in doubt, use DP.

---
## 12. Problems Where Greedy LOOKS Correct but Fails

### 0/1 Knapsack
**Tempting idea**: sort by value/weight ratio descending, take whole items greedily like Fractional Knapsack.
**Counterexample**: capacity `10`. Items: `(weight 6, value 30)`, `(weight 5, value 25)`, `(weight 5, value 20)`. Ratio order: item1 (5.0), item2 (5.0), item3 (4.0). Greedy might take item1 (weight 6, value 30) then can't fit anything else (only 4 capacity left, next items need 5) → total `30`. But taking item2 + item3 (weight 10, value 45) is better.
**Why it fails**: items can't be split, so a high-ratio item can "waste" leftover capacity that a different combination would use fully.
**What to use instead**: DP over `(item index, remaining capacity)`.

### Coin Change with Arbitrary Denominations
**Tempting idea**: always take the largest coin that fits.
**Counterexample**: denominations `{1, 3, 4}`, target `6` → greedy gives `4+1+1` (3 coins), optimal is `3+3` (2 coins).
**Why it fails**: the coin system isn't canonical; a large coin can leave a remainder that needs many small coins, while a slightly smaller coin would have left a remainder needing fewer.
**What to use instead**: DP — `minCoins[amount] = 1 + min(minCoins[amount - c])` over all coins `c`.

### Some Scheduling Problems (Weighted Job Scheduling, No Fixed Duration)
**Tempting idea**: sort by end time and greedily take jobs like Activity Selection, but jobs have different profits/weights, not just a count to maximize.
**Counterexample**: two compatible short jobs with profit `1` each vs. one long job overlapping both with profit `100`. Earliest-finish greedy picks the two short jobs (total `2`), but the single long job (`100`) is far better.
**Why it fails**: Activity Selection's proof only works when you're maximizing *count*, not weighted value. Once profits differ, "earliest finish" is no longer safe.
**What to use instead**: DP with binary search over compatible previous jobs (weighted interval scheduling).

### Choosing the Largest Immediately — General Trap
**Tempting idea**: "bigger is always better" when maximizing a sum under a shared constraint.
**Counterexample**: maximize the number of items picked whose total weight ≤ capacity `10`, items `{9, 5, 5}` — greedily taking the largest item (9) leaves no room for anything else (1 item total). Taking the two 5s (5+5=10) gives 2 items.
**Why it fails**: "largest value" and "best use of a shared limited resource" are different objectives; conflating them is a common trap.
**What to use instead**: depends on the exact objective — often DP, sometimes greedy by smallest-first if the true objective is "maximize count" (see Assign Cookies pattern).

### Choosing the Smallest Immediately — General Trap
**Tempting idea**: "always clear the smallest obligation first" to minimize some downstream cost.
**Counterexample**: minimizing maximum lateness with jobs of different processing times and due dates — always doing the shortest job first ignores due dates and can cause the job with the tightest deadline to become late.
**Why it fails**: the ordering that minimizes one property (job count finished fast) doesn't necessarily minimize the actual target metric (maximum lateness), which depends on due dates too.
**What to use instead**: sort by the property that actually matches the objective (e.g., Earliest Due Date rule for minimizing maximum lateness) — a reminder that "smallest first" is not automatically correct just because it feels efficient.

### Ratio Sorting Fails Without Divisibility
**Tempting idea**: sort by ratio descending whenever a problem "smells like" Fractional Knapsack.
**Counterexample**: same as the 0/1 Knapsack example above — ratio sorting alone ignores that whole items must fit together.
**Why it fails**: ratio-based greedy assumes you can always convert unused "partial capacity" into value, which is only true when items are divisible.
**What to use instead**: DP whenever items are indivisible and combinations matter.

---

## 13. How to Choose the Sorting Comparator

Basic ascending sort:
```cpp
sort(v.begin(), v.end()); // ascending, using operator<
```

Custom comparator (lambda) — this is the workhorse of greedy code:
```cpp
sort(v.begin(), v.end(), [](auto &a, auto &b) {
    return a.second < b.second;   // sort pairs by their second value, ascending
});
```
**What this means**: the comparator returns `true` if `a` should come **before** `b` in the sorted order. Read it as "is `a` strictly less than `b` under my chosen rule?"

**Ascending vs descending:**
```cpp
sort(v.begin(), v.end(), [](int a, int b){ return a < b; });  // ascending
sort(v.begin(), v.end(), [](int a, int b){ return a > b; });  // descending
```

**Sorting pairs by second value:**
```cpp
sort(v.begin(), v.end(), [](auto &a, auto &b){ return a.second < b.second; });
```

**Sorting intervals by start, then by end for ties:**
```cpp
sort(intervals.begin(), intervals.end(), [](auto &a, auto &b){
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
});
```
(Note: a plain `sort(v.begin(), v.end())` on `pair<int,int>` already does exactly this, because `pair` compares lexicographically by default.)

**Tie-breaking explicitly:**
```cpp
sort(jobs.begin(), jobs.end(), [](auto &a, auto &b){
    if (a.profit != b.profit) return a.profit > b.profit;  // primary: profit descending
    return a.deadline < b.deadline;                         // secondary: earlier deadline first
});
```

**Common mistake**: writing a comparator that isn't a strict weak ordering (e.g., using `<=` instead of `<`), which causes undefined behavior in `std::sort` — sometimes a crash, sometimes silently wrong output. Always use strict `<` or `>` in comparators, never `<=` or `>=`.

---

## 14. Greedy + STL

| STL tool | When it's useful in greedy problems |
|---|---|
| `vector` | Default container for storing items, intervals, jobs before/after sorting |
| `pair` | Bundling two related values (start/end, weight/value) so you can sort them together |
| `sort` | The core tool that turns "find best remaining option" into a linear scan |
| `priority_queue` | When the best candidate changes dynamically as you process input (Huffman, Meeting Rooms, top-k problems) |
| `set` | Maintaining a sorted, searchable collection with fast insert/erase/find — useful for "find nearest available slot" greedy patterns |
| `multiset` | Like `set` but allows duplicates — useful when values repeat and you still need sorted order with removal |
| `map` | Frequency counting, or mapping a key (like a deadline) to a value while keeping keys sorted |
| `deque` | Sliding window greedy problems where you need to push/pop from both ends efficiently |
| `lower_bound` / `upper_bound` | Binary search on sorted data — finding the first slot ≥ or > a value, common in scheduling and interval greedy |

**Practical notes:**
- `priority_queue<int, vector<int>, greater<int>>` gives a min-heap; the default `priority_queue<int>` is a max-heap.
- `set` and `multiset` support `lower_bound`/`upper_bound` as **member functions**, which is `O(log n)` — don't use the free-function versions on them, those are `O(n)` for non-random-access containers.
- Use `multiset::erase(iterator)` instead of `multiset::erase(value)` when you only want to remove **one** occurrence — the value-based erase removes all duplicates.

---

## 15. Priority Queue Greedy

**Min heap** (`priority_queue<T, vector<T>, greater<T>>`): gives fast access to the smallest current candidate — used when you repeatedly need "the smallest remaining X" as the set changes (e.g., repeatedly merging the two smallest Huffman frequencies, or tracking the earliest-freeing meeting room).

**Max heap** (default `priority_queue<T>`): gives fast access to the largest current candidate — used for "always process the most urgent/valuable item next" as new items get added dynamically (e.g., task scheduler problems, or evicting the least profitable already-scheduled job when a higher-profit one needs its slot).

**When a heap is the missing piece of a greedy solution**: whenever a single upfront sort isn't enough because the pool of "current candidates" changes over time — new items become available as you go, or items get removed based on a rule that isn't just "process in original sorted order."

**Adding/removing candidates**: push new candidates as they become eligible (e.g., a job's start time has passed, an interval has opened up); pop the top and process it, sometimes pushing a modified version back (as in Huffman, where the merged node is pushed back in).

**Deadlines and scheduling with a heap**: process items sorted by one property (e.g., start time or deadline), and use the heap to track "resources in use" or "resources available," querying/popping the top to decide reuse vs. new allocation (Meeting Rooms) or eviction (task scheduling with limited slots).

**Maintaining top-k choices**: keep a heap of size `k`; if a new candidate is better than the heap's worst element (top of a min-heap sized `k` for "keep k largest"), pop and push.

**Example — task scheduler-like eviction**: when a new job's deadline forces a conflict with an already-scheduled lower-profit job, use a min-heap of scheduled profits to evict the cheapest one if the new job's profit is higher.

---

## 16. Interval Greedy

**Representation**: usually `pair<int,int>` or a small struct with `start` and `end`, sometimes with extra fields like `id`, `weight`, or `deadline`.

**Sorting choice matters a lot:**
- **Sort by start time**: needed when you're scanning intervals in the order they "open," e.g., merging overlapping intervals, or counting simultaneous overlaps with a sweep.
- **Sort by end time**: needed when you're trying to maximize the count of non-overlapping intervals you can keep, because ending earlier preserves the most room for future intervals (Activity Selection, Non-overlapping Intervals, Minimum Arrows).

**Common interval problems and their core technique:**
- **Merging intervals**: sort by start, merge while `next.start <= current.end`.
- **Non-overlapping intervals (maximize kept / minimize removed)**: sort by end, greedily keep compatible ones.
- **Maximum number of intervals overlapping at any point (Minimum Platforms / Meeting Rooms)**: sort starts and ends separately (or use a heap) and sweep, tracking the running count.
- **Interval coverage (minimum arrows / points to hit all intervals)**: sort by end, place a point at the end of the first uncovered interval, skip everything it covers.

**Why sorting by start vs. end leads to different strategies**: sorting by start answers "what opens next, in order?" — good for detecting overlaps as they begin. Sorting by end answers "what closes soonest, freeing up room?" — good for greedily maximizing how many non-conflicting intervals you can fit, because the earliest-ending option always preserves the most future flexibility.

---
## 17. Mathematical Greedy

Some greedy strategies come from a mathematical observation rather than a scheduling/interval structure.

- **Absolute difference**: to minimize the sum of absolute differences between paired elements from two arrays, sort both arrays ascending and pair by position — any other pairing can be shown (via exchange argument) to be at least as large.
- **Minimum/maximum**: when an operation must be applied repeatedly and you want to minimize the final maximum (or maximize the final minimum), it's often best to always act on the current extreme element (e.g., repeatedly reduce the largest pile in certain "equalize" problems).
- **Parity**: some problems reduce to "you can only fix pairs of a certain parity" — recognizing that odd/even counts constrain what's achievable at all often turns into a simple greedy count-and-pair strategy.
- **Frequencies**: problems about rearranging or reducing based on how often values/characters occur often greedily process from the highest-frequency element down (e.g., reorganizing a string so no two adjacent characters are equal, via a max-heap by frequency).
- **Exchange of values**: if you can show that swapping two values in a sequence never decreases (or never increases) some target metric unless they're already in a specific relative order, that gives you a full sorting-based greedy rule (this is Pattern 13 in a mathematical form).
- **Choosing extremes**: many "minimize the maximum" or "maximize the minimum" problems benefit from greedily handling the current extreme value first, often combined with binary search on the answer (binary search + greedy feasibility check is an extremely common competitive programming combo).
- **Rearrangement**: the rearrangement inequality — pairing sorted sequences in the same order maximizes the sum of products, and pairing them in opposite order minimizes it. This underlies many "assign tasks to maximize/minimize total cost" problems.
- **Cost minimization**: when merging costs (like Huffman) or combining values with an additive cost each time, always combining the two cheapest/smallest pending items first tends to minimize total cost — provable via optimal substructure.

---

## 18. Greedy with Strings

- **Choosing lexicographically smallest character**: when building a string greedily, at each position try the smallest available character that still allows the rest of the construction to be completed validly.
- **Building smallest/largest string under constraints**: often solved with a **monotonic stack** — scan the string, and while the top of the stack is worse than the current character and removing it is still allowed (e.g., you have removals left), pop it.
```cpp
string removeKDigits(string num, int k) {
    string stack;
    for (char c : num) {
        while (k > 0 && !stack.empty() && stack.back() > c) {
            stack.pop_back();
            k--;
        }
        stack.push_back(c);
    }
    while (k-- > 0) stack.pop_back();      // remove any leftover digits from the end
    int start = 0;
    while (start < (int)stack.size() - 1 && stack[start] == '0') start++; // strip leading zeros
    string result = stack.substr(start);
    return result.empty() ? "0" : result;
}
```
- **Removing characters to optimize a result**: usually the monotonic stack pattern above — greedily remove a "worse" character if a "better" one follows and you still have removal budget.
- **Frequency-based choices**: for problems like "reorganize string so no two adjacent characters match," use a max-heap by frequency, always placing the currently most frequent valid character next.
- **Stack + greedy**: very common combo — the stack enforces the constraint (validity, monotonic order) while the greedy rule decides what to push/pop.
- **Constructing strings greedily**: build character by character, always trying the best candidate first, but only commit if it keeps a valid construction possible for the remaining characters.

---

## 19. Greedy with Arrays

- **Choosing extremes**: many problems reduce to "always take the current min or max" (Gas Station's running minimum, or repeatedly removing the largest element under a constraint).
- **Sorting**: the single most common first step — once sorted, many array problems become simple linear scans (Assign Cookies, Boats to Save People).
- **Prefix/suffix decisions**: precompute prefix sums, prefix maximums, or suffix minimums so each greedy decision at position `i` can be made in `O(1)` using precomputed information from both directions (Candy problem's two-pass approach).
- **Maintaining best value**: keep a running best-so-far (min/max) while scanning once, updating the answer as you go (classic single-pass greedy, e.g., "maximum profit from one buy/sell" tracked with a running minimum price).
- **Local swaps**: check if swapping two adjacent elements improves a global metric, and generalize that check into a full sort comparator (Pattern 13).
- **Partitioning**: split the array into segments based on a greedy rule about when a segment must end (Partition Labels' "extend until reaching the max last-occurrence" rule).
- **Two pointers**: pair elements from opposite ends of a sorted array to satisfy a constraint efficiently (Boats to Save People).
- **Frequency counting**: use an array or map as a counter, then greedily process values by descending/ascending frequency (string reorganization, task scheduling with cooldowns).

---

## 20. Greedy with Graphs

Only the greedy graph algorithms that matter most for competitive programming.

### Kruskal's Algorithm (Minimum Spanning Tree)
**Greedy choice**: sort all edges by weight ascending; add an edge if it doesn't form a cycle (checked via Union-Find / DSU).
**Why it works**: adding the globally cheapest edge that doesn't create a cycle is always safe — it can be shown via an exchange argument (the "cycle property" of MSTs: the most expensive edge in any cycle is never in the MST).
**Conditions required**: works on any connected, undirected, weighted graph; edge weights can be any real numbers (positive, negative, or zero).
**When it fails**: doesn't apply directly to directed graphs (that's a different problem, "minimum arborescence") or when you need a spanning structure with additional constraints beyond total weight.
**Complexity**: `O(E log E)` for sorting, plus near-`O(E α(V))` for DSU operations.
```cpp
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};

long long kruskalMST(int n, vector<array<int,3>>& edges) { // {weight, u, v}
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    long long totalWeight = 0;
    for (auto &[w, u, v] : edges) {
        if (dsu.unite(u, v)) totalWeight += w; // only add if it connects two different components
    }
    return totalWeight;
}
```

### Prim's Algorithm (Minimum Spanning Tree)
**Greedy choice**: start from any node; repeatedly add the cheapest edge that connects the current tree to a new vertex, using a min-heap of candidate edges.
**Why it works**: same underlying cut property as Kruskal's — the cheapest edge crossing any cut is always safe to include.
**Conditions required**: connected, undirected, weighted graph.
**When it fails**: same limitations as Kruskal's regarding directed graphs.
**Complexity**: `O(E log V)` with a binary heap.

### Dijkstra's Algorithm (Shortest Paths)
**Greedy choice**: repeatedly pick the unvisited vertex with the smallest known distance, and relax its outgoing edges, using a min-heap.
**Why it works**: once a vertex is popped with the smallest tentative distance among all unvisited vertices, that distance is final — no unvisited vertex could offer a shorter path to it, because all edge weights are non-negative.
**Conditions required**: all edge weights must be **non-negative**.
**Why Dijkstra fails with negative edge weights**: the proof that "the smallest tentative distance is final" relies on the fact that no future relaxation through an unvisited (farther) vertex could ever produce a shorter path — because adding a non-negative edge weight can't decrease a distance. With negative edges, a longer-looking path through a vertex with a larger tentative distance could still end up shorter, so a vertex popped "too early" may later need its distance corrected, which Dijkstra's algorithm never does. Use **Bellman-Ford** (`O(VE)`) when negative edges are present (and it can also detect negative cycles).
**Complexity**: `O(E log V)` with a binary heap and adjacency list.
```cpp
vector<long long> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src) { // adj[u] = {v, weight}
    vector<long long> dist(n, LLONG_MAX);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue; // stale entry, skip
        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

---

## 21. Greedy Decision Checklist

Use this literally, during a contest, before writing code.

```text
1. What am I optimizing?
   -> State it in one precise sentence. If you can't, re-read the problem.

2. What decision do I repeatedly make?
   -> Identify the "unit choice" — which item, which slot, which order.

3. What is the locally best choice?
   -> Write the exact rule: largest / smallest / earliest / latest / best ratio / etc.

4. Why should this choice never hurt the future?
   -> Explain in one sentence why picking it now doesn't close off a better outcome later.

5. Can I exchange it with the first choice of an optimal solution?
   -> Try the exchange argument: swap your choice into a hypothetical optimal solution
      and check nothing gets worse.

6. Can I construct a counterexample?
   -> Actively try small, equal, extreme, and duplicate-value inputs to break your rule.

7. Does sorting reveal an ordering?
   -> Identify exactly what property to sort by, matching your greedy choice.

8. Do I need a priority queue?
   -> Check if the "best candidate" changes dynamically as you process input.

9. Is the problem actually DP?
   -> Check if the value of your choice depends on other choices through a shared
      constraint (like capacity) in a way a single rule can't capture.

10. Can I prove the greedy choice?
    -> If yes, implement with confidence. If no, and you can't find a counterexample
       either, weigh contest time cost vs. risk, and consider stress-testing against
       a brute force before submitting.
```

---

## 22. Greedy Debugging Checklist

When a greedy solution gives a wrong answer, check these in order:

- **Wrong sorting order**: ascending vs. descending mixed up, or sorting by the wrong field entirely.
- **Wrong tie-breaking**: two elements with equal primary key need a secondary sort key — check what the problem actually requires when values tie.
- **Choosing based on the wrong property**: double-check the greedy rule matches what you proved/tested, not a slightly different variant you coded by mistake.
- **Ignoring future consequences**: verify your "locally best" choice doesn't have a hidden interaction with later decisions you didn't account for (this often means the greedy idea itself was wrong, not just the code).
- **Not updating the best candidate**: forgetting to update a running min/max/lastEnd variable after using it.
- **Incorrect interval boundaries**: off-by-one on whether touching intervals (`end == next start`) count as overlapping — re-read the problem statement's inclusivity rules.
- **Incorrect priority queue usage**: pushing the wrong value, forgetting to pop stale/invalid entries (common with lazy deletion), or using a max-heap when you needed a min-heap (or vice versa).
- **Off-by-one errors**: loop bounds, 0-indexed vs. 1-indexed slots (common in Job Sequencing deadline arrays).
- **Empty input**: does your code handle zero elements gracefully, or crash/misbehave?
- **Duplicate values**: verify your comparator and logic still work when many elements are equal.
- **Equal endpoints**: intervals or values that tie exactly at a boundary — confirm your `<` vs `<=` matches the intended rule.
- **Large values and integer overflow**: sums of large weights/profits/coordinates can overflow `int` — use `long long` wherever totals could get large, and double-check multiplication before addition.

---

## 23. Complexity

Greedy complexity almost always comes from one (or a combination) of these sources:

| Complexity | Typically comes from |
|---|---|
| `O(n)` | A single linear scan after the input is already usable (e.g., Gas Station, Jump Game, Candy) |
| `O(n log n)` | Sorting the input once, then a linear scan (most interval and "sort + greedy" problems) |
| `O(n log k)` | Maintaining a heap of bounded size `k` while scanning `n` elements (top-k style problems) |
| `O(n²)` | A greedy choice requiring, for each of `n` elements, an `O(n)` search for the right slot (e.g., naive Job Sequencing with a linear backward scan per job) |

**Where the complexity comes from, concretely:**
- **Sorting**: `O(n log n)` — dominates most greedy algorithms since it's usually the most expensive single step.
- **Heap operations**: `O(log n)` per push/pop, so `O(n log n)` total across `n` operations.
- **Set/multiset operations**: `O(log n)` per insert/erase/find, same total order as heaps.
- **Multiple passes**: each additional full pass over the input adds another `O(n)` factor — still cheap unless the number of passes depends on input size (watch for accidentally nested loops disguised as "just one more pass").

---

## 24. Competitive Programming Workflow

### During contest

```
Read problem
  → identify objective
  → identify choices
  → try brute force mentally (or on paper for tiny n)
  → find greedy candidate
  → test small cases
  → search for counterexample
  → prove (or convince yourself as rigorously as time allows)
  → choose data structure
  → implement
  → test edge cases
  → submit
```

**How long to spend before abandoning a greedy idea**: as a rough guide, if you can't find a proof or break the idea with a counterexample within a few minutes of focused effort, and the problem's constraints are small enough for DP or another approach to fit the time limit, it's often safer to pivot rather than gamble on an unproven greedy idea — especially on unfamiliar or higher-difficulty problems. On easier problems, or when the intended solution is clearly greedy (small time limit, large constraints ruling out DP), it's reasonable to trust a rule that survived several counterexample attempts and submit, using the judge's verdict as feedback if wrong.

---

## 25. How to Practice Greedy

### Level 1 — Basic Greedy Recognition
Goal: get comfortable stating the objective precisely and proposing an obvious greedy rule. Solve simple "pick the best option each step" problems (Assign Cookies, simple array greedy). **Skill to gain before moving on**: being able to state, in one sentence, "what am I optimizing and what's my rule" for any easy greedy problem.

### Level 2 — Sorting + Greedy
Goal: get fluent with custom comparators and recognizing what property to sort by. Solve problems like Candy, Boats to Save People. **Skill to gain**: instantly identifying the right sort key from the problem statement.

### Level 3 — Intervals
Goal: master interval representation, sorting by start vs. end, and the classic interval patterns. Solve Activity Selection, Merge Intervals, Non-overlapping Intervals, Minimum Arrows. **Skill to gain**: recognizing which interval pattern (Section 16) a new problem matches.

### Level 4 — Priority Queue + Greedy
Goal: recognize when the candidate pool changes dynamically and needs a heap. Solve Huffman Coding, Meeting Rooms, task scheduling problems. **Skill to gain**: identifying when a single sort isn't enough and a heap is required.

### Level 5 — Greedy with Proofs
Goal: stop trusting "it looks right" and start actually proving or disproving greedy ideas using exchange argument, staying ahead, and counterexample search. Revisit earlier solved problems and write a one-paragraph proof for each. **Skill to gain**: comfortably applying at least two of the four proof techniques from Section 5 under time pressure.

### Level 6 — Hard Codeforces-Style Greedy
Goal: handle problems where the greedy rule is non-obvious, requires a clever reformulation (Section 17's mathematical greedy, or combining greedy with binary search), or requires recognizing a subtle DP-vs-greedy boundary. Solve Div 2 D/E-level greedy problems and problems tagged "greedy" with high difficulty ratings. **Skill to gain**: independently discovering non-obvious greedy rules using the brute-force-to-pattern workflow (Section 8), not just applying memorized patterns.

---

## 26. Problem Analysis Template

Copy this for every greedy problem you solve — it builds the habit of proving before implementing.

```markdown
## Problem


## Observation


## Greedy Choice


## Why Greedy Works


## Proof


## Algorithm


## Complexity


## Edge Cases


## Implementation


## Mistake I Initially Made


## Pattern Learned

```

---
## 27. Final Cheat Sheet

**Greedy recognition clues** (none of these prove correctness — test before trusting):
- Max/min optimization, selection, scheduling, intervals, deadlines, resource allocation, "minimum operations," "maximum count," sorting reveals structure.

**Common greedy choices:**
- Largest / smallest first, earliest finish, latest slot, cheapest, best ratio, largest immediate gain.

**Common sorting strategies:**
- By end time (maximize non-overlapping count), by start time (merging/sweeping), by ratio descending (fractional/divisible problems), by profit descending (deadline scheduling), by value/cost ascending or descending depending on objective.

**Common STL tools:**
- `sort` + comparator, `priority_queue` (min/max heap), `set`/`multiset` for sorted dynamic collections, `lower_bound`/`upper_bound` for fast slot search, `pair`/`tuple` for bundling sort keys.

**Proof techniques:**
- **Exchange argument** — swap greedy's choice into an optimal solution without making it worse.
- **Staying ahead** — show greedy's partial progress is never behind any other solution's, step by step.
- **Optimal substructure** — show the remaining problem after the greedy choice is a smaller instance of the same problem.
- **Contradiction** — assume the greedy choice isn't in some optimal solution, construct a modification that includes it without loss.

**Counterexample techniques:**
- Small cases, equal values, extreme values, duplicate values, smallest/largest single input, cases designed to make the local choice block a better future option.

**Greedy vs DP — quick test:**
- Can you prove the choice with exchange/optimal substructure? → Greedy.
- Does the value of a choice depend on interacting combinations through a shared constraint (like capacity)? → DP.
- Found a counterexample? → DP (or refine the rule with more state).

**Common patterns (see Section 10 for full detail):**
1. Smallest first · 2. Largest first · 3. Earliest finish · 4. Latest choice · 5. Sort and process · 6. Sort + two pointers · 7. Priority queue · 8. Deadlines · 9. Ratio-based · 10. Minimize loss / maximize gain · 11. Cover as much as possible · 12. Maintain best candidate · 13. Swapping · 14. Constructive.

**Common traps:**
- 0/1 Knapsack (ratio sort fails — items aren't divisible).
- Arbitrary coin denominations (largest-first fails — system not canonical).
- Weighted interval scheduling (earliest-finish-only fails once profits differ).
- "Largest first" for shared-resource maximization (can waste capacity vs. multiple smaller items).
- Dijkstra with negative edges (breaks the "popped distance is final" guarantee — use Bellman-Ford).

**Complexity reminders:**
- `O(n)`: single pass, no sort needed.
- `O(n log n)`: sort once, then linear scan — the most common greedy complexity.
- `O(n log k)`: heap of bounded size `k`.
- `O(n²)`: naive per-element search for a slot — often improvable with a heap or DSU to `O(n log n)`.

**Before every submission, ask:**
1. Did I actually try to break my own rule?
2. Did I check ties, duplicates, and extreme values?
3. Did I check for integer overflow on sums of large values?
4. Does my comparator use strict `<`/`>`, never `<=`/`>=`?
5. Did I handle empty input and single-element input?

---

*Place this file at `problems/Algorithms/Greedy/README.md`.*
