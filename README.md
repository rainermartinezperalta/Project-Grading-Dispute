# Project Grading Dispute - Feedback Request

## Overview
This repository contains the files and context for a project I submitted as part of my Operating Systems course. I am seeking feedback from coding experts and the community to determine if my work aligns with the assignment requirements and if I was graded fairly.

### **The Issue**
After submitting my project, I was informed that my work did not meet the requirements. I disagree with this assessment and believe my implementation is valid. This repository includes:
- The original assignment instructions.
- The provided starter code.
- My submitted code.
- The professor's and teaching assistant's feedback.

---

## Assignment Summary

### **Project 1: Dining Philosopher's Problem**
Simulate a restaurant using multi-threaded programming where:
- Small and big groups dine at corresponding tables.
- Small groups can use big tables under specific conditions.
- Groups must wait if no suitable table is available.
- Implement functions: `small_group_dining()` and `big_group_dining()`.

### **Requirements**:
1. Use mutexes and condition variables for synchronization.
2. Match the output format provided.
3. Avoid hard-coding solutions.

Refer to the full [assignment instructions](assignment/assignment_instructions.md) for details.

---

## Provided Files
The original files provided for the project are stored in the `assignment/original_files/` folder. These include:
- `dining.c` (starter implementation for main logic).
- `dining.h` (header file for data structures and macros).
- `Makefile` (build configuration).
- Other associated files for sorting.

---

## Submitted Files
My submitted implementation is stored in the `submitted_files/` folder. Key changes include:
- **Implemented `small_group_dining()` and `big_group_dining()` functions.**
- **Used mutexes and condition variables for thread synchronization.**
- **Adhered to assignment instructions while ensuring correct output.**

---

## Feedback Received
The teaching assistant and professor provided the following feedback:
1. **TA's Comments**:
   - The code doesn’t use the `DINING()` function (I did use it).
   - Small and big groups were not handled in separate functions (they are).
   - The code was flagged as AI-generated (it is not; I wrote it myself).
   - Modifying starter code is prohibited (this was not explicitly stated in the assignment).
   - The Makefile update is irrelevant to the grading.
   
2. **Professor's Comments**:
    The professor followed up with:
    > "As **REDACTED** has stated above, the whole idea of providing starter code is so that you work with the given template. Considering you have submitted all labs and assignments during the semester, there shouldn't have been a doubt about it. As such, you have been given the best grade possible for your submission."

---

## **Discord Comments**:
    In the course Discord server, the professor mentioned:
    > "Yes, I do expect that. Perhaps I'll just take a look at everyone's Q1 in that case. Just make sure your execution is not serial. Logically the code should be correct and doing what is instructed in the PDF."

    Other students also commented about issues with the provided `Makefile` not working properly, which prompted me to fix it as part of my submission. This wasn’t addressed in the grading feedback.

---

## Why I Believe My Code is Correct
- **Separate Functions**: `small_group_dining()` and `big_group_dining()` were implemented to handle the groups as required.
- **Synchronization**: Mutexes and condition variables were used for thread safety.
- **Output**: Matches the sample output provided.
- **Dynamic Logic**: The implementation handles different group and table types dynamically, avoiding hard-coded solutions.

---

### **Clarifications on Code**:
1. **DINING() Function**: 
   - I did call the `DINING()` function in both `small_group_dining()` and `big_group_dining()` to simulate the dining process.
   - It was explicitly mentioned in the assignment that this function must be used, and I followed this instruction.

2. **Makefile**:
   - The provided `Makefile` did not work initially. I noticed other students commenting about this issue on Discord and fixed it in my submission to ensure my code compiled and ran correctly.

3. **Starter Code Modification**:
   - Nowhere in the assignment does it explicitly prohibit modifying other parts of the starter code. While I used my judgment to add logging and adjustments for clarity, the fundamental structure of the project remains intact.

4. **AI-Generated Code**:
   - The flagged code is entirely my work. I saved multiple versions of my implementation, iterating and testing extensively. I returned to earlier versions when debugging complex logic, which might have led to similarities in code structure.

---

## Questions for Feedback
1. Does my implementation meet the assignment requirements as outlined?
2. Was modifying the starter code acceptable given the instructions provided?
3. Could the output generated by my submission be considered valid for the project?
4. How should I approach this situation with my professor and TA? Should I escalate this further?

---

## How You Can Help
- **Review My Code**: Compare the starter code and my submission. Share feedback on whether my changes align with the assignment's expectations.
- **Provide Guidance**: If you've experienced similar grading disputes, what steps helped resolve them?

Thank you for your time and expertise!