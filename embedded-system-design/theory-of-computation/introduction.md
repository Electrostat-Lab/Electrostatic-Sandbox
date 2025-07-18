# Introduction

This document will present some prerequisite definitions and formal representations for the Sets and the Relations, alongside some examples from the proof theory that will be used in the _"Theory of Computation"_.

## Sets: 
- Definition: A group of objects represented as a unit. A set may contain any type of objects, including numbers, symbols, and even other sets. The objects in a set are called **elements** or **members**.
- Formal description of sets:
    * Listing elements (Tabular Method): $$S = \[1, 2, 3, 4, ...\]$$
    * Set-builder notation: $$A = \[ x ∣ x∈N \land x≤5 \]$$
- Special instances of sets: 
    * Empty Set: is the set of null elements and is written as $$\phi$$, $$\phi = []$$.
    * Complement Set: is the negation of the specified set, and it's the set of all elements under consideration that are not in the specified set.
    * Singleton Set: is the set of _a single member_.
    * Unordered pair: is the set of _two members_.
    * Multiset: is a set of an additional modified property; in which the number of occurences of its members is not taken into account; thus $$S = [3, 3, 2]$$ is different from $$S = [3, 2]$$.
    * Powerset: is a set of all possible proper subsets of a set. The cardinality is the number of elements in the power set, and is calculated using $$|P(Q)| = 2^n$$; where $$n$$ is the number of members of the original set $$Q$$; Proof of the cardinality formula is made by taking the binomial 

- Operation on sets:
    * Complementation.
    * Union.
    * Intersection.
    * Exclusiveness.
    * Compound operators.
    * Cartesian product.

## Sequences:


* Ordered pairs:

* N-tuple collections:

## Relations and Functions: 

- Special instances of functions:
   * Predicates:
   * 

## The multiplicative principle of counting and $$\prod$$ (Pi Products) 

## Permutations
- **Definition**: _**Permutations**_ are sequences selected from sets of members (alternatively, later described as **subsets of sets** when dealing with the mathematical formulas); such that the order matters, and the _repetition properties_ are specified. 
- **Formula**: Recall that _A_ is a set of objects of cardinality $$|A| = n$$ members;
   * A permutation of A is the number of all the possible subsequences of A taken $$|A|$$ at a time; **given the property of no repetition of the permutated objects**:
      $$_nP_n = \prod\_{i = 0}^{(n - 1)} (n - i) = \frac{n!}{(n - n)!} = n! = n.(n-1).(n-2).(n-3)...(n-(n-2)).(n-(n-1))$$. 
   * The number of permutations of A taken _r_ at a time is the number of all the possible subsequences of A taken _r_ at a time (aka. subsequences constructed with cardinality of _r_); such that $$1 <= r <= n$$, and **given the property of no repetition of the permutated objects**: $$_rP_n = \prod\_{i = 0}^{(r - 1)} (n - i) = \frac{n!}{(n - r)!} = n.(n-1).(n-2).(n-3)....(n-(r-2)).(n-(r-1))$$.
   * The number of permutations of A taken _r_ at a time is the number of all the possible subsequences of A taken _r_ at a time; such that $$1 <= r <= n$$, and **given the property of allowed repetitions of the permutated objects**; such that the first member $m_0$ repeats $k_0$ number of times, the second member $m_1$ repeats $k_1$ number of times, and so on till member $m_{n-1}$; where n is the total number of objects in set A, and $$\sum_{i = 0}^{(n-1)} (k_i) <= n$$ is $$_rP_n^{\\{k_0, k_1, ...k\_{n-1}\\}} = \frac{\prod\_{i = 0}^{(r - 1)} (n - i)}{\prod\_{m = 0}^{(n - 1)} (\prod\_{j = 0}^{(k - 1)} (k - j))_m} = \frac{n!}{k_0.k_1...k_n.(n - r)!}$$.
 
