/*
https://leetcode.com/problems/design-browser-history/description/

You have a browser of one tab where you start on the homepage and you can visit another url, get back in the history number of steps or move forward in the history number of steps.

Implement the BrowserHistory class:
    - BrowserHistory(string homepage) Initializes the object with the homepage of the browser.
    - void visit(string url) Visits url from the current page. It clears up all the forward history.
    - string back(int steps) Move steps back in history. If you can only return x steps in the history and steps > x, you will return only x steps. Return the current url after moving back in history at most steps.
    - string forward(int steps) Move steps forward in history. If you can only forward x steps in the history and steps > x, you will forward only x steps. Return the current url after forwarding in history at most steps.
    

Example:
    Input:
    ["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
    [["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]
    Output:
    [null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]

Explanation:
    BrowserHistory browserHistory = new BrowserHistory("leetcode.com");
    browserHistory.visit("google.com");       // You are in "leetcode.com". Visit "google.com"
    browserHistory.visit("facebook.com");     // You are in "google.com". Visit "facebook.com"
    browserHistory.visit("youtube.com");      // You are in "facebook.com". Visit "youtube.com"
    browserHistory.back(1);                   // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
    browserHistory.back(1);                   // You are in "facebook.com", move back to "google.com" return "google.com"
    browserHistory.forward(1);                // You are in "google.com", move forward to "facebook.com" return "facebook.com"
    browserHistory.visit("linkedin.com");     // You are in "facebook.com". Visit "linkedin.com"
    browserHistory.forward(2);                // You are in "linkedin.com", you cannot move forward any steps.
    browserHistory.back(2);                   // You are in "linkedin.com", move back two steps to "facebook.com" then to "google.com". return "google.com"
    browserHistory.back(7);                   // You are in "google.com", you can move back only one step to "leetcode.com". return "leetcode.com"
    

Constraints:
    1 <= homepage.length <= 20
    1 <= url.length <= 20
    1 <= steps <= 100
    homepage and url consist of  '.' or lower case English letters.
    At most 5000 calls will be made to visit, back, and forward.
*/

#include <string>
#include <iostream>

struct Page {
    std::string url;
    Page* next;
    Page* prev;

    Page(std::string url, Page* next = nullptr, Page* prev = nullptr) 
    : url(url), next(next), prev(prev) {}
};


class BrowserHistory {
private:
    Page* firstPage;
    Page* currentPage;

    void freeAllForwardHistory() {
        Page* page = currentPage->next;
        Page* nextPage;
        while (page) {
            nextPage = page->next;
            delete page;
            page = nextPage;
        }
        currentPage->next = nullptr;
    }

public:
    BrowserHistory(std::string homepage) {
        firstPage = new Page(homepage);
        currentPage = firstPage;
    }

    ~BrowserHistory() {
        currentPage = firstPage;
        freeAllForwardHistory();
        delete firstPage;
    }
    
    void visit(std::string url) {
        freeAllForwardHistory();
        currentPage->next = new Page(url, nullptr, currentPage);
        currentPage = currentPage->next;
    }
    
    std::string back(int steps) {
        while (currentPage != firstPage && steps--) currentPage = currentPage->prev;
        return currentPage->url;
    }
    
    std::string forward(int steps) {
        while (currentPage->next != nullptr && steps--) currentPage = currentPage->next;
        return currentPage->url;
    }


    void display() {
        Page* page = firstPage;
        while (page) {
            if (page == currentPage) std::cout << "[curr] ";
            std::cout << page->url << " -> ";
            page = page->next;
        }
        std::cout << "\n";
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */


int main() {
    BrowserHistory* obj = new BrowserHistory("leetcode.com");
    obj->display();
    obj->visit("google.com");
    obj->display();
    obj->visit("facebook.com");
    obj->display();
    obj->back(3);
    obj->display();
    obj->forward(1);
    obj->display();
    obj->back(1);
    obj->display();
    obj->forward(3);
    obj->display();
    obj->back(2);
    obj->display();
    obj->visit("youtube.com");
    obj->display();
    delete obj;
    return 0;
}