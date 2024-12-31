# ICPC Jakarta 2024 - Problem Repository

## Repository Structure

Each problem (from PA to PD for trial and A to M for contest) has their own folder. The folder name is the `slug` of the problem, which is the codename we used when we internally prepare the problems. The following table describes the slug for each problem

| Problem Code | Problem Slug | Problem Title            |
| ------------ | ------------ | ------------------------ |
| PA           | provincial   | ICPC Provincial          |
| PB           | brackets     | Palindromic Parentheses  |
| PC           | triangle     | Triangle Construction    |
| PD           | panda        | Red Panda                |
| A            | scramble     | Scrambled Scrabble       |
| B            | rooftop      | ICPC Square              |
| C            | saraga       | Saraga                   |
| D            | dragon       | Aquatic Dragon           |
| E            | foggy        | Narrower Passageway      |
| F            | game         | Grid Game 3-angle        |
| G            | maze         | X Aura                   |
| H            | newline      | Missing Separators       |
| I            | micro        | Microwavable Subsequence |
| J            | xorder       | Xorderable Array         |
| K            | twin         | GCDDCG                   |
| L            | bdfs         | Buggy DFS                |
| M            | laser        | Mirror Maze              |

In the problem folder, there should be exactly the following file/folder:

- `description.pdf`. The problem statement distributed to the contestants during the contest.
- `data/`. A folder consisting of all testcases. The sample inputs given in the problem statement will be in the form of `sample/[icpc/icpcp]-<slug>_sample_<testcase number>.[in/ans]`, while the hidden testcases will be in the form of `secret/[icpc/icpcp]-<slug>_1_<testcase number>.[in/ans]`.
- `solution.cpp`. The official solution used to generate the outputs of the testcases
- `scorer.cpp`. A validator used to validate contestants' output. The code accepts three arguments.
  - The first parameter will be used as the filename of the input file
  - The second parameter will be used as the filename of the judge's output file
  - The third parameter will be used as the filename of the contestant's output file
  - This code will print `WA` to stdout if the contestant's output is intended to be judged `WRONG ANSWER`, while it will print `AC` to stdout if the contestants's output is intended to be judged `CORRECT`.
- `verifier.py`. A verifier used to validate the input of the testcases. The code will crash if the input violates the problem constraint, while it will exit gracefully and will not output anything if the input satisfies the problem constraint.

## Limitations

The following table describes the time and memory limit for each problem.

| Problem Code | Problem Slug | Time Limit | Memory Limit |
| ------------ | ------------ | ---------- | ------------ |
| PA           | provincial   | 1 sec      | 1024 MB      |
| PB           | brackets     | 1 sec      | 1024 MB      |
| PC           | triangle     | 1 sec      | 1024 MB      |
| PD           | panda        | 1 sec      | 1024 MB      |
| A            | scramble     | 1 sec      | 1024 MB      |
| B            | rooftop      | 1 sec      | 1024 MB      |
| C            | saraga       | 1 sec      | 1024 MB      |
| D            | dragon       | 3 sec      | 1024 MB      |
| E            | foggy        | 1 sec      | 1024 MB      |
| F            | game         | 1 sec      | 1024 MB      |
| G            | maze         | 1 sec      | 1024 MB      |
| H            | newline      | 1 sec      | 1024 MB      |
| I            | micro        | 1 sec      | 1024 MB      |
| J            | xorder       | 1 sec      | 1024 MB      |
| K            | twin         | 1 sec      | 1024 MB      |
| L            | bdfs         | 1 sec      | 1024 MB      |
| M            | laser        | 1 sec      | 1024 MB      |

## Solutions

Note that while there is only one official published solution, we have a lot of other solutions prepared for our internal testing. These other solutions include, but not limited to:

- Solutions in several other languages
- Solutions that is intended to be incorrect (e.g. WA, TLE, etc.)
- Other correct solutions (especially on problems with more than one correct outputs for each input)

## Errata

None.

## Additional Notes

The problemset was officially deployed by the judges on [Codeforces](https://codeforces.com/contest/2045) and [TLX](https://tlx.toki.id/problems/icpc-jakarta-2024).