> [!TIP]
> **Derivation of the number of permutations from the multiplication principle and the $$\prod$$ notation:**
> * _Lemma.01_: Recall that _A_ is a set of objects of cardinality $$|A| = n$$ members;
> * Hence, the number of the reproducible subsets by the multiplication principle of counting; **given the property of allowed repetitions** is $$\prod_{i = 0}^{(n-1)} (n)$$.
> * _Lemma.02_: Recall that _B_ is a sequence of objects taken from the set _A_; **given the property of repetitions of members are not allowed within a sequence**, and from _eq.01_; then $$\prod_{i = 0}^{(n-1)} (n - c)$$; where $$c = 0$$; 
> * _Lemma.03_: Let $$c = i$$; then $$\prod_{i = 0}^{(n-1)} (n - c) = \prod_{i = 0}^{(n-1)} (n - i)$$; with the assertion that: $$c = i$$.
> * _Corollary on Lemma.02_: It follows from _Lemma.02_ that _Lemma.03_ results a manipulation of _Lemma.01_ over some new assertions (i.e., repetitions allowed); the interchange of the $$c$$ constant with the $$i$$ variable shows that the number of the possible available objects decreases as we proceed with incrementing the position until reaching the end of the sequence _B_ which has the same cardinality as the original set _A_; hence the number $$i$$ subtracted from the cardinality of the original set is the number of the already used objects in sequence _B_ from the set _A_.
> * _Lemma.04_: Recall that _C_ is a sequence of objects taken from the set _A_; **given the property of repetitions of members are not allowed within the sequence**, and $$|C| <= |A|$$; then: if the number of possible configurations of sequence _C_ of set _A_ taken $$n$$ at a time is $$\prod_{i = 0}^{(n-1)} (n - i)$$; then let $$n = |C|$$, and whence $$|C| <= |A|$$ thence $$n <= |A|$$; therefore we can rewrite the formula as: $$\prod_{i = 0}^{(r-1)} (n - i)$$; where $$1 <= r <= n$$.
> 

## Combinations
- **Definition**: _**Combinations**_ are subsets selected from sets of members; such that the order doesn't matter, and the _repetition properties_ are specified; hence, the uniqueness of a subset chosen over a set of member is defined by the objects selected, and their count in that subset.
- **Formula**: Recall _A_ is a set of objects of cardinality $|A| = n$ members; 
   * The number of combinations of _A_ taken _r_ at a time is the number of all the possible subsets of _A_ of cardinality _r_; **given the property of repetitions are not allowed**, and $$1 <= r <= n$$: $$_rC_n = \frac{_rP_n}{\prod\_{i = 0}^{(r-1)} (r - i)} = \frac{_rP_n}{r!}$$.
   * The number of combinations of _A_ taken _r_ at a time is the number of all the possible subsets of _A_ of cardinality _r_; **given the property of allowed repetitions; such that **given the property of allowed repetitions of the permutated objects**; such that the first member $m_0$ repeats $k_0$ number of times, the second member $m_1$ repeats $k_1$ number of times, and so on till member $m_{n-1}$, and $$\sum_{i = 0}^{(n-1)} (k_i) <= n$$ is $$_rC_n^{\\{k_0, k_1, ...k\_{n-1}\\}} = \frac{_rP_n^{\\{k_0, k_1, ...k\_{n-1}\\}}}{\prod\_{i = 0}^{(r-1)} (r - i)}$$.

> [!TIP]
> **Derivation of the combination number from the number of permutations over the same cardinality:**
> * Recall that _A_ is a set of objects of cardinality $$|A| = n$$ number of members, _B_ is a subsequence over _A_ of cardinality _r_, and _C_ is a subset over _A_ of cardinality _r_, and **given repetitions of the members within the collections are not allowed**; where $$1 <= r <= n$$.
> * Now, if the number of all the possible permutations provided for _B_ over the set _A_ is: $$_rP\_n = \prod\_{i = 0}^{(r-1)} (n - i)$$.
> * Then, the number of all possible combinations of the _C_ subset of cardinality _r_ multiplied by the number of permutations over an r-element combination is the same as $$_rP\_n$$; hence $$C.\prod\_{i = 0}^{(r-1)} (r - i) = _rP_n$$, and therefore, the number of combinations of set _A_ taken _r_ at a time is: $$_rC_n = \frac{_rP_n}{\prod\_{i = 0}^{(r-1)} (r - i)} = \frac{_rP_n}{r!} = \frac{_rP_n}{_rP_r}$$.

## Mathematical Models
