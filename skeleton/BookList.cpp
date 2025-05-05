#include "BookList.h"
#include "Book.h"

BookList::BookList() : head(nullptr)
{
}

BookList::BookList(const BookList &other)
{
    if (other.head == nullptr)
    {
        this->head = nullptr;
    }
    else
    {
        Node* temp1 = other.head->next;
        Node* temp2 = other.head;
        Node* newnode = new Node(other.head->data);
        this->head = newnode;
        while (temp1 != nullptr)
        {
            Node* newnode = new Node(temp1->data);
            temp2->next = newnode;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
}

BookList::~BookList()
{
    if (head != nullptr)
    {
        Node* current = head;
        Node* nextnode = nullptr;
        while (current != nullptr)
        {
            nextnode = current->next;
            delete current;
            current = nextnode;
        }
        head = nullptr;
    }
}

bool BookList::isEmpty() const
{
    return (head == nullptr);
}

void BookList::insertBook(Book *book)
{
    if (!(isEmpty()))
    {
        Node* current = head;
        Node* last = nullptr;
        for (; current != nullptr; current=current->next)
        {
            if (current->data->getId() == book->getId())
            {
                book->changeInventoryCount(1);
                return;
            }
            if (current->next == nullptr)
            {
                last = current;
            }
        }
        Node* newnode = new Node(book);
        last->next = newnode;
    }
    else
    {
        Node* newnode = new Node(book);
        head = newnode;
    }
}

void BookList::removeBook(Book *book)
{
    if (!(isEmpty()))
    {
        Node* current = head;
        Node* previous = nullptr;
        for (; current != nullptr; current=current->next)
        {
            if (current->data->getId() == book->getId())
            {
                if (book->getInventoryCount() > 1)
                {
                    book->changeInventoryCount(-1);
                    return;
                }
                else if (current == head)
                {
                    head = current->next;
                    delete current;
                    current = head;
                    return;
                }
                else
                {
                    previous->next = current->next;
                    delete current;
                    return;
                }
            }
            previous = current;
        }
    }
    else
    {
        Node* newnode = new Node(book);
        newnode->next = head;
        head = newnode;
    }
}

void BookList::displayBooks() const
{
    /*
    There are 13 books in the library. They are:
Library Book Details:
ID: 1 - Title: The Great Gatsby - Author: F. Scott Fitzgerald - Rating: 4
ID: 2 - Title: 1984 - Author: George Orwell - Rating: 3
ID: 3 - Title: To Kill a Mockingbird - Author: Harper Lee - Rating: 2.5
ID: 4 - Title: Great Expectations - Author: Charles Dickens - Rating: 0
ID: 5 - Title: Pride and Prejudice - Author: Jane Austen - Rating: 2
ID: 6 - Title: The Catcher in the Rye - Author: J.D Salinger - Rating: 0
    */

    // Output the number of books

    // Reset current to the head to traverse again
    Node* current = head;

    // Display each book's details
    cout << "Library Book Details:\n";
    while (current != nullptr) {
        Book* book = current->data;
        cout << "ID: " << book->getId()
                  << " - Title: " << book->getTitle()
                  << " - Author: " << book->getAuthor()
                  << " - Rating: " << book->getRating()
                  << "\n";
        current = current->next;
    }
}

void BookList::sortBooks(SortCriteria criteria)
{
    switch (criteria)
    {
        case BY_RATING:
            for (Node* i = head; i->next != nullptr; i = i->next) {
                for (Node* j = i->next; j != nullptr; j = j->next) {
                    if (i->data->getRating() < j->data->getRating()) {
                        // Swap the book data between i and j
                        Book* temp = i->data;
                        i->data = j->data;
                        j->data = temp;
                    }
                }
            }
            break;    
        
            case BY_TITLE: {
                // Sorting by title without using string library.
                for (Node *i = head; i != nullptr; i = i->next) {
                    for (Node *j = i->next; j != nullptr; j = j->next) {
                        // Compare titles character by character
                        string title1 = i->data->getTitle(); // Assuming getTitle() returns a C-string
                        string title2 = j->data->getTitle();
        
                        bool swapNeeded = false;
                        for (int k = 0; title1[k] != '\0' && title2[k] != '\0'; ++k) {
                            if (title1[k] > title2[k]) {
                                swapNeeded = true;
                                break;
                            } else if (title1[k] < title2[k]) {
                                swapNeeded = false;
                                break;
                            }
                        }
        
                        // If titles are identical up to the end of one, the shorter title comes first
                        if (!swapNeeded && title1[0] != '\0' && title2[0] != '\0' && title1[0] == title2[0]) {
                            swapNeeded = (title1[0] != '\0' && title2[0] == '\0');
                        }
        
                        if (swapNeeded) {
                            // Swap the book data
                            Book *temp = i->data;
                            i->data = j->data;
                            j->data = temp;
                        }
                    }
                }
                break;
            }
        
            default:
                cout << "Invalid sorting criteria." << endl;
                break;
        }
            
}


Book *BookList::searchList(int bookId) const
{
    Node* current = head;
    while (current != nullptr)
    {
        if (current->data->getId() == bookId)
        {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

int BookList::countBooks() const
{
    Node* current = head;
    int count = 0; // To keep track of the number of books

    // Count the number of books
    while (current != nullptr) {
        count += current->data->getInventoryCount();
        current = current->next;
    }
    return count;
}

void BookList::rateBook(int bookId, double newRating)
{
    // Search for the book in the linked list
    Book* currbook = searchList(bookId);

    if (currbook != nullptr) 
    {
        currbook->addRating(newRating);
        cout << "Rating updated for Book " << bookId << ". New rating: " << currbook->getRating() << endl;
    } 
    else 
    {
        cout << "Book with ID " << bookId << " not found." << endl;
    }
}

Book *BookList::getBookWithMaxRating() const
{
    if (head == nullptr)
    {
        cout << "This book list is empty" << endl;
        return nullptr;
    }
    else 
    {
        Node* current = head;
        Book* max_rating_book = head->data;
        int max = head->data->getRating();
        for (; current != nullptr; current = current->next)
        {
            if (current->data->getRating() > max)
            {
                max_rating_book = current->data;
            }
        }
        return max_rating_book;
    }
}

Book *BookList::getBookWithMinRating() const
{
    if (head == nullptr)
    {
        cout << "This book list is empty" << endl;
        return nullptr;
    }
    else 
    {
        Node* current = head;
        Book* min_rating_book = head->data;
        int min = head->data->getRating();
        for (; current != nullptr; current = current->next)
        {
            if (current->data->getRating() < min)
            {
                min_rating_book = current->data;
            }
        }
        return min_rating_book;
    }
}

void BookList::reverseBooksByRating()
{
    this->sortBooks(BY_RATING);
    Node* current = head;
    Node* previous = nullptr;
    Node* next = nullptr;
    
    while (current != nullptr)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    head = previous;
}