#include "Library.h"

// Constructor
Library::Library(int initialCapacity): users(new User*[initialCapacity]), userCount(0), capacity(initialCapacity), totalRevenue(0)
{
}

// Destructor
Library::~Library()
{
    for (int i = 0 ; i < userCount ; ++i)
    {
        delete users[i];
        users[i] = nullptr;
    }
    delete[] users;
    users = nullptr;
}

void Library::addUser(int id, const string &name)
{
    if (userCount >= capacity)
    {
        int newcap = capacity * 2;
        User** newUsers = new User*[newcap];
        for (int i = 0 ; i < newcap ; ++i)
        {
            if (users[i] != nullptr)
            {
                newUsers[i] = users[i];
            }
            else
            {
                newUsers[i] = nullptr;
            }
        }
        delete[] users;
        users = newUsers;
        capacity = newcap;
    }
    users[userCount] = new User(id,name);
    ++userCount;
    totalRevenue += 5;
}

void Library::upgradeUserSlots(int userId, int additionalSlots)
{
    User* user = getUserById(userId);
    if (user == nullptr)
    {
        cout << "User ID " << userId << " not found." << endl;
    }
    else
    {
        user->updateMaxBooks(additionalSlots);
        totalRevenue += additionalSlots;
        cout << "User ID " << user->getUserId() << " upgraded by " << additionalSlots << " slots." << endl;
    }
}

double Library::getTotalRevenue() const
{
    return totalRevenue;
}

void Library::displayUsers() const
{
    if (userCount == 0)
    {
        cout << "No users in the library." << endl;
        return;
    }

    for (int i = 0; i < userCount; ++i)
    {
        if (users[i] != nullptr)
        {
            cout << "User ID: " << users[i]->getUserId()
                 << ", Name: " << users[i]->getUserName()
                 << ", Borrowed Books: " << users[i]->getNumBooksBorrowed()
                 << ", Max Books: " << users[i]->getMaxBooks()
                 << endl;
        }
    }
}


User *Library::getUserById(int userId) const
{
    for (int i = 0 ; i < userCount; ++i)
    {
        if (users[i]->getUserId() == userId)
        {
            return users[i];
        }
    }
    return nullptr;
}

void Library::addNewBook(Book *book)
{
    if (totalRevenue >= 2)
    {
        BookList &booklist = getLibraryInventory();
        if (booklist.searchList(book->getId()) != nullptr)
        {
            totalRevenue -= 2;
        }
        totalRevenue -= 2;
        booklist.insertBook(book);
        cout << "Book '" << book->getTitle() << "' added to the library." << endl;
    }
    else
    {
        cout << "Insufficient funds to add the book " << book->getTitle() << "." << endl;
    }
}

void Library::removeBook(int bookId)
{
    BookList booklist = getLibraryInventory();
    Book* book = booklist.searchList(bookId);
    if (book != nullptr)
    {
        booklist.removeBook(book);
        totalRevenue += 1;
    }
    else
    {
        cout << "Book with ID " << bookId << " not found in the library." << endl;
    }
}

void Library::displayBooks() const
{
    libraryInventory.displayBooks();
}

BookList &Library::getLibraryInventory()
{
    return libraryInventory;
}