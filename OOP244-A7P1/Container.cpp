#include "Container.h"

namespace sdds {

	// Constructor and Destructor
	Container::Container(const char* newContent, int newCapacity, int newContentVolume) {
		size_t len = strlen(newContent) + 1;
		Content = new char[len];
		memcpy(Content, newContent, len);

		Capacity = newCapacity;
		ContentVolume = newContentVolume;
	}

	Container::~Container() {
		if (Content != nullptr) {
			delete[] Content;
			Content = nullptr;
		}
	}

	// Protected
	// --------------------------------
	void Container::setEmpty() {
		delete[] Content;
		Content = nullptr;
	}

	int Container::capacity() {
		return Capacity;
	}

	int Container::volume() {
		return ContentVolume;
	}
	// --------------------------------

	int Container::operator+=(int volume) {
		// if total of volume is less than Capacity
		if ((ContentVolume + volume) <= Capacity) {
			ContentVolume += volume;
			return volume;
		}
		else {
			// calculate the difference needed to hit Capacity
			int spaceAvail = Capacity - ContentVolume;
			ContentVolume += spaceAvail;
			return spaceAvail;
		}
	}

	int Container::operator-=(int volume) {
		if ((ContentVolume - volume) >= 0) {
			ContentVolume -= volume;
			return volume;
		}
		else {
			int removed = ContentVolume;
			ContentVolume = 0;
			return removed;
		}
	}

	Container::operator bool() const{
		if (strlen(Content) > 0 && ContentVolume <= Capacity) {
			return true;
		}
		return false;
	}

	// Methods
	// ------------------------------------------

	void Container::clear(int nCapacity, const char* nContent) {
		// Check if the provided capacity is a positive value
		if (nCapacity > 0) {
			// Deallocate any existing memory
			if (Content != nullptr) {
				delete[] Content;
				Content = nullptr;
			}

			// Allocate new memory for the content description and copy it
			size_t len = strlen(nContent) + 1;
			Content = new char[len];
			memcpy(Content, nContent, len);
			// Set the content volume to 0, assuming it's empty initially
			ContentVolume = 0;
		}
	}

	std::ostream& Container::print(std::ostream& ostr) {
		// ABC: (XXcc/YY)
		// ABC is the content description
		// XX is the content volume
		// YY is the capacity
		if (*this) {
			ostr << Content << ": (" << ContentVolume << "cc/" << Capacity << ")";
		}
		else {
			ostr << "****: (**cc/***)";
		}
		return ostr;
	}

	std::istream& Container::read(std::istream& istr) {
		if (!(*this)) {
			std::cout << "Broken Container, adding aborted! Press <ENTER> to continue...." << std::endl;
			while (istr.get() != '\n');
			return istr;
		}
		else {
			std::cout << "> ";

			// Foolproof integer entrys
			bool ok = true;
			while (ok) {
				int value = 0;
				if (!(istr >> value)) {
					istr.clear();
					istr.ignore(1000, '\n');
					std::cout << "Invalid Integer. retry: ";
				}
				else if (value > 0 && value < 220000) {
					std::cout << "added " << value << " CCs" << std::endl;
					*this += value;
					ok = false;
				}
				else {
					istr.clear();
					istr.ignore(1000, '\n');
					std::cout << "Value out of range [1<=val<=999]: ";
				}
			}
			return istr;
		}
	}

	// Overload operator<< and operator>> to be able to print and read A container using cout and cin.

	std::ostream& operator<<(std::ostream& ostr, Container& c){
		return c.print(ostr);
	}

	std::istream& operator>>(std::istream& istr, Container& c) {
		return c.read(istr);
	}
}