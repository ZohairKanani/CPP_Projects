#include "User.h"
#include "Book.h"

User::User() : userId(0), name(""), numBooksBorrowed(0), maxBooks(5), booksBorrowed(new Book*[maxBooks])
{
    for (int i = 0 ; i < maxBooks; ++i)
    {
        booksBorrowed[i] = nullptr;
    }
}

User::User(int id, const string &n, int borrow, int max) : userId(id), name(n), numBooksBorrowed(borrow), maxBooks(max), booksBorrowed(new Book*[maxBooks])
{
    for (int i = 0 ; i < maxBooks; ++i)
    {
        booksBorrowed[i] = nullptr;
    }
}

User::~User()
{
    for (int i = 0; i < numBooksBorrowed; ++i)
    {
        delete booksBorrowed[i];
        booksBorrowed[i] = nullptr; 
    }
    delete[] booksBorrowed;
    booksBorrowed = nullptr;
}

void User::borrowBook(Book *book)
{
    if (numBooksBorrowed >= maxBooks)
    {
        cout << "You cannot borrow more books." << endl;
    }
    else if (book->getInventoryCount() == 0)
    {
        cout << "This book is currently unavailable." << endl;
    }
    else
    {
        cout << "Successfully borrowed: " << book->getTitle() << endl;
        book->changeInventoryCount(-1);
        for (int i = 0 ; i < numBooksBorrowed ; ++i)
        {
            if (booksBorrowed[i]->getTitle() == book->getTitle())
            {
                
                numBooksBorrowed++;
                booksBorrowed[i]->changeInventoryCount(1);
                return;
            }
        }
        booksBorrowed[numBooksBorrowed++] = new Book(book->getId(), book->getTitle(), book->getAuthor(), 1, book->getRating(), 0);

        
    }
}

void User::returnBook(Book *book)
{
    int i = 0;
    for ( ; i < numBooksBorrowed ; ++i)
    {
        if (booksBorrowed[i]->getId() == book->getId())
        {
            break;
        }
    }
    if (i == numBooksBorrowed)
    {
        cout << "This book was not borrowed by you." << endl;
    }
    else
    {
        cout << "Successfully returned: " << book->getTitle() << endl;
        booksBorrowed[i]->changeInventoryCount(-1);
        book->changeInventoryCount(1);
        numBooksBorrowed--;
        if (booksBorrowed[i]->getInventoryCount() == 0)
        {
            delete booksBorrowed[i];
            while(i < numBooksBorrowed - 1)
            {
                booksBorrowed[i] = booksBorrowed[i+1];
            }
        }
    }
}

int User::getNumBooksBorrowed() const
{
    return numBooksBorrowed;
}

int User::getUserId() const
{
    return userId;
}

string User::getUserName() const
{
    return name;
}

int User::getMaxBooks() const
{
    return maxBooks;
}

void User::viewBorrowedBooks() const
{
    if (numBooksBorrowed == 0) { // Check if the user has not borrowed any books
        cout << name << " has not borrowed any books." << endl;
    } else {
        cout << name << "'s Borrowed Books:" << endl; // Display user's name and title
        for (int i = 0 ; booksBorrowed[i] != nullptr; ++i) { // Iterate through the borrowed books map
            cout << booksBorrowed[i]->getTitle() << " (x" << booksBorrowed[i]->getInventoryCount() << ")" << endl;
        }
    }
}


void User::giveRating(BookList &list, int bookId, double newRating)
{
    if (numBooksBorrowed >= maxBooks)
    {
        cout << "User is blocked and cannot rate books." << endl;
    }
    else
    {
        list.rateBook(bookId, newRating);
    }
}

void User::updateMaxBooks(int additionalSlots)
{
    if (additionalSlots <= 0)
    {
        cout << "Invalid number of additional slots." << endl;
        return;
    }

    maxBooks += additionalSlots;

    Book** newBooksBorrowed = new Book*[maxBooks];
    int i = 0;
    for (; booksBorrowed[i] != nullptr; ++i)
    {
        newBooksBorrowed[i] = booksBorrowed[i];
    }

    for (; i < maxBooks; ++i)
    {
        newBooksBorrowed[i] = nullptr;
    }

    delete[] booksBorrowed;
    booksBorrowed = newBooksBorrowed;

    cout << "Max books updated to: " << maxBooks << endl;
}
