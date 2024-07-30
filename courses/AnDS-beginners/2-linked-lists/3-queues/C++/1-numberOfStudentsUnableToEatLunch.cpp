/*
https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/description/

The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers 0
and 1 respectively. All students stand in a queue. Each student either prefers square or circular sandwiches.

The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are placed in a stack. At each step:

    - If the student at the front of the queue prefers the sandwich on the top of the stack, they will take it and leave the queue.
    - Otherwise, they will leave it and go to the queue's end.
    - This continues until none of the queue students want to take the top sandwich and are thus unable to eat.

You are given two integer arrays students and sandwiches where sandwiches[i] is the type of the i​​​​​​th 
sandwich in the stack (i = 0 is the top of the stack) and students[j] is the preference of the j​​​​​​th 
student in the initial queue (j = 0 is the front of the queue). Return the number of students that 
are unable to eat.

 
Example 1:
    Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
    Output: 0 
    Explanation:
        - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,0,1].
        - Front student leaves the top sandwich and returns to the end of the line making students = [0,0,1,1].
        - Front student takes the top sandwich and leaves the line making students = [0,1,1] and sandwiches = [1,0,1].
        - Front student leaves the top sandwich and returns to the end of the line making students = [1,1,0].
        - Front student takes the top sandwich and leaves the line making students = [1,0] and sandwiches = [0,1].
        - Front student leaves the top sandwich and returns to the end of the line making students = [0,1].
        - Front student takes the top sandwich and leaves the line making students = [1] and sandwiches = [1].
        - Front student takes the top sandwich and leaves the line making students = [] and sandwiches = [].
        Hence all students are able to eat.

Example 2:
    Input: students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
    Output: 3
 

Constraints:
    - 1 <= students.length, sandwiches.length <= 100
    - students.length == sandwiches.length
    - sandwiches[i] is 0 or 1.
    - students[i] is 0 or 1.
*/


#include <vector>
#include <algorithm>

class Solution {
public:
    // This algorithm is O(n) time as it requires 1 pass to count the number of 1s, and 1 pass through sandwiches
    // This makes is O(2n) time complexity which simplifies down to O(n)
    int countStudents(std::vector<int>& students, std::vector<int>& sandwiches) {
        int studentsNotEaten = students.size();

        // Note this could be done better with a hashmap
        int student1s = std::count(students.begin(), students.end(), 1);
        int student0s = studentsNotEaten - student1s;

        // Since students always wrap to back, and the lengths are the same, the order of students doesn't actually matter
        for (const int sandwich : sandwiches) {
            if (sandwich == 0) {
                // If there is still a student who eats 0s, decrement the number of students that havent eaten
                // and decrement the number of students who eat 0s.
                if (student0s-- > 0) --studentsNotEaten;

                // Else, no more students will eat the top sandwich, so no more students will eat
                else return studentsNotEaten;

            // Same logic but for students who eat 1s
            } else {
                if (student1s-- > 0) --studentsNotEaten;
                else return studentsNotEaten;
            }
        }
        return 0;
    }
};



int main() {

    return 0;
}