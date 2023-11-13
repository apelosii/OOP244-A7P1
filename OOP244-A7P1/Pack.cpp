#include "Pack.h"

namespace sdds {

	// =-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	// 
	//	 TODO:
	//		IMPLEMENT read method
	//		IMPLEMENT overload operator<< and operator>> to be able to print and read A Pack using cout and cin.
	//		"Container" class ambuigious in main.cpp (May be because of include in Pack.h and in main.cpp)
	// 
	// =-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	Pack::Pack(const char* nContent, int nSize, int nUnitSize, int nNumOfUnits)
		: Container::Container(nContent, nSize* nUnitSize, nNumOfUnits* nUnitSize) {
		if (nUnitSize > 0) {
			Size = nSize;
			UnitSize = nUnitSize;
			NumOfUnits = nNumOfUnits;
		}
		else {
			Container::setEmpty();
		}
	}

	int Pack::operator+=(int unitsToAdd) {
		NumOfUnits += unitsToAdd;
		// Calculate the total volume to add (units * UnitSize)
		int totalVolumeToAdd = unitsToAdd * UnitSize;
		// Call the base class's operator+=
		int addedVolume = Container::operator+=(totalVolumeToAdd);
		// Calculate the number of units added (addedVolume / UnitSize)
		int unitsAdded = addedVolume / UnitSize;
		return unitsAdded;
	}

	int Pack::operator-=(int unitsToRemove) {
		NumOfUnits -= unitsToRemove;
		// Calculate the total volume to remove (units * UnitSize)
		int totalVolumeToRemove = unitsToRemove * UnitSize;
		// Call the base class's operator-=
		int removedVolume = Container::operator-=(totalVolumeToRemove);
		// Calculate the number of units removed (removedVolume / UnitSize)
		int unitsRemoved = removedVolume / UnitSize;
		return unitsRemoved;
	}

	// Queries

	int Pack::unit() {
		return UnitSize;
	}
	int Pack::noOfUnits() {
		return NumOfUnits;
	}
	int Pack::size() {
		return Size;
	}

	// Methods

	void Pack::clear(int packSize, int nUnitSize, const char* nContent) {
		if (nUnitSize > 0) {
			Container::clear(packSize * nUnitSize, nContent);
			UnitSize = nUnitSize;
			Size = packSize;
			NumOfUnits = 0;
		}
	}

	std::ostream& Pack::print(std::ostream& ostr){
		Container::print(ostr);
		if (Container::operator bool()) {
			ostr << ", " << NumOfUnits << " in a pack of " << Size;
		}
		return ostr;
	}

	std::istream& Pack::read(std::istream& istr) {
		if (!(Container::operator bool())) {
			std::cout << "Broken Container, adding aborted! Press <ENTER> to continue....";
			while (istr.get() != '\n');
			return istr;
		}

		int missingUnits = size() - noOfUnits();

		if (missingUnits > 0) {
			std::cout << *this << std::endl;
			std::cout << "> ";

			int unitsToAdd;
			bool validInput = false;

			while (!validInput) {
				if (!(istr >> unitsToAdd)) {
					// Invalid integer input
					std::cout << "Invalid Integer, retry: ";
					istr.clear();
					istr.ignore(1000, '\n');
				}
				else if (unitsToAdd < 1 || unitsToAdd > missingUnits) {
					// Value out of range
					std::cout << "Value out of range [1<=" << unitsToAdd << "<=" << missingUnits << "]: ";
				}
				else {
					// Valid input
					validInput = true;
				}
			}

			// Add the units to the pack using operator+=
			int addedUnits = *this += unitsToAdd;

			// Print the message indicating the number of units added
			std::cout << "Added " << addedUnits << std::endl;
		}
		else {
			std::cout << "Pack is full!, press <ENTER> to continue...\n";
			while (istr.get() != '\n');
			return istr;
		}

		return istr;
	}

	std::ostream& operator<<(std::ostream& ostr, Pack& p) {
		return p.print(ostr);
	}

	std::istream& operator>>(std::istream& istr, Pack& p) {
		return p.read(istr);
	}

}