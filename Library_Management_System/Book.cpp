#include "Book.h"

Book::Book() : bookId(0), title(""), author(""), inventoryCount(0), rating(0.0), ratingCount(0)
{  
}

Book::Book(int id, const string &t, const string &a, int count, double rat, int ratCount)
{
    this->bookId = id;
    this->title = t;
    this->author = a;
    this->inventoryCount = count;
    this->rating = rat;
    this->ratingCount = ratCount;
}

int Book::getId() const
{
    return this->bookId;
}

int Book::getInventoryCount() const
{
    return this->inventoryCount;
}

void Book::changeInventoryCount(int c)
{
    this->inventoryCount += c;
}

string Book::getTitle() const
{
    return this->title;
}

string Book::getAuthor() const
{
    return this->author;
}

double Book::getRating() const
{
    return this->rating;
}

void Book::addRating(double newRating)
{
    if (newRating > 5.0 || newRating < 0.0)
    {
        cout << "Rating must be between 0 and 5." << endl;
    }
    else
    {
        ratingCount++;
        rating = (newRating+rating*(ratingCount-1))/ratingCount;
    }
    
}