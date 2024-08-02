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


#include <stdlib.h>
#include <stdio.h>


int countInArr(const int target, const int* arr, const int arrSize)
{
    int count = 0;
    for (int i = 0; i < arrSize; i++) { if (arr[i] == target) ++count; }
    return count;
}

int countStudents(const int* students, const int studentsSize, const int* sandwiches, const int sandwichesSize)
{
    int studentsNotEaten = studentsSize;

    // Note this could be done better with a hashmap
    int student1sCount = countInArr(1, students, studentsSize);
    int student0sCount = studentsNotEaten - student1sCount;

    for (int i = 0; i < sandwichesSize; i++)
    {
        /*
        If the sandwhich is a 0 AND there is still a student who eats 0's, OR
        if the sandwhich is a 1 AND there is still a student who eats 1's,
        decrement the number of students who haven't yet eaten.
        Else, no more sandwhiches will be eaten, 
        therefore return the current number of students who haven't eaten.
        */
        if (!sandwiches[i] && student0sCount-- ||
             sandwiches[i] && student1sCount--) --studentsNotEaten;
        else return studentsNotEaten;
    }
    return 0;
}




int main() {
    int testStudents[6] = {1,1,1,0,0,1};
    int testSandwiches[6] = {1,0,0,0,1,1};
    printf("%d", countStudents(testStudents, 6, testSandwiches, 6));
}